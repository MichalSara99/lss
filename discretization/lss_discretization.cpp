#include "lss_discretization.hpp"
#include "lss_grid.hpp"

#include <thrust/host_vector.h>

using lss_grids::grid_1d;
using lss_grids::grid_2d;
using lss_grids::grid_3d;
using lss_grids::grid_config_1d_ptr;
using lss_grids::grid_config_2d_ptr;
using lss_grids::grid_config_3d_ptr;

// specialization for std::vector:

template <>
void discretization_1d<std::vector, std::allocator<double>>::of_space(
    grid_config_1d_ptr const &grid_config, std::vector<double, std::allocator<double>> &container_x)
{
    LSS_ASSERT(container_x.size() > 0, "The input container must be initialized.");
    for (std::size_t t = 0; t < container_x.size(); ++t)
    {
        container_x[t] = grid_1d::value(grid_config, t);
    }
}

template <>
void discretization_1d<std::vector, std::allocator<double>>::of_function(
    grid_config_1d_ptr const &grid_config, double const &time, std::function<double(double, double)> const &fun,
    std::vector<double, std::allocator<double>> &container_fun_t)
{
    LSS_ASSERT(container_fun_t.size() > 0, "The input container must be initialized.");
    for (std::size_t t = 0; t < container_fun_t.size(); ++t)
    {
        container_fun_t[t] = fun(time, grid_1d::value(grid_config, t));
    }
}

template <>
void discretization_1d<std::vector, std::allocator<double>>::of_function(
    grid_config_1d_ptr const &grid_config, std::function<double(double)> const &fun,
    std::vector<double, std::allocator<double>> &container_fun)
{
    LSS_ASSERT(container_fun.size() > 0, "The input container must be initialized.");
    for (std::size_t t = 0; t < container_fun.size(); ++t)
    {
        container_fun[t] = fun(grid_1d::value(grid_config, t));
    }
}

template <>
void discretization_2d<std::vector, std::allocator<double>>::of_function(
    grid_config_2d_ptr const &grid_config, std::function<double(double, double)> const &fun,
    container_2d<by_enum::Row> &container_fun)
{
    LSS_ASSERT(container_fun.rows() > 0, "The input container must be initialized.");
    LSS_ASSERT(container_fun.columns() > 0, "The input container must be initialized.");
    double value{};
    for (std::size_t r = 0; r < container_fun.rows(); ++r)
    {
        for (std::size_t c = 0; c < container_fun.columns(); ++c)
        {
            value = fun(grid_2d::value_1(grid_config, r), grid_2d::value_2(grid_config, c));
            container_fun(r, c, value);
        }
    }
}

template <>
void discretization_2d<std::vector, std::allocator<double>>::of_function(
    grid_config_2d_ptr const &grid_config, double const &time, std::function<double(double, double, double)> const &fun,
    container_2d<by_enum::Row> &container_fun_t)
{
    LSS_ASSERT(container_fun_t.rows() > 0, "The input container must be initialized.");
    LSS_ASSERT(container_fun_t.columns() > 0, "The input container must be initialized.");
    double value{};
    for (std::size_t r = 0; r < container_fun_t.rows(); ++r)
    {
        for (std::size_t c = 0; c < container_fun_t.columns(); ++c)
        {
            value = fun(time, grid_2d::value_1(grid_config, r), grid_2d::value_2(grid_config, c));
            container_fun_t(r, c, value);
        }
    }
}

template <>
void discretization_2d<std::vector, std::allocator<double>>::of_function(
    grid_config_2d_ptr const &grid_config, double const &time, std::function<double(double, double, double)> const &fun,
    std::size_t const &rows, std::size_t const &cols, std::vector<double, std::allocator<double>> &cont)
{
    LSS_ASSERT(cont.size() > 0, "The input container must be initialized.");
    double value{};
    for (std::size_t r = 0; r < rows; ++r)
    {
        for (std::size_t c = 0; c < cols; ++c)
        {
            value = fun(time, grid_2d::value_1(grid_config, r), grid_2d::value_2(grid_config, c));
            cont[c + r * cols] = value;
        }
    }
}

template <>
void discretization_3d<std::vector, std::allocator<double>>::of_function(
    grid_config_3d_ptr const &grid_config, std::function<double(double, double, double)> const &fun,
    container_3d<by_enum::Row> &container_fun)
{
    LSS_ASSERT(container_fun.rows() > 0, "The input container must be initialized.");
    LSS_ASSERT(container_fun.columns() > 0, "The input container must be initialized.");
    LSS_ASSERT(container_fun.layers() > 0, "The input container must be initialized.");
    double value{};
    for (std::size_t l = 0; l < container_fun.layers(); ++l)
    {
        for (std::size_t r = 0; r < container_fun.rows(); ++r)
        {
            for (std::size_t c = 0; c < container_fun.columns(); ++c)
            {
                value = fun(grid_3d::value_1(grid_config, r), grid_3d::value_2(grid_config, c),
                            grid_3d::value_3(grid_config, l));
                container_fun(r, c, l, value);
            }
        }
    }
}

template <>
void discretization_3d<std::vector, std::allocator<double>>::of_function(
    grid_config_3d_ptr const &grid_config, double const &time,
    std::function<double(double, double, double, double)> const &fun, container_3d<by_enum::Row> &container_fun_t)
{
    LSS_ASSERT(container_fun_t.rows() > 0, "The input container must be initialized.");
    LSS_ASSERT(container_fun_t.columns() > 0, "The input container must be initialized.");
    LSS_ASSERT(container_fun_t.layers() > 0, "The input container must be initialized.");
    double value{};

    for (std::size_t l = 0; l < container_fun_t.layers(); ++l)
    {
        for (std::size_t r = 0; r < container_fun_t.rows(); ++r)
        {
            for (std::size_t c = 0; c < container_fun_t.columns(); ++c)
            {
                value = fun(time, grid_3d::value_1(grid_config, r), grid_3d::value_2(grid_config, c),
                            grid_3d::value_3(grid_config, l));
                container_fun_t(r, c, l, value);
            }
        }
    }
}
