#include <typeinfo>
#include <vector>

#include "lss_container_3d.hpp"

namespace lss_containers
{

container_3d<by_enum::Row>::container_3d()
{
}

container_3d<by_enum::Row>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Row>(rows_, columns_));
    }
}

container_3d<by_enum::Row>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Row>(rows_, columns_, value));
    }
}

container_3d<by_enum::Row>::~container_3d()
{
}

container_3d<by_enum::Row>::container_3d(container_3d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, layers_{copy.layers_}, data_{copy.data_}
{
}

container_3d<by_enum::Row>::container_3d(container_3d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, layers_{std::move(other.layers_)},
      data_{std::move(other.data_)}
{
}

container_3d<by_enum::Row>::container_3d(container_3d<by_enum::Column> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{

    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Row>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::Row>::container_3d(container_3d<by_enum::Layer> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{
    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Row>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::Row> &container_3d<by_enum::Row>::operator=(container_3d const &copy)
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

container_3d<by_enum::Row> &container_3d<by_enum::Row>::operator=(container_3d &&other) noexcept
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

container_3d<by_enum::Row> &container_3d<by_enum::Row>::operator=(container_3d<by_enum::Column> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Row>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
    return *this;
}

container_3d<by_enum::Row> &container_3d<by_enum::Row>::operator=(container_3d<by_enum::Layer> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Row>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
    return *this;
}

void container_3d<by_enum::Row>::from_data(std::vector<double> const &data)
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
                tid = c + r * columns_ + l * rows_ * columns_;
                data_[l](r, c, data[tid]);
            }
        }
    }
}

std::size_t container_3d<by_enum::Row>::rows() const
{
    return rows_;
}

std::size_t container_3d<by_enum::Row>::columns() const
{
    return columns_;
}

std::size_t container_3d<by_enum::Row>::layers() const
{
    return layers_;
}

std::size_t container_3d<by_enum::Row>::total_size() const
{
    return rows_ * columns_ * layers_;
}

double container_3d<by_enum::Row>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[lay_idx](row_idx, col_idx);
}

std::vector<double> container_3d<by_enum::Row>::operator()(std::size_t row_idx, std::size_t lay_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[lay_idx](row_idx);
}

double container_3d<by_enum::Row>::at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    return operator()(row_idx, col_idx, lay_idx);
}

std::vector<double> container_3d<by_enum::Row>::at(std::size_t row_idx, std::size_t lay_idx) const
{
    return operator()(row_idx, lay_idx);
}

void container_3d<by_enum::Row>::operator()(std::size_t row_idx, std::size_t lay_idx, container_t const &cont)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    LSS_ASSERT(cont.size() == columns_, "Outside of column range");
    data_[lay_idx](row_idx, cont);
}

void container_3d<by_enum::Row>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx, double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    data_[lay_idx](row_idx, col_idx, value);
}

std::vector<double> const container_3d<by_enum::Row>::data() const
{
    std::vector<double> d(rows_ * columns_ * layers_);
    auto itr = d.begin();
    for (std::size_t l = 0; l < layers_; ++l)
    {
        for (std::size_t r = 0; r < rows_; ++r)
        {
            auto row = at(r, l);
            std::copy(row.begin(), row.end(), itr);
            std::advance(itr, columns_);
        }
    }
    return d;
}

/// COLUMN-WISE

container_3d<by_enum::Column>::container_3d()
{
}

container_3d<by_enum::Column>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, columns_));
    }
}

container_3d<by_enum::Column>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, columns_, value));
    }
}

container_3d<by_enum::Column>::~container_3d()
{
}

container_3d<by_enum::Column>::container_3d(container_3d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, layers_{copy.layers_}, data_{copy.data_}
{
}

container_3d<by_enum::Column>::container_3d(container_3d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, layers_{std::move(other.layers_)},
      data_{std::move(other.data_)}
{
}

container_3d<by_enum::Column>::container_3d(container_3d<by_enum::Row> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{

    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::Column>::container_3d(container_3d<by_enum::Layer> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{
    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::Column> &container_3d<by_enum::Column>::operator=(container_3d const &copy)
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

container_3d<by_enum::Column> &container_3d<by_enum::Column>::operator=(container_3d &&other) noexcept
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

container_3d<by_enum::Column> &container_3d<by_enum::Column>::operator=(container_3d<by_enum::Row> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
    return *this;
}

container_3d<by_enum::Column> &container_3d<by_enum::Column>::operator=(container_3d<by_enum::Layer> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t l = 0; l < layers_; ++l)
    {
        data_.emplace_back(container_2d<by_enum::Column>(rows_, columns_));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[l](r, c, copy(r, c, l));
            }
        }
    }
    return *this;
}

std::size_t container_3d<by_enum::Column>::rows() const
{
    return rows_;
}

std::size_t container_3d<by_enum::Column>::columns() const
{
    return columns_;
}

std::size_t container_3d<by_enum::Column>::layers() const
{
    return layers_;
}

std::size_t container_3d<by_enum::Column>::total_size() const
{
    return rows_ * columns_ * layers_;
}

void container_3d<by_enum::Column>::from_data(std::vector<double> const &data)
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
                tid = r + c * rows_ + l * rows_ * columns_;
                data_[l](r, c, data[tid]);
            }
        }
    }
}

double container_3d<by_enum::Column>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[lay_idx](row_idx, col_idx);
}

std::vector<double> container_3d<by_enum::Column>::operator()(std::size_t col_idx, std::size_t lay_idx) const
{
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[lay_idx](col_idx);
}

double container_3d<by_enum::Column>::at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    return operator()(row_idx, col_idx, lay_idx);
}

std::vector<double> container_3d<by_enum::Column>::at(std::size_t col_idx, std::size_t lay_idx) const
{
    return operator()(col_idx, lay_idx);
}

void container_3d<by_enum::Column>::operator()(std::size_t col_idx, std::size_t lay_idx, container_t const &cont)
{
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    LSS_ASSERT(cont.size() == rows_, "Outside of row range");
    data_[lay_idx](col_idx, cont);
}

void container_3d<by_enum::Column>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx,
                                               double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    data_[lay_idx](row_idx, col_idx, value);
}

std::vector<double> const container_3d<by_enum::Column>::data() const
{
    std::vector<double> d(rows_ * columns_ * layers_);
    auto itr = d.begin();
    for (std::size_t l = 0; l < layers_; ++l)
    {
        for (std::size_t c = 0; c < columns_; ++c)
        {
            auto col = at(c, l);
            std::copy(col.begin(), col.end(), itr);
            std::advance(itr, rows_);
        }
    }
    return d;
}

/// LAYER-WISE

container_3d<by_enum::Layer>::container_3d()
{
}

container_3d<by_enum::Layer>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Column>(layers_, columns_));
    }
}

container_3d<by_enum::Layer>::container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value)
    : rows_{rows}, columns_{columns}, layers_{layers}
{
    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Column>(layers_, columns_, value));
    }
}

container_3d<by_enum::Layer>::~container_3d()
{
}

container_3d<by_enum::Layer>::container_3d(container_3d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, layers_{copy.layers_}, data_{copy.data_}
{
}

container_3d<by_enum::Layer>::container_3d(container_3d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, layers_{std::move(other.layers_)},
      data_{std::move(other.data_)}
{
}

container_3d<by_enum::Layer>::container_3d(container_3d<by_enum::Row> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{
    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Column>(layers_, columns_));
        for (std::size_t l = 0; l < layers_; ++l)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[r](l, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::Layer>::container_3d(container_3d<by_enum::Column> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}, layers_{copy.layers()}
{
    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Column>(layers_, columns_));
        for (std::size_t l = 0; l < layers_; ++l)
        {
            for (std::size_t c = 0; c < columns_; ++c)
            {
                data_[r](l, c, copy(r, c, l));
            }
        }
    }
}

container_3d<by_enum::Layer> &container_3d<by_enum::Layer>::operator=(container_3d const &copy)
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

container_3d<by_enum::Layer> &container_3d<by_enum::Layer>::operator=(container_3d &&other) noexcept
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

container_3d<by_enum::Layer> &container_3d<by_enum::Layer>::operator=(container_3d<by_enum::Row> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Column>(layers_, columns_));
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

container_3d<by_enum::Layer> &container_3d<by_enum::Layer>::operator=(container_3d<by_enum::Column> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    layers_ = copy.layers();

    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(container_2d<by_enum::Column>(layers_, columns_));
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

std::size_t container_3d<by_enum::Layer>::rows() const
{
    return rows_;
}

std::size_t container_3d<by_enum::Layer>::columns() const
{
    return columns_;
}

std::size_t container_3d<by_enum::Layer>::layers() const
{
    return layers_;
}

std::size_t container_3d<by_enum::Layer>::total_size() const
{
    return rows_ * columns_ * layers_;
}

void container_3d<by_enum::Layer>::from_data(std::vector<double> const &data)
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
                tid = l + c * layers_ + r * layers_ * columns_;
                data_[r](l, c, data[tid]);
            }
        }
    }
}

double container_3d<by_enum::Layer>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    return data_[row_idx](lay_idx, col_idx);
}

std::vector<double> container_3d<by_enum::Layer>::operator()(std::size_t row_idx, std::size_t col_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    return data_[row_idx](col_idx);
}

double container_3d<by_enum::Layer>::at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const
{
    return operator()(row_idx, col_idx, lay_idx);
}

std::vector<double> container_3d<by_enum::Layer>::at(std::size_t row_idx, std::size_t col_idx) const
{
    return operator()(row_idx, col_idx);
}

void container_3d<by_enum::Layer>::operator()(std::size_t row_idx, std::size_t col_idx, container_t const &cont)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(cont.size() == layers_, "Outside of layer range");
    data_[row_idx](col_idx, cont);
}

void container_3d<by_enum::Layer>::operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx,
                                              double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(lay_idx < layers_, "Outside of layer range");
    data_[row_idx](lay_idx, col_idx, value);
}

std::vector<double> const container_3d<by_enum::Layer>::data() const
{
    std::vector<double> d(rows_ * columns_ * layers_);
    auto itr = d.begin();
    for (std::size_t r = 0; r < rows_; ++r)
    {
        for (std::size_t c = 0; c < columns_; ++c)
        {
            auto lay = at(r, c);
            std::copy(lay.begin(), lay.end(), itr);
            std::advance(itr, layers_);
        }
    }
    return d;
}

} // namespace lss_containers
