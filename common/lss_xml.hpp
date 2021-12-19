#pragma once
#if !defined(_LSS_XML_HPP_)
#define _LSS_XML_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>

#include "../common/lss_enumerations.hpp"
#include "../containers/lss_container_2d.hpp"
#include "../discretization/lss_discretization_config.hpp"
#include "../discretization/lss_grid_config_hints.hpp"
#include "../ode_solvers/lss_ode_discretization_config.hpp"
#include "../pde_solvers/lss_pde_discretization_config.hpp"

namespace lss_xml
{

using lss_containers::container_2d;
using lss_discretization::discretization_config_1d_ptr;
using lss_enumerations::by_enum;
using lss_grids::grid_config_hints_1d_ptr;
using lss_grids::grid_config_hints_2d_ptr;
using lss_ode_solvers::ode_discretization_config_ptr;
using lss_pde_solvers::pde_discretization_config_1d_ptr;
using lss_pde_solvers::pde_discretization_config_2d_ptr;
using lss_utility::container_t;

/**
    @brief Creates an xml from container using passed discretization and grid hints
    @param discretization_cfg
    @param grid_config_hints
    @param container
    @param out
**/
extern void xml(discretization_config_1d_ptr const &discretization_config,
                grid_config_hints_1d_ptr const &grid_config_hints, container_t const &container,
                std::ostream &out = std::cout);

/**
    @brief Prints contents of the container using passed discretization and grid hints
    @param pde_discretization_config
    @param grid_config_hints
    @param container
    @param out
**/
extern void xml(pde_discretization_config_1d_ptr const &pde_discretization_config,
                grid_config_hints_1d_ptr const &grid_config_hints, container_2d<by_enum::Row> const &container,
                std::ostream &out = std::cout);

/**
    @brief Prints contents of the container using passed discretization and grid hints
    @param pde_discretization_config
    @param grid_config_hints
    @param container
    @param out
**/
extern void xml(pde_discretization_config_2d_ptr const &pde_discretization_config,
                grid_config_hints_2d_ptr const &grid_config_hints, container_2d<by_enum::Row> const &container,
                std::ostream &out = std::cout);

} // namespace lss_xml

#endif ///_LSS_XML_HPP_
