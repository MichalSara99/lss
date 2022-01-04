/**

    @file      lss_container_2d.hpp
    @brief     Represents 2D row and column-wise container
    @details   ~
    @author    Michal Sara
    @date      14.12.2021
    @copyright © Michal Sara, 2021. All right reserved.

**/
#pragma once
#if !defined(_LSS_CONTAINER_2D_HPP_)
#define _LSS_CONTAINER_2D_HPP_

#include "../common/lss_enumerations.hpp"
#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"
#include <typeinfo>
#include <vector>

namespace lss_containers
{

using lss_enumerations::by_enum;
using lss_utility::container_t;
using lss_utility::sptr_t;

template <by_enum by> class container_2d
{
};

/**

    @class   container_2d
    @brief   row-wise 2D conatiner object
    @details ~

**/
template <> class container_2d<by_enum::Row>
{
  private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<std::vector<double>> data_;

    explicit container_2d();

  public:
    explicit container_2d(std::size_t rows, std::size_t columns);
    explicit container_2d(std::size_t rows, std::size_t columns, double value);

    ~container_2d();

    container_2d(container_2d const &copy);
    container_2d(container_2d &&other) noexcept;
    container_2d(container_2d<by_enum::Column> const &copy);

    container_2d &operator=(container_2d const &copy);
    container_2d &operator=(container_2d &&other) noexcept;
    container_2d &operator=(container_2d<by_enum::Column> const &copy);

    LSS_API void from_data(std::vector<double> const &data);

    LSS_API std::size_t rows() const;
    LSS_API std::size_t columns() const;
    LSS_API std::size_t total_size() const;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @retval value from container_2d at potision (row_idx,col_idx)
    **/
    LSS_API double operator()(std::size_t row_idx, std::size_t col_idx) const;

    /**
        @brief
        @param  row_idx
        @retval row container from container_2d at potision (row_idx)
    **/
    LSS_API container_t operator()(std::size_t row_idx) const;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @retval value from container_2d at potision (row_idx,col_idx)
    **/
    LSS_API double at(std::size_t row_idx, std::size_t col_idx) const;

    /**
        @brief
        @param  row_idx
        @retval  row container from container_2d at potision (row_idx)
    **/
    LSS_API container_t at(std::size_t row_idx) const;

    /**
        @brief place row container at position (row_idx)
        @param row_idx
        @param cont
    **/
    LSS_API void operator()(std::size_t row_idx, std::vector<double> const &cont);

    /**
        @brief place value at position (row_idx,col_idx)
        @param row_idx
        @param col_idx
        @param value
    **/
    LSS_API void operator()(std::size_t row_idx, std::size_t col_idx, double value);

    /**
        @brief
        @retval data as flat vector row-wise
    **/
    LSS_API container_t const data() const;
};

/**

    @class   container_2d
    @brief   column-wise 2D conatiner object
    @details ~

**/
template <> class container_2d<by_enum::Column>
{
  private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<std::vector<double>> data_;

    explicit container_2d();

  public:
    explicit container_2d(std::size_t rows, std::size_t columns);
    explicit container_2d(std::size_t rows, std::size_t columns, double value);

    ~container_2d();

    container_2d(container_2d const &copy);
    container_2d(container_2d &&other) noexcept;
    container_2d(container_2d<by_enum::Row> const &copy);

    container_2d &operator=(container_2d const &copy);
    container_2d &operator=(container_2d &&other) noexcept;
    container_2d &operator=(container_2d<by_enum::Row> const &copy);

    LSS_API std::size_t rows() const;
    LSS_API std::size_t columns() const;
    LSS_API std::size_t total_size() const;

    LSS_API void from_data(std::vector<double> const &data);

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @retval   value from container_2d at potision (row_idx,col_idx)
    **/
    LSS_API double operator()(std::size_t row_idx, std::size_t col_idx) const;

    /**
        @brief
        @param  col_idx
        @retval  column container from container_2d at potision (col_idx)
    **/
    LSS_API container_t operator()(std::size_t col_idx) const;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @retval  value from container_2d at potision (row_idx,col_idx)
    **/
    LSS_API double at(std::size_t row_idx, std::size_t col_idx) const;

    /**
        @brief
        @param  col_idx
        @retval column container from container_2d at potision (col_idx)
    **/
    LSS_API container_t at(std::size_t col_idx) const;

    /**
        @brief place column container at position (col_idx)
        @param col_idx
        @param cont
    **/
    LSS_API void operator()(std::size_t col_idx, std::vector<double> const &cont);

    /**
        @brief place value at position (row_idx,col_idx)
        @param row_idx
        @param col_idx
        @param value
    **/
    LSS_API void operator()(std::size_t row_idx, std::size_t col_idx, double value);

    /**
        @brief
        @retval  data as flat vector column-wise
    **/
    LSS_API container_t const data() const;
};

/**
    @brief  copy container from one to another
    @tparam by
    @param  dest
    @param  src
**/
template <by_enum by> void copy(container_2d<by> &dest, container_2d<by> const &src)
{
    LSS_ASSERT(dest.columns() == src.columns(), "dest and src must have same dimensions");
    LSS_ASSERT(dest.rows() == src.rows(), "dest and src must have same dimensions");
    std::size_t size;
    if (by == by_enum::Row)
        size = dest.rows();
    else
        size = dest.columns();

    for (std::size_t t = 0; t < size; ++t)
    {
        dest(t, src.at(t));
    }
}

using rmatrix_2d = container_2d<by_enum::Row>;
using cmatrix_2d = container_2d<by_enum::Column>;

using rmatrix_2d_ptr = sptr_t<rmatrix_2d>;
using cmatrix_2d_ptr = sptr_t<cmatrix_2d>;

} // namespace lss_containers

#endif ///_LSS_CONTAINER_2D_HPP_
