#include <typeinfo>
#include <vector>

#include "lss_container_3d.hpp"

namespace lss_containers
{

container_3d<by_enum::RowPlane>::container_3d()
{
}

container_3d<by_enum::RowPlane>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t i = 0; i < rows_; ++i)
    {
        data_.emplace_back(container_2d<by_enum::Row>(layers_, columns_));
    }
}

container_3d<by_enum::RowPlane>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t i = 0; i < rows_; ++i)
    {
        data_.emplace_back(container_2d<by_enum::Row>(layers_, columns_, value));
    }
}

container_3d<by_enum::RowPlane>::~container_3d()
{
}

container_3d<by_enum::RowPlane>::container_3d(container_3d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, layers_{copy.layers_}, data_{copy.data_}
{
}

container_3d<by_enum::RowPlane>::container_3d(container_3d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, layers_{std::move(other.layers_)},
      data_{std::move(other.data_)}
{
}

container_3d<by_enum::RowPlane>::container_3d(container_3d<by_enum::ColumnPlane> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{

    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Row>(layers_, columns_));
        for (std::size_t l = 0; l < layers_; ++l)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[r](l, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::RowPlane> &container_3d<by_enum::RowPlane>::operator=(container_3d const &copy)
{
    if (this != &copy)
    {
        rows_ = copy.rows_;
        columns_ = copy.columns_;
        layers_ = copy.layers_;
        data_ = copy.data_;
    }
    return *this;
}

container_3d<by_enum::RowPlane> &container_3d<by_enum::RowPlane>::operator=(container_3d &&other) noexcept
{
    if (this != &other)
    {
        rows_ = std::move(other.rows_);
        columns_ = std::move(other.columns_);
        layers_ = std::move(other.layers_);
        data_ = std::move(other.data_);
    }
    return *this;
}

container_3d<by_enum::RowPlane> &container_3d<by_enum::RowPlane>::operator=(
    container_3d<by_enum::ColumnPlane> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Row>(layers_, columns_));
        for (std::size_t l = 0; l < layers_; ++l)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[r](l, c, copy(r, c, l));
            }
        }
    }
    return *this;
}

void container_3d<by_enum::RowPlane>::from_data(std::vector<double> const &data)
{
    auto const total_size = rows_ * columns_ * layers_;
    std::size_t tid{};
    LSS_ASSERT(total_size == data.size(), "Data are not of the correct size");
    for (std::size_t l = 0; l < layers_; ++l)
    {
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                tid = c + l * columns_ + r * layers_ * columns_;
                data_[r](l, c, data[tid]);
            }
        }
    }
}

std::size_t container_3d<by_enum::RowPlane>::rows() const
{
    return rows_;
}

std::size_t container_3d<by_enum::RowPlane>::columns() const
{
    return columns_;
}

std::size_t container_3d<by_enum::RowPlane>::layers() const
{
    return layers_;
}

std::size_t container_3d<by_enum::RowPlane>::total_size() const
{
    return rows_ * columns_ * layers_;
}

double container_3d<by_enum::RowPlane>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[row_idx](lay_idx, col_idx);
}

container_2d<by_enum::Row> container_3d<by_enum::RowPlane>::operator()(std::size_t row_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    return data_[row_idx];
}

double container_3d<by_enum::RowPlane>::at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    return operator()(row_idx, col_idx, lay_idx);
}

container_2d<by_enum::Row> container_3d<by_enum::RowPlane>::at(std::size_t row_idx) const
{
    return operator()(row_idx);
}

void container_3d<by_enum::RowPlane>::operator()(std::size_t row_idx, container_2d<by_enum::Row> const &cont)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(cont.rows() == layers_, "Outside of layer range");
    LSS_ASSERT(cont.columns() == columns_, "Outside of column range");
    data_[row_idx] = std::move(cont);
}

void container_3d<by_enum::RowPlane>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx,
                                                 double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    data_[row_idx](lay_idx, col_idx, value);
}

std::vector<double> const container_3d<by_enum::RowPlane>::data() const
{
    std::vector<double> d(rows_ * columns_ * layers_);
    auto itr = d.begin();
    for (std::size_t r = 0; r < rows_; ++r)
    {
        auto row_plane = at(r);
        auto row = row_plane.data();
        std::copy(row.begin(), row.end(), itr);
        std::advance(itr, row.size());
    }
    return d;
}

/// COLUMN-WISE

container_3d<by_enum::ColumnPlane>::container_3d()
{
}

container_3d<by_enum::ColumnPlane>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t c = 0; c < columns_; ++c)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, layers_));
    }
}

container_3d<by_enum::ColumnPlane>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers,
                                                 double value)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t c = 0; c < columns_; ++c)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, layers_, value));
    }
}

container_3d<by_enum::ColumnPlane>::~container_3d()
{
}

container_3d<by_enum::ColumnPlane>::container_3d(container_3d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, layers_{copy.layers_}, data_{copy.data_}
{
}

container_3d<by_enum::ColumnPlane>::container_3d(container_3d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, layers_{std::move(other.layers_)},
      data_{std::move(other.data_)}
{
}

container_3d<by_enum::ColumnPlane>::container_3d(container_3d<by_enum::RowPlane> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{

    for (std::size_t c = 0; c < columns_; ++c)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, layers_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t l = 0; l < layers_; ++l)
            {
                data_[c](r, l, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::ColumnPlane> &container_3d<by_enum::ColumnPlane>::operator=(container_3d const &copy)
{
    if (this != &copy)
    {
        rows_ = copy.rows_;
        columns_ = copy.columns_;
        layers_ = copy.layers_;
        data_ = copy.data_;
    }
    return *this;
}

container_3d<by_enum::ColumnPlane> &container_3d<by_enum::ColumnPlane>::operator=(container_3d &&other) noexcept
{
    if (this != &other)
    {
        rows_ = std::move(other.rows_);
        columns_ = std::move(other.columns_);
        layers_ = std::move(other.layers_);
        data_ = std::move(other.data_);
    }
    return *this;
}

container_3d<by_enum::ColumnPlane> &container_3d<by_enum::ColumnPlane>::operator=(
    container_3d<by_enum::RowPlane> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t c = 0; c < columns_; ++c)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, layers_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t l = 0; l < layers_; ++l)
            {
                data_[c](r, l, copy(r, c, l));
            }
        }
    }
    return *this;
}

std::size_t container_3d<by_enum::ColumnPlane>::rows() const
{
    return rows_;
}

std::size_t container_3d<by_enum::ColumnPlane>::columns() const
{
    return columns_;
}

std::size_t container_3d<by_enum::ColumnPlane>::layers() const
{
    return layers_;
}

std::size_t container_3d<by_enum::ColumnPlane>::total_size() const
{
    return rows_ * columns_ * layers_;
}

void container_3d<by_enum::ColumnPlane>::from_data(std::vector<double> const &data)
{
    auto const total_size = rows_ * columns_ * layers_;
    std::size_t tid{};
    LSS_ASSERT(total_size == data.size(), "Data are not of the correct size");
    for (std::size_t l = 0; l < layers_; ++l)
    {
        for (std::size_t c = 0; c < columns_; ++c)
        {
            for (std::size_t r = 0; r < rows_; ++r)
            {
                tid = r + l * rows_ + c * rows_ * layers_;
                data_[c](r, l, data[tid]);
            }
        }
    }
}

double container_3d<by_enum::ColumnPlane>::operator()(std::size_t row_idx, std::size_t col_idx,
                                                      std::size_t lay_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[col_idx](row_idx, lay_idx);
}

container_2d<by_enum::Column> container_3d<by_enum::ColumnPlane>::operator()(std::size_t col_idx) const
{
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    return data_[col_idx];
}

double container_3d<by_enum::ColumnPlane>::at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    return operator()(row_idx, col_idx, lay_idx);
}

container_2d<by_enum::Column> container_3d<by_enum::ColumnPlane>::at(std::size_t col_idx) const
{
    return operator()(col_idx);
}

void container_3d<by_enum::ColumnPlane>::operator()(std::size_t col_idx, container_2d<by_enum::Column> const &cont)
{
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(cont.rows() == rows_, "Outside of row range");
    LSS_ASSERT(cont.columns() == layers_, "Outside of layer range");
    data_[col_idx] = std::move(cont);
}

void container_3d<by_enum::ColumnPlane>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx,
                                                    double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    data_[col_idx](row_idx, lay_idx, value);
}

std::vector<double> const container_3d<by_enum::ColumnPlane>::data() const
{
    std::vector<double> d(rows_ * columns_ * layers_);
    auto itr = d.begin();

    for (std::size_t c = 0; c < columns_; ++c)
    {
        auto col_plane = at(c);
        auto col = col_plane.data();
        std::copy(col.begin(), col.end(), itr);
        std::advance(itr, col.size());
    }

    return d;
}

} // namespace lss_containers
