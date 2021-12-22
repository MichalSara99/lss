/**

    @file      lss_boundary.hpp
    @brief     represents general 1D and 2D boundary
    @details   ~
    @author    Michal Sara
    @date      14.12.2021
    @copyright � Michal Sara, 2021. All right reserved.

**/

#pragma once
#if !defined(_LSS_BOUNDARY_HPP_)
#define _LSS_BOUNDARY_HPP_

#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"
#include <functional>

namespace lss_boundary
{

using lss_utility::sptr_t;

/**

    @class   boundary_1d
    @brief   represents general 1D boundary
    @details ~

**/
class boundary_1d
{
  protected:
    double linear_val_, const_val_;
    std::function<double(double)> linear_fun_{nullptr};
    std::function<double(double)> const_fun_{nullptr};
    bool is_time_dependent_{true};

    explicit boundary_1d() = delete;

  public:
    explicit boundary_1d(double linear, double constant);

    explicit boundary_1d(const std::function<double(double)> &linear, const std::function<double(double)> &constant);

    virtual ~boundary_1d();

    bool const &is_time_dependent() const;

    LSS_API virtual double value(double time) const = 0;

    LSS_API virtual double value() const = 0;
};

using boundary_1d_ptr = sptr_t<boundary_1d>;
using boundary_1d_pair = std::pair<boundary_1d_ptr, boundary_1d_ptr>;

/**

    @class   boundary_2d
    @brief   represents general 2D boundary
    @details ~

**/
class boundary_2d
{
  protected:
    std::function<double(double, double)> linear_;
    std::function<double(double, double)> const_;

    explicit boundary_2d() = delete;

  public:
    explicit boundary_2d(const std::function<double(double, double)> &linear,
                         const std::function<double(double, double)> &constant);

    virtual ~boundary_2d();

    LSS_API virtual double value(double time, double space_arg) const = 0;
};

using boundary_2d_ptr = sptr_t<boundary_2d>;
using boundary_2d_pair = std::pair<boundary_2d_ptr, boundary_2d_ptr>;

} // namespace lss_boundary

#endif ///_LSS_BOUNDARY_HPP_
