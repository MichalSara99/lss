#pragma once
#if !defined(_LSS_CONTAINER_3D_HPP_)
#define _LSS_CONTAINER_3D_HPP_

#include "../common/lss_enumerations.hpp"
#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"
#include "lss_container_2d.hpp"
#include <typeinfo>
#include <vector>

namespace lss_containers
{

using lss_enumerations::by_enum;
using lss_utility::sptr_t;

template <by_enum by> class container_3d
{
  private:
    std::size_t rows_;
    std::size_t columns_;
    std::size_t layers_;
    std::vector<container_2d<by>> rdata_;

    explicit container_3d()
    {
    }

  public:
    typedef container_2d<by> element_type;

    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers)
        : rows_{rows}, columns_{columns}, layers_{layers}
    {
        for (std::size_t l = 0; l < layers; ++l)
        {
            rdata_.emplace_back(container_2d<by>(rows, columns));
        }
    }

    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value)
        : rows_{rows}, columns_{columns}, layers_{layers}
    {
        for (std::size_t l = 0; l < layers; ++l)
        {
            rdata_.emplace_back(container_2d<by>(rows, columns, value));
        }
    }

    ~container_3d()
    {
    }

    container_3d(container_3d const &copy)
        : rows_{copy.rows_}, columns_{copy.columns_}, layers_{copy.layers_}, rdata_{copy.rdata_}
    {
    }

    container_3d(container_3d &&other) noexcept
        : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, layers_{std::move(other.layers_)},
          rdata_{std::move(other.rdata_)}
    {
    }

    container_3d &operator=(container_3d const &copy)
    {
        if (this != &copy)
        {
            rows_ = copy.rows_;
            columns_ = copy.columns_;
            layers_ = copy.layers_;
            rdata_ = copy.rdata_;
        }
        return *this;
    }

    container_3d &operator=(container_3d &&other) noexcept
    {
        if (this != &other)
        {
            rows_ = std::move(other.rows_);
            columns_ = std::move(other.columns_);
            layers_ = std::move(other.layers_);
            rdata_ = std::move(other.rdata_);
        }
        return *this;
    }

    std::size_t rows() const
    {
        return rows_;
    }
    std::size_t columns() const
    {
        return columns_;
    }
    std::size_t layers() const
    {
        return layers_;
    }
    std::size_t total_size() const
    {
        return rows_ * columns_ * layers_;
    }
    /// TODo: continue from here on
    // return value from container_2d at potision (row_idx,col_idx)
    double operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
    {
        LSS_ASSERT(row_idx < rows_, "Outside of row range");
        LSS_ASSERT(col_idx < columns_, "Outside of column range");
        LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
        return rdata_[lay_idx](row_idx, col_idx);
    }

    // return  container_2d at potision (lay_idx)
    container_2d<by> operator()(std::size_t lay_idx) const
    {
        LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
        return rdata_[lay_idx];
    }

    // return value from container_2d at potision (row_idx,col_idx,lay_idx)
    double at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
    {
        return operator()(row_idx, col_idx, lay_idx);
    }

    // return  container_2d at potision (lay_idx)
    container_2d<by> at(std::size_t lay_idx) const
    {
        return operator()(lay_idx);
    }

    // place container_2d at row position (row_idx)
    void operator()(std::size_t lay_idx, container_2d<by> const &container2d)
    {
        LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
        LSS_ASSERT(container2d.rows() == rows_, "Outside of row range");
        LSS_ASSERT(container2d.columns() == columns_, "Outside of column range");
        rdata_[lay_idx] = std::move(container2d);
    }

    //// place ro_container at row position starting at col_start_idx and ending at
    //// col_end_idx
    // void operator()(std::size_t row_idx, container<fp_type, allocator> const &row_container, std::size_t
    // col_start_idx,
    //                std::size_t col_end_idx)
    //{
    //    LSS_ASSERT(col_start_idx <= col_end_idx, "col_start_idx must be smaller or equal then col_end_idx");
    //    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    //    LSS_ASSERT(col_start_idx < columns_, "col_start_idx is outside of column range");
    //    LSS_ASSERT(col_end_idx < columns_, "col_end_idx is outside of column range");
    //    const std::size_t len = col_end_idx - col_start_idx + 1;
    //    LSS_ASSERT(len <= row_container.size(), "Inserted length is bigger then the row_container");
    //    container<fp_type, allocator> cont = this->at(row_idx);
    //    std::size_t c = 0;
    //    for (std::size_t t = col_start_idx; t <= col_end_idx; ++t, ++c)
    //    {
    //        cont[t] = row_container[c];
    //    }
    //    this->operator()(row_idx, std::move(cont));
    //}

    // place value at position (row_idx,col_idx,lay_idx)
    void operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx, double value)
    {
        LSS_ASSERT(row_idx < rows_, "Outside of row range");
        LSS_ASSERT(col_idx < columns_, "Outside of column range");
        LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
        rdata_[lay_idx](row_idx, col_idx) = value;
    }

    //// returns data as flat vector row-wise
    // std::vector<fp_type, allocator> const data() const
    //{
    //    std::vector<fp_type, allocator> d(rows_ * columns_);
    //    auto itr = d.begin();
    //    for (std::size_t r = 0; r < rows_; ++r)
    //    {
    //        auto row = at(r);
    //        std::copy(row.begin(), row.end(), itr);
    //        std::advance(itr, columns_);
    //    }
    //    return d;
    //}
    // template <typename in_itr> void set_data(in_itr first, in_itr last)
    //{
    //    const std::size_t dist = std::distance(first, last);
    //    LSS_ASSERT((rows_ * columns_) == dist, "Source data is either too long or too short");
    //    for (std::size_t r = 0; r < rows_; ++r)
    //    {
    //        for (std::size_t c = 0; c < columns_; ++c)
    //        {
    //            this->operator()(r, c, *first);
    //            ++first;
    //        }
    //    }
    //}
};

// template <typename fp_type, template <typename, typename> typename container, typename allocator>
// void copy(container_3d<fp_type, container, allocator> &dest, container_3d<fp_type, container, allocator> const &src)
//{
//    LSS_ASSERT(dest.columns() == src.columns(), "dest and src must have same dimensions");
//    LSS_ASSERT(dest.rows() == src.rows(), "dest and src must have same dimensions");
//    for (std::size_t r = 0; r < dest.rows(); ++r)
//    {
//        dest(r, src.at(r));
//    }
//}

//// concrete single-precision floating-point matrix
// using matrix_3d_float = container_3d<float, std::vector, std::allocator<float>>;
//// concrete double-precision floating-point matrix
// using matrix_3d_double = container_3d<double, std::vector, std::allocator<double>>;
//
// template <typename fp_type>
// using matrix_3d_default_ptr = sptr_t<container_3d<fp_type, std::vector, std::allocator<fp_type>>>;

} // namespace lss_containers

#endif ///_LSS_CONTAINER_3D_HPP_
