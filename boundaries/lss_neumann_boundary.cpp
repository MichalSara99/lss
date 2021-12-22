#include "lss_neumann_boundary.hpp"

namespace lss_boundary
{
neumann_boundary_1d::neumann_boundary_1d(const std::function<double(double)> &value) : boundary_1d(nullptr, value)
{
}

neumann_boundary_1d::neumann_boundary_1d(double value) : boundary_1d(double{}, value)
{
}

double neumann_boundary_1d::value(double time) const
{
    LSS_ASSERT(is_time_dependent_ == true, "neumann_boundary_1d: Boundary must not be time independent.");
    return this->const_fun_(time);
}

double neumann_boundary_1d::value() const
{
    return this->const_val_;
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
