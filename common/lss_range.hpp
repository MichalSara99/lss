/**

    @file      lss_range.hpp
    @brief     Range utility
    @details   ~
    @author    Michal Sara
    @date      14.12.2021
    @copyright © Michal Sara, 2021. All right reserved.

**/
#pragma once
#if !defined(_LSS_RANGE_HPP_)
#define _LSS_RANGE_HPP_

#include "lss_macros.hpp"
#include "lss_utility.hpp"

namespace lss_utility
{

/**

    @class   range
    @brief   Range object
    @details ~

**/
class range
{
  private:
    double l_, u_;

  public:
    /**
        @brief range object constructor
        @param lower end-point
        @param upper end-point
    **/
    explicit range(double lower, double upper);
    explicit range();

    ~range();

    range(range const &copy);
    range(range &&other) noexcept;

    range &operator=(range const &copy);
    range &operator=(range &&other) noexcept;

    LSS_API double lower() const;
    LSS_API double upper() const;
    LSS_API double spread() const;
    LSS_API double mid_point() const;
};

typedef sptr_t<range> range_ptr;

} // namespace lss_utility

#endif ///_LSS_RANGE_HPP_
