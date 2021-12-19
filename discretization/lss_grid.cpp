#include "lss_grid.hpp"

namespace lss_grids
{

double grid_1d::value(grid_config_1d_ptr const &grid_config, std::size_t const &idx)
{
    return grid_config->value_for(idx);
}

double grid_1d::step(grid_config_1d_ptr const &grid_config)
{
    return grid_config->step();
}

std::size_t grid_1d::index_of(grid_config_1d_ptr const &grid_config, double zeta)
{
    return grid_config->index_of(zeta);
}

double grid_1d::transformed_value(grid_transform_config_1d_ptr const &grid_trans_config, double zeta)
{
    return grid_trans_config->value_for(zeta);
}

double grid_2d::value_1(grid_config_2d_ptr const &grid_config, std::size_t const &idx)
{
    return grid_config->value_for_1(idx);
}

double grid_2d::value_2(grid_config_2d_ptr const &grid_config, std::size_t const &idx)
{
    return grid_config->value_for_2(idx);
}

double grid_2d::step_1(grid_config_2d_ptr const &grid_config)
{
    return grid_config->step_1();
}

double grid_2d::step_2(grid_config_2d_ptr const &grid_config)
{
    return grid_config->step_2();
}

std::size_t grid_2d::index_of_1(grid_config_2d_ptr const &grid_config, double zeta)
{
    return grid_config->index_of_1(zeta);
}

std::size_t grid_2d::index_of_2(grid_config_2d_ptr const &grid_config, double eta)
{
    return grid_config->index_of_2(eta);
}

double grid_2d::transformed_value_1(grid_transform_config_2d_ptr const &grid_trans_config, double zeta)
{
    return grid_trans_config->value_for_1(zeta);
}

double grid_2d::transformed_value_2(grid_transform_config_2d_ptr const &grid_trans_config, double eta)
{
    return grid_trans_config->value_for_2(eta);
}

} // namespace lss_grids
