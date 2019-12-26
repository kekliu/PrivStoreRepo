//#include <functional>
//#include <iostream>
// using namespace std;
// function<void()> f;
// void func() {
//  int i = 666;
//  f = [&]() { cout << i << endl; };
//  f();
//}
// int main(int argc, char *argv[]) {
//  func();
//  f();
//  return 0;
//}

#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace Eigen;

const double DERIV_STEP = 1e-5;
const int MAX_ITER = 25;

double func(const VectorXd& input, const VectorXd& output,
            const VectorXd& params, double objIndex) {
  // obj = A * sin(Bx) + C * cos(D*x) - F
  double x1 = params(0);
  double x2 = params(1);
  double x3 = params(2);
  double x4 = params(3);

  double t = input(objIndex);
  double f = output(objIndex);

  return x1 * sin(x2 * t) + x3 * cos(x4 * t) - f;
}

// Return vector make up of func() element.
VectorXd objF(const VectorXd& input, const VectorXd& output,
              const VectorXd& params) {
  VectorXd obj(input.rows());
  for (int i = 0; i < input.rows(); i++)
    obj(i) = func(input, output, params, i);

  return obj;
}

// F = (f ^t * f)/2
double Func(const VectorXd& obj) { return obj.squaredNorm() / 2; }

// Numerical deriviation
double Deriv(const VectorXd& input, const VectorXd& output, int objIndex,
             const VectorXd& params, int paraIndex) {
  VectorXd para1 = params;
  VectorXd para2 = params;

  para1(paraIndex) -= DERIV_STEP;
  para2(paraIndex) += DERIV_STEP;

  double obj1 = func(input, output, para1,
                     objIndex);  // obj = A * sin(Bx) + C * cos(D*x) - F
  double obj2 = func(input, output, para2, objIndex);

  return (obj2 - obj1) / (2 * DERIV_STEP);
}

MatrixXd Jacobin(const VectorXd& input, const VectorXd& output,
                 const VectorXd& params) {
  int rowNum = input.rows();
  int colNum = params.rows();
  MatrixXd Jac(rowNum, colNum);
  for (int i = 0; i < rowNum; i++) {
    for (int j = 0; j < colNum; j++) {
      Jac(i, j) = Deriv(input, output, i, params, j);
    }
  }
  return Jac;
}

void gaussNewton(const VectorXd& input, const VectorXd& output,
                 VectorXd& params) {
  double last_sum = 0;

  int iterCnt = 0;
  printf("Gauss-Newton Algorithm:\n");
  while (iterCnt++ < MAX_ITER) {
    VectorXd R = objF(input, output, params);

    double sum = 0;
    sum = Func(R);  // F = (f ^t * f)/2

    printf("%4d     %10f %10f %10f %10f  %14f\n", iterCnt, params[0], params[1],
           params[2], params[3], sum);

    if (fabs(sum - last_sum) <= 1e-6) break;
    last_sum = sum;

    MatrixXd J = Jacobin(input, output, params);

    params += -(J.transpose() * J).inverse() * J.transpose() * R;
  }
}

double maxMatrixDiagonale(const MatrixXd& Hessian) {
  int max = 0;
  for (int i = 0; i < Hessian.rows(); i++) {
    if (Hessian(i, i) > max) max = Hessian(i, i);
  }
  return max;
}

// L(h) = F(x) + h^t*J^t*f + h^t*J^t*J*h/2
// deltaL = h^t * (u * h - g)/2
double linerDeltaL(const VectorXd& step, const VectorXd& gradient,
                   const double u) {
  double L = step.transpose() * (u * step - gradient);
  return L / 2;
}

void levenMar(const VectorXd& input, const VectorXd& output, VectorXd& x) {
  double tao = 1e-3;
  double eps1 = 1e-12;
  double eps2 = 1e-12;
  int k = 0;
  long v = 2;
  VectorXd f = objF(input, output, x);
  MatrixXd J = Jacobin(input, output, x);  // jacobin
  MatrixXd A = J.transpose() * J;          // hessian
  VectorXd g = J.transpose() * f;          // gradient
  double u = tao * maxMatrixDiagonale(A);
  printf("\nLevenberg-Marquart Algorithm:\n");
  while (k++ < MAX_ITER) {
    if (g.norm() <= eps1) {
      cout << "stop g(x) = 0 for a local minimizer optimizer." << endl;
      break;
    }
    printf("%4d     %13.8f%13.8f%13.8f%13.8f%14.8f\n", k, x[0], x[1], x[2],
           x[3], Func(f));
    VectorXd h =
        -(A + u * MatrixXd::Identity(x.rows(), x.rows())).inverse() * g;
    //    std::cout << eps2 * (x.norm() + eps2) << ", " << h.transpose() <<
    //    std::endl;
    if (h.norm() <= eps2 * (x.norm() + eps2)) {
      cout << "stop because change in x is small" << endl;
      break;
    }
    VectorXd x_new = x + h;
    VectorXd F_new = objF(input, output, x_new);
    double deltaF = Func(f) - Func(F_new);
    double deltaL = linerDeltaL(h, g, u);
    double rho = deltaF / deltaL;
    std::cout << "rho = " << rho << ", u= " << u << ", v= " << v << std::endl;
    if (rho > 0) {
      // update x
      x = x_new;
      // update A g
      f = objF(input, output, x);
      J = Jacobin(input, output, x);
      A = J.transpose() * J;
      g = J.transpose() * f;
      // update u v
      u *= std::max(1.0 / 3.0, 1 - pow(2 * rho - 1, 3));
      v = 2;
    } else {
      u *= v;
      v *= 2;
    }
  }
}

void dogLeg(const VectorXd& input, const VectorXd& output, VectorXd& params) {
  //  int errNum = input.rows();    // error num
  //  int paraNum = params.rows();  // parameter num

  VectorXd obj = objF(input, output, params);
  MatrixXd Jac = Jacobin(input, output, params);  // jacobin
  VectorXd gradient = Jac.transpose() * obj;      // gradient

  // initial parameter tao v epsilon1 epsilon2
  double eps1 = 1e-12, eps2 = 1e-12, eps3 = 1e-12;
  double radius = 1.0;

  bool found = obj.norm() <= eps3 || gradient.norm() <= eps1;
  if (found) return;

  //  double last_sum = 0;
  int iterCnt = 0;
  while (iterCnt < MAX_ITER) {
    VectorXd obj = objF(input, output, params);
    MatrixXd Jac = Jacobin(input, output, params);  // jacobin
    VectorXd gradient = Jac.transpose() * obj;      // gradient

    if (gradient.norm() <= eps1) {
      cout << "stop F'(x) = g(x) = 0 for a global minimizer optimizer." << endl;
      break;
    }
    if (obj.norm() <= eps3) {
      cout << "stop f(x) = 0 for f(x) is so small";
      break;
    }

    // compute how far go along stepest descent direction.
    double alpha = gradient.squaredNorm() / (Jac * gradient).squaredNorm();
    // compute gauss newton step and stepest descent step.
    VectorXd stepest_descent = -alpha * gradient;
    VectorXd gauss_newton =
        (Jac.transpose() * Jac).inverse() * Jac.transpose() * obj * (-1);

    double beta = 0;

    // compute dog-leg step.
    VectorXd dog_leg(params.rows());
    if (gauss_newton.norm() <= radius)
      dog_leg = gauss_newton;
    else if (alpha * stepest_descent.norm() >= radius)
      dog_leg = (radius / stepest_descent.norm()) * stepest_descent;
    else {
      VectorXd a = alpha * stepest_descent;
      VectorXd b = gauss_newton;
      double c = a.transpose() * (b - a);
      beta =
          (sqrt(c * c +
                (b - a).squaredNorm() * (radius * radius - a.squaredNorm())) -
           c) /
          (b - a).squaredNorm();

      dog_leg = alpha * stepest_descent +
                beta * (gauss_newton - alpha * stepest_descent);
    }

    cout << "dog-leg: " << endl << dog_leg << endl;

    if (dog_leg.norm() <= eps2 * (params.norm() + eps2)) {
      cout << "stop because change in x is small" << endl;
      break;
    }

    VectorXd new_params(params.rows());
    new_params = params + dog_leg;

    cout << "new parameter is: " << endl << new_params << endl;

    // compute f(x)
    obj = objF(input, output, params);
    // compute f(x_new)
    VectorXd F_new = objF(input, output, new_params);

    // compute delta F = F(x) - F(x_new)
    double deltaF = Func(obj) - Func(F_new);

    // compute delat L =L(0)-L(dog_leg)
    double deltaL = 0;
    if (gauss_newton.norm() <= radius)
      deltaL = Func(obj);
    else if (alpha * stepest_descent.norm() >= radius)
      deltaL = radius * (2 * alpha * gradient.norm() - radius) / (2.0 * alpha);
    else {
      VectorXd a = alpha * stepest_descent;
      VectorXd b = gauss_newton;
      double c = a.transpose() * (b - a);
      beta =
          (sqrt(c * c +
                (b - a).squaredNorm() * (radius * radius - a.squaredNorm())) -
           c) /
          (b - a).squaredNorm();

      deltaL = alpha * (1 - beta) * (1 - beta) * gradient.squaredNorm() / 2.0 +
               beta * (2.0 - beta) * Func(obj);
    }

    double roi = deltaF / deltaL;
    if (roi > 0) {
      params = new_params;
    }
    if (roi > 0.75) {
      radius = max(radius, 3.0 * dog_leg.norm());
    } else if (roi < 0.25) {
      radius = radius / 2.0;
      if (radius <= eps2 * (params.norm() + eps2)) {
        cout << "trust region radius is too small." << endl;
        break;
      }
    }

    cout << "roi: " << roi << " dog-leg norm: " << dog_leg.norm() << endl;
    cout << "radius: " << radius << endl;

    iterCnt++;
    cout << "Iterator " << iterCnt << " times" << endl << endl;
  }
}

int main() {
  // obj = A * sin(Bx) + C * cos(D*x) - F
  // there are 4 parameter: A, B, C, D.
  int num_params = 4;

  // generate random data using these parameter
  int total_data = 100;

  VectorXd input(total_data);
  VectorXd output(total_data);

  double A = 5, B = 1, C = 10, D = 2;
  // load observation data
  for (int i = 0; i < total_data; i++) {
    // generate a random variable [-10 10]
    double x = 20.0 * ((rand() % 1000) / 1000.0) - 10.0;
    double deltaY = 0.3 * (rand() % 1000) / 1000.0;
    double y = A * sin(B * x) + C * cos(D * x) + deltaY;

    input(i) = x;
    output(i) = y;
  }

  // gauss the parameters
  VectorXd params_gaussNewton(num_params);
  // init gauss
  //  params_gaussNewton << 5.3, 1, 10.3, 2;
  //  params_gaussNewton << 5.3, 1.3, 10.3, 2;
  params_gaussNewton << 1.6, 1.4, 6.2, 1.7;

  VectorXd params_levenMar = params_gaussNewton;
  VectorXd params_dogLeg = params_gaussNewton;

  gaussNewton(input, output, params_gaussNewton);
  levenMar(input, output, params_levenMar);
  //  dogLeg(input, output, params_dogLeg);

  cout << "gauss newton parameter: " << endl
       << params_gaussNewton << endl
       << endl
       << endl;
  cout << "Levenberg-Marquardt parameter: " << endl
       << params_levenMar << endl
       << endl
       << endl;
  //  cout << "dog-leg parameter: " << endl
  //       << params_dogLeg << endl
  //       << endl
  //       << endl;
}
