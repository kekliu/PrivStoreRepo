#include <ceres/ceres.h>

using Vec = Eigen::Vector3d;

namespace {

inline Eigen::Quaterniond toQuaterniond(const Eigen::Vector3d &v3d) {
  const double kAngleEpisode = 1e-6;
  double theta = v3d.norm();
  double half_theta = 0.5 * theta;

  double imag_factor;
  double real_factor = cos(half_theta);
  if (theta < kAngleEpisode) {
    double theta_sq = theta * theta;
    double theta_po4 = theta_sq * theta_sq;
    imag_factor = 0.5 - (1 / 48.) * theta_sq + (1 / 3840.) * theta_po4;
  } else {
    double sin_half_theta = sin(half_theta);
    imag_factor = sin_half_theta / theta;
  }

  return Eigen::Quaterniond(real_factor, imag_factor * v3d.x(),
                            imag_factor * v3d.y(), imag_factor * v3d.z());
}

} // namespace

///////////////////// autodiff begin /////////////////////
class CostFunctor {
public:
  CostFunctor(Vec x, Vec y) : x_(x), y_(y) {}

  template <typename T> bool operator()(const T *const q_raw, T *e_raw) const {
    Eigen::Map<const Eigen::Quaternion<T>> q(q_raw);
    Eigen::Map<Eigen::Matrix<T, 3, 1>>{e_raw} =
        (q * x_.cast<T>() - y_.cast<T>());
    return true;
  }

  static ceres::CostFunction *Create(const Vec &x, const Vec &y) {
    return new ceres::AutoDiffCostFunction<CostFunctor, 3, 4>(
        new CostFunctor(x, y));
  }

private:
  Vec x_;
  Vec y_;
};

void TestCostFunctor() {
  Eigen::Quaterniond q = Eigen::Quaterniond(0, 0.6, 0.8, 0);
  ceres::Problem problem;
  // Q1: sqrt derivate is infinite when sqrt(0)
  // A: sqrt'(x) is infinite when x=0
  // Q2: when use head 3 records, opt failed
  // Q: TODO
  problem.AddResidualBlock(CostFunctor::Create({1, 0, 0}, {1, 0, 0}), nullptr,
                           q.coeffs().data());
  problem.AddResidualBlock(CostFunctor::Create({0, 0, 3}, {0, 0, 3}), nullptr,
                           q.coeffs().data());
  problem.AddResidualBlock(CostFunctor::Create({0, 2, 0}, {0, 2, 0}), nullptr,
                           q.coeffs().data());
  problem.AddResidualBlock(CostFunctor::Create({0, 2, 2}, {0, 2, 2}), nullptr,
                           q.coeffs().data());

  problem.AddParameterBlock(q.coeffs().data(), 4,
                            new ceres::EigenQuaternionParameterization());

  ceres::Solver::Options option;
  option.minimizer_progress_to_stdout = true;
  ceres::Solver::Summary summary;
  ceres::Solve(option, &problem, &summary);
  std::cout << summary.BriefReport() << std::endl;
}
///////////////////// autodiff end /////////////////////

///////////////////// custom begin /////////////////////
inline Eigen::Matrix3d Skew(const Vec &t) {
  Eigen::Matrix3d t_hat;
  t_hat << 0, -t(2), t(1), t(2), 0, -t(0), -t(1), t(0), 0;
  return t_hat;
}

class CostFunctorSO3 : ceres::SizedCostFunction<3, 4> {
public:
  CostFunctorSO3(Vec x, Vec y) : x_(std::move(x)), y_(std::move(y)) {}

  bool Evaluate(double const *const *parameters, double *residuals,
                double **jacobians) const override {
    Eigen::Map<const Eigen::Quaterniond> q(parameters[0]);
    Eigen::Map<Eigen::Vector3d>{residuals} = q * x_ - y_;

    if (jacobians) {
      if (jacobians[0]) {
        Eigen::Map<Eigen::Matrix<double, 3, 4, Eigen::RowMajor>> J(
            jacobians[0]);
        // keypoint1:
        // jacobian of q * SO3::exp(x)  wrt. x at x=0
        // that is the jacobian of redisual wrt tanget space
        J.leftCols(3) = -(q.toRotationMatrix() * Skew(x_));
        J.rightCols(1).setZero();
      }
    }
    return true;
  }

  static ceres::CostFunction *Create(const Vec &x, const Vec &y) {
    return new CostFunctorSO3(x, y);
  }

private:
  Vec x_;
  Vec y_;
};

class ParameterizationSO3 : public ceres::LocalParameterization {
public:
  bool Plus(const double *x, const double *delta,
            double *x_plus_delta) const override {
    auto dq = toQuaterniond(Vec(delta));
    Eigen::Map<Eigen::Quaterniond>{x_plus_delta} =
        (Eigen::Map<const Eigen::Quaterniond>{x} * dq).normalized();
    return true;
  }

  bool ComputeJacobian(const double *x, double *jacobian) const override {
    // use RowMajor in Matrix instead of Map
    Eigen::Map<Eigen::Matrix<double, 4, 3, Eigen::RowMajor>> J(jacobian);
    // keypoint2:
    // we've already got jacobian of rediduals to tanget space,
    // so local parameterization jacobian should be set to identity
    J.setIdentity();
    return true;
  }

  int GlobalSize() const override { return 4; }

  int LocalSize() const override { return 3; }
};

void TestCostFunctorSO3() {
  Eigen::Quaterniond q = Eigen::Quaterniond(0, 0.6, 0.8, 0);
  ceres::Problem problem;
  problem.AddResidualBlock(CostFunctorSO3::Create({1, 0, 0}, {1, 0, 0}),
                           nullptr, q.coeffs().data());
  problem.AddResidualBlock(CostFunctorSO3::Create({0, 0, 3}, {0, 0, 3}),
                           nullptr, q.coeffs().data());
  problem.AddResidualBlock(CostFunctorSO3::Create({0, 2, 0}, {0, 2, 0}),
                           nullptr, q.coeffs().data());
  problem.AddResidualBlock(CostFunctorSO3::Create({0, 2, 2}, {0, 2, 2}),
                           nullptr, q.coeffs().data());

  problem.AddParameterBlock(q.coeffs().data(), 4, new ParameterizationSO3());

  ceres::Solver::Options option;
  option.minimizer_progress_to_stdout = true;
  ceres::Solver::Summary summary;
  ceres::Solve(option, &problem, &summary);
  std::cout << summary.BriefReport() << std::endl;
}
///////////////////// custom end /////////////////////

int main() {
  TestCostFunctor();
  TestCostFunctorSO3();

  return 0;
}
