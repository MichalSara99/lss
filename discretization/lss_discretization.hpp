/**

    @file      lss_discretization.hpp
    @brief     Represents discretizations
    @details   ~
    @author    Michal Sara
    @date      14.12.2021
    @copyright © Michal Sara, 2021. All right reserved.

**/
#pragma once
#if !defined(_LSS_DISCRETIZATION_HPP_)
#define _LSS_DISCRETIZATION_HPP_

#include <functional>

#include "../common/lss_enumerations.hpp"
#include "../common/lss_utility.hpp"
#include "../containers/lss_container_2d.hpp"
#include "../containers/lss_container_3d.hpp"
#include "lss_grid.hpp"
#include "lss_grid_config.hpp"

using lss_containers::container_2d;
using lss_containers::container_3d;
using lss_enumerations::by_enum;
using lss_enumerations::dimension_enum;
using lss_grids::grid_config_1d_ptr;
using lss_grids::grid_config_2d_ptr;
using lss_grids::grid_config_3d_ptr;

/**
    1D discretization structure
 */
template <template <typename, typename> typename container, typename allocator> struct discretization_1d
{
  public:
    /**
     * Discretize 1D space
     *
     * \param grid_config - 1D grid config object
     * \param container_x - 1D container for output
     */
    static void of_space(grid_config_1d_ptr const &grid_config, container<double, allocator> &container_x); //!<

    /**
     * Discretize function F(x) where x = first dim variable
     *
     * \param grid_config - 1D grid config object
     * \param fun - function F(x)
     * \param container_fun - 1D container for output
     */
    static void of_function(grid_config_1d_ptr const &grid_config, std::function<double(double)> const &fun,
                            container<double, allocator> &container_fun);

    /**
     * Discretize function F(t,x) where t = time, x = first dim variable
     *
     * \param grid_config - 1D grid config object
     * \param time - time valraible t
     * \param fun - function F(t,x)
     * \param container_fun_t = 1D container for output
     */
    static void of_function(grid_config_1d_ptr const &grid_config, double const &time,
                            std::function<double(double, double)> const &fun,
                            container<double, allocator> &container_fun_t);
};

/**
    2D discretization structure
 */
template <template <typename, typename> typename container, typename allocator> struct discretization_2d
{
  public:
    /**
     * Discretize function F(x,y) where x=first dim variable,
     *  y = second dim variable
     *
     * \param grid_config - 2D grid config object
     * \param fun - function F(x,y)
     * \param container_fun - 2D container for output
     */
    static void of_function(grid_config_2d_ptr const &grid_config, std::function<double(double, double)> const &fun,
                            container_2d<by_enum::Row> &container_fun);

    /**
     * Discretize function F(t,x,y) where t=time, x=first dim variable,
     *  y = second dim variable
     *
     * \param grid_config - 2D grid config object
     * \param time  - time valraible t
     * \param fun - function F(t,x,y)
     * \param container_fun_t - 2D container for output
     */
    static void of_function(grid_config_2d_ptr const &grid_config, double const &time,
                            std::function<double(double, double, double)> const &fun,
                            container_2d<by_enum::Row> &container_fun_t);
    /**
     * Discretize function F(t,x,y) where t=time, x=first dim variable,
     *  y = second dim variable
     *
     * \param grid_config - 2D grid config object
     * \param time - time valraible t
     * \param fun - function F(t,x,y)
     * \param rows - number of rows of the output
     * \param cols - number of columns of the output
     * \param cont - 1D container for output (row-wise)
     */

    static void of_function(grid_config_2d_ptr const &grid_config, double const &time,
                            std::function<double(double, double, double)> const &fun, std::size_t const &rows,
                            std::size_t const &cols, container<double, allocator> &cont);
};

/**
    3D discretization structure
 */
template <template <typename, typename> typename container, typename allocator> struct discretization_3d
{
  public:
    /**
     * Discretize function F(x,y,z) where x=first dim variable,
     *  y = second dim variable, z = third dim variable
     *
     * \param grid_config - 3D grid config object
     * \param fun - function F(x,y,z)
     * \param container_fun - 3D container for output
     */
    static void of_function(grid_config_3d_ptr const &grid_config,
                            std::function<double(double, double, double)> const &fun,
                            container_3d<by_enum::Row> &container_fun);

    /**
     * Discretize function F(t,x,y,z) where t=time, x=first dim variable,
     *  y = second dim variable, z = third dim variable
     *
     * \param grid_config - 3D grid config object
     * \param time  - time valraible t
     * \param fun - function F(t,x,y,z)
     * \param container_fun_t - 3D container for output
     */
    static void of_function(grid_config_3d_ptr const &grid_config, double const &time,
                            std::function<double(double, double, double, double)> const &fun,
                            container_3d<by_enum::Row> &container_fun_t);
};

#endif ///_LSS_DISCRETIZATION_HPP_
