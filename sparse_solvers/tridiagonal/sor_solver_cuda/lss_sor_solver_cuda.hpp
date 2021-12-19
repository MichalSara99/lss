#pragma once
#if !defined(_LSS_SOR_SOLVER_CUDA_HPP_)
#define _LSS_SOR_SOLVER_CUDA_HPP_

#include "../../../boundaries/lss_boundary.hpp"
#include "../../../common/lss_utility.hpp"
#include "../lss_tridiagonal_solver.hpp"
#include "lss_sor_cuda_boundary.hpp"

namespace lss_sor_solver_cuda
{

using lss_boundary::boundary_1d_pair;
using lss_boundary::boundary_2d_pair;
using lss_enumerations::factorization_enum;
using lss_utility::container_t;
using lss_utility::sptr_t;

class sor_solver_cuda : public lss_tridiagonal_solver::tridiagonal_solver
{
  private:
    sor_cuda_boundary_ptr sor_boundary_;

    void kernel(boundary_1d_pair const &boundary, container_t &solution, factorization_enum factorization,
                double time) override;

    void kernel(boundary_2d_pair const &boundary, container_t &solution, factorization_enum factorization, double time,
                double space_args) override;

    void initialize();

    explicit sor_solver_cuda() = delete;

  public:
    explicit sor_solver_cuda(std::size_t discretization_size);

    ~sor_solver_cuda();

    sor_solver_cuda(sor_solver_cuda const &) = delete;
    sor_solver_cuda(sor_solver_cuda &&) = delete;
    sor_solver_cuda &operator=(sor_solver_cuda const &) = delete;
    sor_solver_cuda &operator=(sor_solver_cuda &&) = delete;
};

using sor_solver_cuda_ptr = sptr_t<sor_solver_cuda>;

} // namespace lss_sor_solver_cuda
#endif ///_LSS_SOR_SOLVER_CUDA_HPP_
