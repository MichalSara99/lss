#if !defined(_LSS_WAVE_IMPLICIT_COEFFICIENTS_HPP_)
#define _LSS_WAVE_IMPLICIT_COEFFICIENTS_HPP_

#include <functional>

#include "../../../../common/lss_macros.hpp"
#include "../../../../discretization/lss_discretization.hpp"
#include "../../../lss_pde_discretization_config.hpp"
#include "../../../transformation/lss_wave_data_transform.hpp"

namespace lss_pde_solvers
{

namespace one_dimensional
{
using lss_utility::range_ptr;
using lss_utility::sptr_t;

struct wave_implicit_coefficients
{
  public:
    // scheme coefficients:
    double lambda_, gamma_, delta_, rho_, k_;
    std::size_t space_size_;
    range_ptr range_;
    // functional coefficients:
    std::function<double(double, double)> A_;
    std::function<double(double, double)> B_;
    std::function<double(double, double)> C_;
    std::function<double(double, double)> D_;
    std::function<double(double, double)> E_;

  private:
    void initialize(pde_discretization_config_1d_ptr const &discretization_config);

    void initialize_coefficients(wave_data_transform_1d_ptr const &wave_data_config);

  public:
    wave_implicit_coefficients() = delete;

    explicit wave_implicit_coefficients(wave_data_transform_1d_ptr const &wave_data_config,
                                        pde_discretization_config_1d_ptr const &discretization_config);
};

using wave_implicit_coefficients_ptr = sptr_t<wave_implicit_coefficients>;

} // namespace one_dimensional

} // namespace lss_pde_solvers

#endif ///_LSS_WAVE_IMPLICIT_COEFFICIENTS_HPP_
