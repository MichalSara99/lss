#include "lss_boundary.hpp"

namespace lss_boundary
{

boundary_1d::boundary_1d(const std::function<double(double)> &linear, const std::function<double(double)> &constant)
    : linear_{linear}, const_{constant}
{
}

boundary_1d::~boundary_1d()
{
}

boundary_2d::boundary_2d(const std::function<double(double, double)> &linear,
                         const std::function<double(double, double)> &constant)
    : linear_{linear}, const_{constant}
{
}

boundary_2d ::~boundary_2d()
{
}

} // namespace lss_boundary
