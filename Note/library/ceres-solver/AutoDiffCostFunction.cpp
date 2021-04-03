#include <ceres/ceres.h>
#include <Eigen/Eigen>
#include <vector>

struct ExponentialResidual {
  ExponentialResidual(std::vector<double> data) : data_(data) {}

  template <typename T>
  bool operator()(const T* const trans, const T* const rotat,
                  T* residual) const {
    Eigen::Matrix<T, 3, 3> rotation;
    rotation = Eigen::AngleAxis<T>(rotat[0], Eigen::Matrix<T, 3, 1>::UnitZ());
    Eigen::Matrix<T, 3, 1> translation(trans[0], trans[1], T(0));
    Eigen::Matrix<T, 3, 1> p1(T(data_[0]), T(data_[1]), T(0));
    Eigen::Matrix<T, 3, 1> p2(T(data_[2]), T(data_[3]), T(0));
    Eigen::Matrix<T, 3, 1> resid = rotation * p1 + translation - p2;
    residual[0] = resid[0];
    residual[1] = resid[1];
    return true;
  }

 private:
  const std::vector<double> data_;
};

int main(int argc, char** argv) {
  std::vector<std::vector<double> > data = {
      {0, 0, 0, 1}, {1, 0, 0, 2.1}, {1, 1, -1, 2}};

  double rotation[1] = {0};
  double translation[2] = {0};

  ceres::Problem problem;
  for (auto&& item : data) {
    problem.AddResidualBlock(
        new ceres::AutoDiffCostFunction<ExponentialResidual, 2, 2, 1>(
            new ExponentialResidual(item)),
        new ceres::HuberLoss(0.1), translation, rotation);
  }

  ceres::Solver::Options options;
  options.max_num_iterations = 25;
  options.minimizer_progress_to_stdout = true;

  ceres::Solver::Summary summary;
  Solve(options, &problem, &summary);

  printf("%s\n", summary.FullReport().c_str());
  printf("(dx,dy,theta) = (%f,%f,%f)\n", translation[0], translation[1],
         rotation[0]);
  printf("error = %f\n", std::sqrt(summary.final_cost * 2 / (data.size() - 1)));

  return 0;
}