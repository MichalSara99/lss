#include "lss_heat_equation_implicit_kernel.hpp"

#include "../../../boundaries/lss_boundary.hpp"
#include "../../../common/lss_enumerations.hpp"
#include "../../../common/lss_utility.hpp"
#include "../../../containers/lss_container_2d.hpp"
#include "../../../discretization/lss_grid_config.hpp"
#include "../../../sparse_solvers/tridiagonal/cuda_solver/lss_cuda_solver.hpp"
#include "../../../sparse_solvers/tridiagonal/double_sweep_solver/lss_double_sweep_solver.hpp"
#include "../../../sparse_solvers/tridiagonal/sor_solver/lss_sor_solver.hpp"
#include "../../../sparse_solvers/tridiagonal/sor_solver_cuda/lss_sor_solver_cuda.hpp"
#include "../../../sparse_solvers/tridiagonal/thomas_lu_solver/lss_thomas_lu_solver.hpp"
#include "solver_method/lss_heat_implicit_solver_method.hpp"
#include "time_loop/lss_implicit_time_loop.hpp"

namespace lss_pde_solvers
{
namespace one_dimensional
{

using lss_cuda_solver::cuda_solver;
using lss_double_sweep_solver::double_sweep_solver;
using lss_sor_solver::sor_solver;
using lss_sor_solver_cuda::sor_solver_cuda;
using lss_thomas_lu_solver::thomas_lu_solver;

heat_equation_implicit_kernel<memory_space_enum::Device, tridiagonal_method_enum::CUDASolver>::
    heat_equation_implicit_kernel(boundary_1d_pair const &boundary_pair,
                                  heat_data_transform_1d_ptr const &heat_data_config,
                                  pde_discretization_config_1d_ptr const &discretization_config,
                                  heat_implicit_solver_config_ptr const &solver_config,
                                  grid_config_1d_ptr const &grid_config)
    : boundary_pair_{boundary_pair}, heat_data_cfg_{heat_data_config}, discretization_cfg_{discretization_config},
      solver_cfg_{solver_config}, grid_cfg_{grid_config}
{
}

void heat_equation_implicit_kernel<memory_space_enum::Device, tridiagonal_method_enum::CUDASolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<cuda_solver<memory_space_enum::Device>>(space_size);
    solver->set_factorization(solver_cfg_->tridiagonal_factorization());
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);

    if (is_heat_sourse_set)
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, heat_source,
                                solution);
    }
    else
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, solution);
    }
}

void heat_equation_implicit_kernel<memory_space_enum::Device, tridiagonal_method_enum::CUDASolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    container_2d<by_enum::Row> &solutions)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<cuda_solver<memory_space_enum::Device>>(space_size);
    solver->set_factorization(solver_cfg_->tridiagonal_factorization());
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              heat_source, solution, solutions);
    }
    else
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              solution, solutions);
    }
}

heat_equation_implicit_kernel<memory_space_enum::Device, tridiagonal_method_enum::SORSolver>::
    heat_equation_implicit_kernel(boundary_1d_pair const &boundary_pair,
                                  heat_data_transform_1d_ptr const &heat_data_config,
                                  pde_discretization_config_1d_ptr const &discretization_config,
                                  heat_implicit_solver_config_ptr const &solver_config,
                                  grid_config_1d_ptr const &grid_config)
    : boundary_pair_{boundary_pair}, heat_data_cfg_{heat_data_config}, discretization_cfg_{discretization_config},
      solver_cfg_{solver_config}, grid_cfg_{grid_config}
{
}

void heat_equation_implicit_kernel<memory_space_enum::Device, tridiagonal_method_enum::SORSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    double omega_value)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<sor_solver_cuda>(space_size);
    solver->set_omega(omega_value);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, heat_source,
                                solution);
    }
    else
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, solution);
    }
}

void heat_equation_implicit_kernel<memory_space_enum::Device, tridiagonal_method_enum::SORSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    double omega_value, container_2d<by_enum::Row> &solutions)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<sor_solver_cuda>(space_size);
    solver->set_omega(omega_value);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              heat_source, solution, solutions);
    }
    else
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              solution, solutions);
    }
}

heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::CUDASolver>::
    heat_equation_implicit_kernel(boundary_1d_pair const &boundary_pair,
                                  heat_data_transform_1d_ptr const &heat_data_config,
                                  pde_discretization_config_1d_ptr const &discretization_config,
                                  heat_implicit_solver_config_ptr const &solver_config,
                                  grid_config_1d_ptr const &grid_config)
    : boundary_pair_{boundary_pair}, heat_data_cfg_{heat_data_config}, discretization_cfg_{discretization_config},
      solver_cfg_{solver_config}, grid_cfg_{grid_config}
{
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::CUDASolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<cuda_solver<memory_space_enum::Host>>(space_size);
    solver->set_factorization(solver_cfg_->tridiagonal_factorization());
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, heat_source,
                                solution);
    }
    else
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, solution);
    }
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::CUDASolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    container_2d<by_enum::Row> &solutions)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<cuda_solver<memory_space_enum::Host>>(space_size);
    solver->set_factorization(solver_cfg_->tridiagonal_factorization());
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              heat_source, solution, solutions);
    }
    else
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              solution, solutions);
    }
}

heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::SORSolver>::
    heat_equation_implicit_kernel(boundary_1d_pair const &boundary_pair,
                                  heat_data_transform_1d_ptr const &heat_data_config,
                                  pde_discretization_config_1d_ptr const &discretization_config,
                                  heat_implicit_solver_config_ptr const &solver_config,
                                  grid_config_1d_ptr const &grid_config)
    : boundary_pair_{boundary_pair}, heat_data_cfg_{heat_data_config}, discretization_cfg_{discretization_config},
      solver_cfg_{solver_config}, grid_cfg_{grid_config}
{
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::SORSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    double omega_value)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();

    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<sor_solver>(space_size);
    solver->set_omega(omega_value);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, heat_source,
                                solution);
    }
    else
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, solution);
    }
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::SORSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    double omega_value, container_2d<by_enum::Row> &solutions)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<sor_solver>(space_size);
    solver->set_omega(omega_value);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);
    if (is_heat_sourse_set)
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              heat_source, solution, solutions);
    }
    else
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              solution, solutions);
    }
}

heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::DoubleSweepSolver>::
    heat_equation_implicit_kernel(boundary_1d_pair const &boundary_pair,
                                  heat_data_transform_1d_ptr const &heat_data_config,
                                  pde_discretization_config_1d_ptr const &discretization_config,
                                  heat_implicit_solver_config_ptr const &solver_config,
                                  grid_config_1d_ptr const &grid_config)
    : boundary_pair_{boundary_pair}, heat_data_cfg_{heat_data_config}, discretization_cfg_{discretization_config},
      solver_cfg_{solver_config}, grid_cfg_{grid_config}
{
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::DoubleSweepSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<double_sweep_solver>(space_size);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);

    if (is_heat_sourse_set)
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, heat_source,
                                solution);
    }
    else
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, solution);
    }
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::DoubleSweepSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    container_2d<by_enum::Row> &solutions)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<double_sweep_solver>(space_size);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);

    if (is_heat_sourse_set)
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              heat_source, solution, solutions);
    }
    else
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              solution, solutions);
    }
}

heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::ThomasLUSolver>::
    heat_equation_implicit_kernel(boundary_1d_pair const &boundary_pair,
                                  heat_data_transform_1d_ptr const &heat_data_config,
                                  pde_discretization_config_1d_ptr const &discretization_config,
                                  heat_implicit_solver_config_ptr const &solver_config,
                                  grid_config_1d_ptr const &grid_config)
    : boundary_pair_{boundary_pair}, heat_data_cfg_{heat_data_config}, discretization_cfg_{discretization_config},
      solver_cfg_{solver_config}, grid_cfg_{grid_config}
{
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::ThomasLUSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<thomas_lu_solver>(space_size);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);

    if (is_heat_sourse_set)
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, heat_source,
                                solution);
    }
    else
    {
        implicit_time_loop::run(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir, solution);
    }
}

void heat_equation_implicit_kernel<memory_space_enum::Host, tridiagonal_method_enum::ThomasLUSolver>::operator()(
    container_t &solution, bool is_heat_sourse_set, std::function<double(double, double)> const &heat_source,
    container_2d<by_enum::Row> &solutions)
{
    // get time range:
    auto const &time = discretization_cfg_->time_range();
    // time step:
    const double k = discretization_cfg_->time_step();
    // size of space discretization:
    const std::size_t space_size = discretization_cfg_->number_of_space_points();
    // last time index:
    const std::size_t last_time_idx = discretization_cfg_->number_of_time_points() - 1;
    // save traverse_direction
    const traverse_direction_enum traverse_dir = solver_cfg_->traverse_direction();
    // create a heat coefficient holder:
    auto const heat_coeff_holder = std::make_shared<heat_coefficients>(heat_data_cfg_, discretization_cfg_,
                                                                       solver_cfg_->implicit_pde_scheme_value());
    // create and set up the solver:
    auto const &solver = std::make_shared<thomas_lu_solver>(space_size);
    auto const &solver_method_ptr =
        std::make_shared<heat_implicit_solver_method>(solver, heat_coeff_holder, grid_cfg_, is_heat_sourse_set);

    if (is_heat_sourse_set)
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              heat_source, solution, solutions);
    }
    else
    {
        implicit_time_loop::run_with_stepping(solver_method_ptr, boundary_pair_, time, last_time_idx, k, traverse_dir,
                                              solution, solutions);
    }
}

} // namespace one_dimensional

} // namespace lss_pde_solvers
