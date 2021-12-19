#include "lss_heat_solver_config.hpp"

namespace lss_pde_solvers
{

heat_implicit_solver_config::heat_implicit_solver_config(memory_space_enum const &memory_space,
                                                         traverse_direction_enum const &traverse_direction,
                                                         tridiagonal_method_enum const &tridiagonal_method,
                                                         factorization_enum const &tridiagonal_factorization,
                                                         implicit_pde_schemes_enum const &implicit_pde_scheme)
    : pde_implicit_solver_config{memory_space, traverse_direction, tridiagonal_method, tridiagonal_factorization},
      implicit_pde_scheme_{implicit_pde_scheme}
{
}

heat_implicit_solver_config ::~heat_implicit_solver_config()
{
}

implicit_pde_schemes_enum heat_implicit_solver_config::implicit_pde_scheme() const
{
    return implicit_pde_scheme_;
}

heat_explicit_solver_config::heat_explicit_solver_config(memory_space_enum const &memory_space,
                                                         traverse_direction_enum const &traverse_direction,
                                                         explicit_pde_schemes_enum const &explicit_pde_scheme)
    : pde_explicit_solver_config{memory_space, traverse_direction}, explicit_pde_scheme_{explicit_pde_scheme}
{
}

heat_explicit_solver_config::~heat_explicit_solver_config()
{
}

explicit_pde_schemes_enum heat_explicit_solver_config::explicit_pde_scheme() const
{
    return explicit_pde_scheme_;
}
} // namespace lss_pde_solvers
