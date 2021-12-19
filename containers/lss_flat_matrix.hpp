/**

    @file      lss_flat_matrix.hpp
    @brief     represents flat matrix
    @details   ~
    @author    Michal Sara
    @date      14.12.2021
    @copyright © Michal Sara, 2021. All right reserved.

**/
#pragma once

#pragma once
#if !defined(_LSS_FLAT_MATRIX_HPP_)
#define _LSS_FLAT_MATRIX_HPP_

#include "../common/lss_enumerations.hpp"
#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"
#include <vector>

namespace lss_containers
{

using lss_enumerations::flat_matrix_sort_enum;

/**
    @struct flat_matrix
    @brief  Flat matrix object
**/
struct flat_matrix
{
  private:
    std::vector<std::tuple<std::size_t, std::size_t, double>> container_;
    std::vector<std::size_t> column_cnt_;
    std::vector<double> diagonal_;
    std::size_t ncols_, nrows_;

    explicit flat_matrix();

  public:
    explicit flat_matrix(std::size_t nrows, std::size_t ncols);

    virtual ~flat_matrix();

    flat_matrix(flat_matrix const &copy);
    flat_matrix(flat_matrix &&other) noexcept;

    flat_matrix &operator=(flat_matrix const &copy);
    flat_matrix &operator=(flat_matrix &&other) noexcept;

    std::size_t rows() const;
    std::size_t columns() const;
    std::size_t size() const;
    void clear();
    double diagonal_at_row(std::size_t row_idx) const;
    std::size_t non_zero_column_size(std::size_t row_idx) const;

    void emplace_back(std::size_t row_idx, std::size_t col_idx, double value);

    void emplace_back(std::tuple<std::size_t, std::size_t, double> tuple);

    void sort(flat_matrix_sort_enum sort);

    std::tuple<std::size_t, std::size_t, double> const &at(std::size_t idx) const;
};

} // namespace lss_containers

#endif ///_LSS_FLAT_MATRIX_HPP_
