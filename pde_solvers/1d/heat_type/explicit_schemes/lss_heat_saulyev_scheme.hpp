#if !defined(_LSS_HEAT_SAULYEV_SCHEME_HPP_)
#define _LSS_HEAT_SAULYEV_SCHEME_HPP_

#include "../../../../boundaries/lss_boundary.hpp"
#include "../../../../common/lss_range.hpp"
#include "../../../../common/lss_utility.hpp"
#include "../../../../containers/lss_container_2d.hpp"
#include "../../../../discretization/lss_grid_config.hpp"
#include "../explicit_coefficients/lss_heat_saulyev_coefficients.hpp"
#include "../time_loop/lss_explicit_time_loop.hpp"

namespace lss_pde_solvers
{

namespace one_dimensional
{

using lss_boundary::boundary_1d_pair;
using lss_boundary::boundary_1d_ptr;
using lss_containers::container_2d;
using lss_enumerations::traverse_direction_enum;
using lss_utility::container_t;
using lss_utility::NaN;
using lss_utility::range_ptr;

using container_2d_t = container_2d<by_enum::Row>;

class heat_saulyev_scheme
{

  private:
    heat_saulyev_coefficients_ptr s_coeffs_;
    boundary_1d_pair boundary_pair_;
    pde_discretization_config_1d_ptr discretization_cfg_;
    grid_config_1d_ptr grid_cfg_;

    void initialize(heat_coefficients_ptr const &coefficients);

    explicit heat_saulyev_scheme() = delete;

  public:
    heat_saulyev_scheme(heat_coefficients_ptr const &coefficients, boundary_1d_pair const &boundary_pair,
                        pde_discretization_config_1d_ptr const &discretization_config,
                        grid_config_1d_ptr const &grid_config);

    ~heat_saulyev_scheme();

    void operator()(container_t &solution, bool is_heat_sourse_set,
                    std::function<double(double, double)> const &heat_source, traverse_direction_enum traverse_dir);

    void operator()(container_t &solution, bool is_heat_sourse_set,
                    std::function<double(double, double)> const &heat_source, traverse_direction_enum traverse_dir,
                    container_2d<by_enum::Row> &solutions);
};

} // namespace one_dimensional

} // namespace lss_pde_solvers

#endif ///_LSS_HEAT_SAULYEV_SCHEME_HPP_
