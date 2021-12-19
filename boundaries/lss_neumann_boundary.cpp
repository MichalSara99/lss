#include "lss_neumann_boundary.hpp"

namespace lss_boundary
{
neumann_boundary_1d::neumann_boundary_1d(const std::function<double(double)> &value) : boundary_1d(nullptr, value)
{
}

double neumann_boundary_1d::value(double time) const
{
    return this->const_(time);
}

neumann_boundary_2d::neumann_boundary_2d(const std::function<double(double, double)> &value)
    : boundary_2d(nullptr, value)
{
}

double neumann_boundary_2d::value(double time, double space_arg) const
{
    return this->const_(time, space_arg);
}
} // namespace lss_boundary
