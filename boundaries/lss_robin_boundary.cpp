#include "lss_robin_boundary.hpp"

namespace lss_boundary
{
robin_boundary_1d::robin_boundary_1d(const std::function<double(double)> &linear_value,
                                     const std::function<double(double)> &value)
    : boundary_1d(linear_value, value)
{
}

double robin_boundary_1d::linear_value(double time) const
{
    return this->linear_(time);
}
double robin_boundary_1d::value(double time) const
{
    return this->const_(time);
}

robin_boundary_2d::robin_boundary_2d(const std::function<double(double, double)> &linear_value,
                                     const std::function<double(double, double)> &value)
    : boundary_2d(linear_value, value)
{
}

double robin_boundary_2d::linear_value(double time, double space_arg) const
{
    return this->linear_(time, space_arg);
}
double robin_boundary_2d::value(double time, double space_arg) const
{
    return this->const_(time, space_arg);
}
} // namespace lss_boundary
