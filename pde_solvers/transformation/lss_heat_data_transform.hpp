#if !defined(_LSS_HEAT_DATA_TRANSFORM_HPP_)
#define _LSS_HEAT_DATA_TRANSFORM_HPP_

#include <functional>

#include "../../common/lss_enumerations.hpp"
#include "../../common/lss_macros.hpp"
#include "../../common/lss_utility.hpp"
#include "../../discretization/lss_grid.hpp"
#include "../../discretization/lss_grid_transform_config.hpp"
#include "../lss_heat_data_config.hpp"

namespace lss_pde_solvers
{

using lss_enumerations::dimension_enum;
using lss_grids::grid_1d;
using lss_grids::grid_2d;
using lss_grids::grid_transform_config_1d_ptr;
using lss_grids::grid_transform_config_2d_ptr;
using lss_utility::range;
using lss_utility::sptr_t;

/**
    1D heat_data_transform structure
 */
struct heat_data_transform_1d
{
  private:
    bool is_heat_source_set_{false};
    std::function<double(double, double)> a_coeff_{nullptr};
    std::function<double(double, double)> b_coeff_{nullptr};
    std::function<double(double, double)> c_coeff_{nullptr};
    std::function<double(double)> init_coeff_{nullptr};
    std::function<double(double, double)> src_coeff_{nullptr};

    void initialize(heat_data_config_1d_ptr const &heat_data_config,
                    grid_transform_config_1d_ptr const grid_transform_config);

    explicit heat_data_transform_1d() = delete;

  public:
    explicit heat_data_transform_1d(heat_data_config_1d_ptr const &heat_data_config,
                                    grid_transform_config_1d_ptr const grid_transform_config);

    ~heat_data_transform_1d();

    bool const &is_heat_source_set() const;

    std::function<double(double, double)> heat_source() const;

    std::function<double(double)> const &initial_condition() const;

    std::function<double(double, double)> const &a_coefficient() const;

    std::function<double(double, double)> const &b_coefficient() const;

    std::function<double(double, double)> const &c_coefficient() const;
};

/**
    2D heat_data_transform structure
 */
struct heat_data_transform_2d
{
  private:
    bool is_heat_source_set_{false};
    std::function<double(double, double, double)> a_coeff_{nullptr};
    std::function<double(double, double, double)> b_coeff_{nullptr};
    std::function<double(double, double, double)> c_coeff_{nullptr};
    std::function<double(double, double, double)> d_coeff_{nullptr};
    std::function<double(double, double, double)> e_coeff_{nullptr};
    std::function<double(double, double, double)> f_coeff_{nullptr};
    std::function<double(double, double)> init_coeff_{nullptr};
    std::function<double(double, double, double)> src_coeff_{nullptr};

    void initialize(heat_data_config_2d_ptr const &heat_data_config,
                    grid_transform_config_2d_ptr const &grid_transform_config);

    explicit heat_data_transform_2d() = delete;

  public:
    explicit heat_data_transform_2d(heat_data_config_2d_ptr const &heat_data_config,
                                    grid_transform_config_2d_ptr const &grid_transform_config);

    ~heat_data_transform_2d();

    bool const &is_heat_source_set() const;

    std::function<double(double, double, double)> heat_source() const;

    std::function<double(double, double)> const &initial_condition() const;

    std::function<double(double, double, double)> const &a_coefficient() const;

    std::function<double(double, double, double)> const &b_coefficient() const;

    std::function<double(double, double, double)> const &c_coefficient() const;

    std::function<double(double, double, double)> const &d_coefficient() const;

    std::function<double(double, double, double)> const &e_coefficient() const;

    std::function<double(double, double, double)> const &f_coefficient() const;
};

using heat_data_transform_1d_ptr = sptr_t<heat_data_transform_1d>;

using heat_data_transform_2d_ptr = sptr_t<heat_data_transform_2d>;

} // namespace lss_pde_solvers

#endif ///_LSS_HEAT_DATA_TRANSFORM_HPP_
