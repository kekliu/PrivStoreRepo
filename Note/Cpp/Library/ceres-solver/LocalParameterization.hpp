// Purpose: Sometimes parameter blocks x can overparameterize a problem
//
//   min f(x)
//    x
//
// In that case it is desirable to choose a parameterization for the
// block itself to remove the null directions of the cost. More
// generally, if x lies on a manifold of a smaller dimension than the
// ambient space that it is embedded in, then it is numerically and
// computationally more effective to optimize it using a
// parameterization that lives in the tangent space of that manifold
// at each point.
//
// For example, a sphere in three dimensions is a 2 dimensional
// manifold, embedded in a three dimensional space. At each point on
// the sphere, the plane tangent to it defines a two dimensional
// tangent space. For a cost function defined on this sphere, given a
// point x, moving in the direction normal to the sphere at that point
// is not useful. Thus a better way to do a local optimization is to
// optimize over two dimensional vector delta in the tangent space at
// that point and then "move" to the point x + delta, where the move
// operation involves projecting back onto the sphere. Doing so
// removes a redundent dimension from the optimization, making it
// numerically more robust and efficient.
//
// More generally we can define a function
//
//   x_plus_delta = Plus(x, delta),
//
// where x_plus_delta has the same size as x, and delta is of size
// less than or equal to x. The function Plus, generalizes the
// definition of vector addition. Thus it satisfies the identify
//
//   Plus(x, 0) = x, for all x.
//
// A trivial version of Plus is when delta is of the same size as x
// and
//
//   Plus(x, delta) = x + delta
//
// A more interesting case if x is two dimensional vector, and the
// user wishes to hold the first coordinate constant. Then, delta is a
// scalar and Plus is defined as
//
//   Plus(x, delta) = x + [0] * delta
//                        [1]
//
// An example that occurs commonly in Structure from Motion problems
// is when camera rotations are parameterized using Quaternion. There,
// it is useful only make updates orthogonal to that 4-vector defining
// the quaternion. One way to do this is to let delta be a 3
// dimensional vector and define Plus to be
//
//   Plus(x, delta) = [cos(|delta|), sin(|delta|) delta / |delta|] * x
//
// The multiplication between the two 4-vectors on the RHS is the
// standard quaternion product.
//
// Given g and a point x, optimizing f can now be restated as
//
//     min  f(Plus(x, delta))
//    delta
//
// Given a solution delta to this problem, the optimal value is then
// given by
//
//   x* = Plus(x, delta)
//
// The class LocalParameterization defines the function Plus and its
// Jacobian which is needed to compute the Jacobian of f w.r.t delta.

/**
 * 自定义参数化类
 * 抽象类， GlobalSize LocalSize Plus ComputeJacobian 必须被子类实现
 * 定义
 *   x_plus_delta = Plus(x, delta)
 * 其中，x维度为GlobalSize，delta维度为LocalSize，delta为x构成的流形的正切空间维度
 *   JacobianMatrix = ComputeJacobian(x)
 *                  = \frac{\partial Plus(x, delta)}{\partial delta} @ delta->0
 */
class LocalParameterization {
 public:
  virtual ~LocalParameterization();

  /**
   * 自定义Plus函数
   *   x_plus_delta = Plus(x, delta)
   * 条件: Plus(x, 0) = x
   */
  virtual bool Plus(const double* x,
                    const double* delta,
                    double* x_plus_delta) const = 0;

  /**
   * 计算 Plus(x, delta) 在 delta=0 处的雅克比矩阵，大小为 GlobalSize x LocalSize
   * 用途: 已知 delta_x 的情况下计算 delta，公式为 delta = delta_x * jacobian
   */
  virtual bool ComputeJacobian(const double* x, double* jacobian) const = 0;

  /**
   * local_matrix = global_matrix * jacobian
   * 该函数只会被 GradientProblem 使用，大部分时候使用默认的实现即可
   */
  virtual bool MultiplyByJacobian(const double* x,
                                  const int num_rows,
                                  const double* global_matrix,
                                  double* local_matrix) const;

  // x 的元素个数
  virtual int GlobalSize() const = 0;

  // delta 的元素个数
  virtual int LocalSize() const = 0;
};

// Some basic parameterizations

// Plus(x, delta) = x + delta
class IdentityParameterization : public LocalParameterization { };

// 一部分参数为常量
class SubsetParameterization : public LocalParameterization { };

// Plus(x, delta) = [cos(|delta|), sin(|delta|) delta / |delta|] * x
// ceres内部的四元数，顺序为 w x y z
class QuaternionParameterization : public LocalParameterization { };

// Plus(x, delta) = [sin(|delta|) delta / |delta|, cos(|delta|)] * x
// Eigen库中的四元数，顺序为 x y z w
class EigenQuaternionParameterization : public LocalParameterization { };
