#include "lss_dirichlet_boundary.hpp"

namespace lss_boundary
{
dirichlet_boundary_1d::dirichlet_boundary_1d(const std::function<double(double)> &value) : boundary_1d(nullptr, value)
{
}

double dirichlet_boundary_1d::value(double time) const
{
    return this->const_(time);
}

dirichlet_boundary_2d::dirichlet_boundary_2d(const std::function<double(double, double)> &value)
    : boundary_2d(nullptr, value)
{
}

double dirichlet_boundary_2d::value(double time, double space_arg) const
{
    return this->const_(time, space_arg);
}

} // namespace lss_boundary
