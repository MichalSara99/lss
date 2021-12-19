#include "lss_print.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <tuple>

#include "../discretization/lss_grid.hpp"
#include "../discretization/lss_grid_config.hpp"
#include "../discretization/lss_grid_transform_config.hpp"

namespace lss_print
{
using lss_grids::grid_1d;
using lss_grids::grid_2d;
using lss_grids::grid_config_1d;
using lss_grids::grid_config_2d;
using lss_grids::grid_transform_config_1d;
using lss_grids::grid_transform_config_2d;

void print(discretization_config_1d_ptr const &discretization_config, grid_config_hints_1d_ptr const &grid_hints_cfg,
           container_t const &container, std::ostream &out)
{
    const std::size_t space_size = discretization_config->number_of_space_points();
    LSS_ASSERT(container.size() == space_size, "Container size differs from passed discretization");
    // create grid_config:
    auto const &grid_cfg = std::make_shared<grid_config_1d>(discretization_config);
    // create grid_transform_config:
    auto const &grid_trans_cfg = std::make_shared<grid_transform_config_1d>(discretization_config, grid_hints_cfg);
    double zeta{};
    out << "SPACE_POINTS\n";
    for (std::size_t t = 0; t < space_size - 1; ++t)
    {
        zeta = grid_1d::value(grid_cfg, t);
        out << grid_1d::transformed_value(grid_trans_cfg, zeta);
        out << ",";
    }
    zeta = grid_1d::value(grid_cfg, space_size - 1);
    out << grid_1d::transformed_value(grid_trans_cfg, zeta) << "\nVALUES\n";
    for (std::size_t t = 0; t < space_size - 1; ++t)
    {
        out << container[t];
        out << ",";
    }
    out << container[space_size - 1];
}

void print(pde_discretization_config_2d_ptr const &pde_discretization_config,
           grid_config_hints_2d_ptr const &grid_config_hints, container_2d<by_enum::Row> const &container,
           std::ostream &out)
{
    const auto &space_sizes = pde_discretization_config->number_of_space_points();
    LSS_ASSERT((container.columns() == std::get<1>(space_sizes)) && (container.rows() == std::get<0>(space_sizes)),
               "The input cont container must have the correct size");
    // create grid_config:
    auto const &grid_cfg = std::make_shared<grid_config_2d>(pde_discretization_config);
    // create grid_transform_config:
    auto const &grid_trans_cfg =
        std::make_shared<grid_transform_config_2d>(pde_discretization_config, grid_config_hints);
    double zeta{}, eta{};
    out << "SPACE_POINTS_X\n";
    for (std::size_t t = 0; t < space_sizes.first - 1; ++t)
    {
        zeta = grid_2d::value_1(grid_cfg, t);
        out << grid_2d::transformed_value_1(grid_trans_cfg, zeta);
        out << ",";
    }
    zeta = grid_2d::value_1(grid_cfg, space_sizes.first - 1);
    out << grid_2d::transformed_value_1(grid_trans_cfg, zeta) << "\nSPACE_POINTS_Y\n";
    for (std::size_t t = 0; t < space_sizes.second - 1; ++t)
    {
        eta = grid_2d::value_2(grid_cfg, t);
        out << grid_2d::transformed_value_2(grid_trans_cfg, eta);
        out << ",";
    }
    eta = grid_2d::value_2(grid_cfg, space_sizes.second - 1);
    out << grid_2d::transformed_value_2(grid_trans_cfg, eta) << "\nVALUES\n";
    for (std::size_t r = 0; r < container.rows(); ++r)
    {
        for (std::size_t c = 0; c < container.columns() - 1; ++c)
        {
            out << container(r, c);
            out << ",";
        }
        out << container(r, container.columns() - 1);
        out << "\n";
    }
}

void print(pde_discretization_config_1d_ptr const &pde_discretization_config,
           grid_config_hints_1d_ptr const &grid_config_hints, container_2d<by_enum::Row> const &container,
           std::ostream &out)
{
    const std::size_t space_size = pde_discretization_config->number_of_space_points();
    const std::size_t time_size = pde_discretization_config->number_of_time_points();
    LSS_ASSERT((container.columns() == space_size) && (container.rows() == time_size),
               "Container size differs from passed discretization");

    // create grid_config:
    auto const &grid_cfg = std::make_shared<grid_config_1d>(pde_discretization_config);
    // create grid_transform_config:
    auto const &grid_trans_cfg =
        std::make_shared<grid_transform_config_1d>(pde_discretization_config, grid_config_hints);

    const double k = pde_discretization_config->time_step();
    const auto &time = pde_discretization_config->time_range();
    const double time_start = time->lower();

    out << "SPACE_POINTS\n";
    double m{}, zeta{};
    for (std::size_t t = 0; t < space_size - 1; ++t)
    {
        zeta = grid_1d::value(grid_cfg, t);
        out << grid_1d::transformed_value(grid_trans_cfg, zeta);
        out << ",";
    }
    zeta = grid_1d::value(grid_cfg, space_size - 1);
    out << grid_1d::transformed_value(grid_trans_cfg, zeta) << "\nTIME_POINTS\n";
    for (std::size_t t = 0; t < time_size - 1; ++t)
    {
        m = static_cast<double>(t);
        out << (time_start + m * k);
        out << ",";
    }
    m = static_cast<double>(time_size - 1);
    out << (time_start + m * k) << "\nVALUES\n";
    for (std::size_t t = 0; t < time_size; ++t)
    {
        for (std::size_t i = 0; i < space_size - 1; ++i)
        {
            out << container(t, i);
            out << ",";
        }
        out << container(t, space_size - 1);
        out << "\n";
    }
}

} // namespace lss_print
