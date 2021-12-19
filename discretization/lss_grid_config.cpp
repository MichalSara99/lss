#include "lss_grid_config.hpp"

namespace lss_grids
{

grid_config_1d::grid_config_1d(discretization_config_1d_ptr const &discretization_config)
{
    auto const one = static_cast<double>(1.0);
    step_ = one / (discretization_config->number_of_space_points() - 1);
}

double grid_config_1d::step() const
{
    return step_;
}

std::size_t grid_config_1d::index_of(double zeta)
{
    return static_cast<std::size_t>(zeta / step_);
}

double grid_config_1d::value_for(std::size_t idx)
{
    return (step_ * idx);
}

grid_config_2d::grid_config_2d(pde_discretization_config_2d_ptr const &discretization_config)
{
    auto const one = static_cast<double>(1.0);
    step_1_ = one / (discretization_config->number_of_space_points().first - 1);
    step_2_ = one / (discretization_config->number_of_space_points().second - 1);
    grid_1_ = std::make_shared<grid_config_1d>(discretization_config->pde_discretization_1());
    grid_2_ = std::make_shared<grid_config_1d>(discretization_config->pde_discretization_2());
}

grid_config_1d_ptr const &grid_config_2d::grid_1() const
{
    return grid_1_;
};

grid_config_1d_ptr const &grid_config_2d::grid_2() const
{
    return grid_2_;
}

double grid_config_2d::step_1() const
{
    return step_1_;
}

double grid_config_2d::step_2() const
{
    return step_2_;
}

std::size_t grid_config_2d::index_of_1(double zeta)
{
    return static_cast<std::size_t>(zeta / step_1_);
}

std::size_t grid_config_2d::index_of_2(double eta)
{
    return static_cast<std::size_t>(eta / step_2_);
}

double grid_config_2d::value_for_1(std::size_t idx)
{
    return (step_1_ * idx);
}

double grid_config_2d::value_for_2(std::size_t idx)
{
    return (step_2_ * idx);
}

} // namespace lss_grids
