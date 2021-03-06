#if !defined(_LSS_SPLITTING_METHOD_CONFIG_HPP_)
#define _LSS_SPLITTING_METHOD_CONFIG_HPP_

#include <map>

#include "../common/lss_enumerations.hpp"
#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"

namespace lss_pde_solvers
{

using lss_enumerations::splitting_method_enum;
using lss_utility::sptr_t;

/**
    splitting_method_config structure
 */
struct splitting_method_config
{
  private:
    splitting_method_enum splitting_method_;
    double weighting_value_;

    explicit splitting_method_config() = delete;

  public:
    explicit splitting_method_config(splitting_method_enum splittitng_method, double weighting_value = double(0.5));
    ~splitting_method_config();

    LSS_API splitting_method_enum splitting_method() const;

    LSS_API double weighting_value() const;
};

using splitting_method_config_ptr = sptr_t<splitting_method_config>;

} // namespace lss_pde_solvers

#endif ///_LSS_SPLITTING_METHOD_CONFIG_HPP_
