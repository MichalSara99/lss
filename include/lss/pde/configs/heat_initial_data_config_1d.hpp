#if !defined(_HEAT_INITIAL_DATA_CONFIG_1D_HPP_)
#define _HEAT_INITIAL_DATA_CONFIG_1D_HPP_

#include <functional>

#include "../../../../common/lss_enumerations.hpp"
#include "../../../../common/lss_macros.hpp"
#include "../../../../common/lss_utility.hpp"
#include "../../../../pde_solvers/lss_heat_data_config.hpp"

namespace lss
{

using heat_initial_data_config_1d = lss_pde_solvers::heat_initial_data_config_1d;
using heat_initial_data_config_1d_ptr = lss_pde_solvers::sptr_t<lss_pde_solvers::heat_initial_data_config_1d>;

struct heat_initial_data_config_1d_builder
{
  private:
    std::function<double(double)> initial_condition_;

  public:
    LSS_API explicit heat_initial_data_config_1d_builder();

    LSS_API heat_initial_data_config_1d_builder &initial_condition(
        std::function<double(double)> const &initial_condition);

    LSS_API heat_initial_data_config_1d_ptr build();
};

} // namespace lss

#endif ///_HEAT_INITIAL_DATA_CONFIG_1D_HPP_
