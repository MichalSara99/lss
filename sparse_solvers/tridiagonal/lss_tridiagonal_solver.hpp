#pragma once
#if !defined(_LSS_TRIDIAGONAL_SOLVER_HPP_)
#define _LSS_TRIDIAGONAL_SOLVER_HPP_

#include "../../boundaries/lss_boundary.hpp"
#include "../../common/lss_enumerations.hpp"
#include "../../common/lss_utility.hpp"

namespace lss_tridiagonal_solver
{

using lss_boundary::boundary_1d_pair;
using lss_boundary::boundary_2d_pair;
using lss_enumerations::factorization_enum;
using lss_utility::container_t;
using lss_utility::sptr_t;

class tridiagonal_solver
{
  protected:
    double omega_;
    container_t a_, b_, c_, f_;
    std::size_t discretization_size_;
    factorization_enum factorization_;

    virtual void kernel(boundary_1d_pair const &boundary, container_t &solution, factorization_enum factorization,
                        double time) = 0;

    virtual void kernel(boundary_2d_pair const &boundary, container_t &solution, factorization_enum factorization,
                        double time, double space_args) = 0;

    tridiagonal_solver() = delete;

  public:
    explicit tridiagonal_solver(std::size_t discretization_size,
                                factorization_enum factorization = factorization_enum::QRMethod);

    void set_diagonals(container_t lower_diagonal, container_t diagonal, container_t upper_diagonal);

    void set_rhs(container_t const &rhs);

    void set_factorization(factorization_enum factorization);

    void set_omega(double value);

    void solve(boundary_1d_pair const &boundary, container_t &solution);

    void solve(boundary_1d_pair const &boundary, container_t &solution, double at_time);

    void solve(boundary_2d_pair const &boundary, container_t &solution, double at_time, double space_arg);
};

using tridiagonal_solver_ptr = sptr_t<tridiagonal_solver>;

} // namespace lss_tridiagonal_solver

#endif ///_LSS_TRIDIAGONAL_SOLVER_HPP_
