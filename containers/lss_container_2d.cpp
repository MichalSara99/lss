#include "lss_container_2d.hpp"

#include <typeinfo>
#include <vector>

namespace lss_containers
{

container_2d<by_enum::Row>::container_2d()
{
}

container_2d<by_enum::Row>::container_2d(std::size_t rows, std::size_t columns) : rows_{rows}, columns_{columns}
{
    for (std::size_t r = 0; r < rows; ++r)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(columns)));
    }
}

container_2d<by_enum::Row>::container_2d(std::size_t rows, std::size_t columns, double value)
    : rows_{rows}, columns_{columns}
{
    for (std::size_t r = 0; r < rows; ++r)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(columns), value));
    }
}

container_2d<by_enum::Row>::~container_2d()
{
}

container_2d<by_enum::Row>::container_2d(container_2d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, data_{copy.data_}
{
}

container_2d<by_enum::Row>::container_2d(container_2d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, data_{std::move(other.data_)}
{
}

container_2d<by_enum::Row>::container_2d(container_2d<by_enum::Column> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}
{
    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(columns_)));
        for (std::size_t c = 0; c < columns_; ++c)
        {
            data_[r][c] = copy(r, c);
        }
    }
}

container_2d<by_enum::Row> &container_2d<by_enum::Row>::operator=(container_2d const &copy)
{
    if (this != &copy)
    {
        rows_ = copy.rows_;
        columns_ = copy.columns_;
        data_ = copy.data_;
    }
    return *this;
}

container_2d<by_enum::Row> &container_2d<by_enum::Row>::operator=(container_2d &&other) noexcept
{
    if (this != &other)
    {
        rows_ = std::move(other.rows_);
        columns_ = std::move(other.columns_);
        data_ = std::move(other.data_);
    }
    return *this;
}

container_2d<by_enum::Row> &container_2d<by_enum::Row>::operator=(container_2d<by_enum::Column> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();
    for (std::size_t r = 0; r < rows_; ++r)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(columns_)));
        for (std::size_t c = 0; c < columns_; ++c)
        {
            data_[r][c] = copy(r, c);
        }
    }
    return *this;
}

void container_2d<by_enum::Row>::from_data(std::vector<double> const &data)
{
    auto const total_size = rows_ * columns_;
    std::size_t tid{};
    LSS_ASSERT(total_size == data.size(), "Data are not of the correct size");
    for (std::size_t r = 0; r < rows_; ++r)
    {
        for (std::size_t c = 0; c < columns_; ++c)
        {
            tid = c + r * columns_;
            data_[r][c] = data[tid];
        }
    }
}

std::size_t container_2d<by_enum::Row>::rows() const
{
    return rows_;
}
std::size_t container_2d<by_enum::Row>::columns() const
{
    return columns_;
}
std::size_t container_2d<by_enum::Row>::total_size() const
{
    return rows_ * columns_;
}

double container_2d<by_enum::Row>::operator()(std::size_t row_idx, std::size_t col_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    return data_[row_idx][col_idx];
}

std::vector<double> container_2d<by_enum::Row>::operator()(std::size_t row_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    return data_[row_idx];
}

double container_2d<by_enum::Row>::at(std::size_t row_idx, std::size_t col_idx) const
{
    return operator()(row_idx, col_idx);
}

std::vector<double> container_2d<by_enum::Row>::at(std::size_t row_idx) const
{
    return operator()(row_idx);
}

void container_2d<by_enum::Row>::operator()(std::size_t row_idx, std::vector<double> const &cont)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(cont.size() == columns_, "Outside of column range");
    data_[row_idx] = std::move(cont);
}

void container_2d<by_enum::Row>::operator()(std::size_t row_idx, std::size_t col_idx, double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    data_[row_idx][col_idx] = value;
}

std::vector<double> const container_2d<by_enum::Row>::data() const
{
    std::vector<double> d(rows_ * columns_);
    auto itr = d.begin();
    for (std::size_t r = 0; r < rows_; ++r)
    {
        auto row = at(r);
        std::copy(row.begin(), row.end(), itr);
        std::advance(itr, columns_);
    }
    return d;
}

/// COLUMN-WISE

container_2d<by_enum::Column>::container_2d()
{
}

container_2d<by_enum::Column>::container_2d(std::size_t rows, std::size_t columns) : rows_{rows}, columns_{columns}
{
    for (std::size_t c = 0; c < columns; ++c)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(rows)));
    }
}

container_2d<by_enum::Column>::container_2d(std::size_t rows, std::size_t columns, double value)
    : rows_{rows}, columns_{columns}
{
    for (std::size_t c = 0; c < columns; ++c)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(rows), value));
    }
}

container_2d<by_enum::Column>::~container_2d()
{
}

container_2d<by_enum::Column>::container_2d(container_2d const &copy)
    : rows_{copy.rows_}, columns_{copy.columns_}, data_{copy.data_}
{
}

container_2d<by_enum::Column>::container_2d(container_2d &&other) noexcept
    : rows_{std::move(other.rows_)}, columns_{std::move(other.columns_)}, data_{std::move(other.data_)}
{
}

container_2d<by_enum::Column>::container_2d(container_2d<by_enum::Row> const &copy)
    : rows_{copy.rows()}, columns_{copy.columns()}
{
    for (std::size_t c = 0; c < columns_; ++c)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(rows_)));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            data_[c][r] = copy(r, c);
        }
    }
}

container_2d<by_enum::Column> &container_2d<by_enum::Column>::operator=(container_2d const &copy)
{
    if (this != &copy)
    {
        rows_ = copy.rows_;
        columns_ = copy.columns_;
        data_ = copy.data_;
    }
    return *this;
}

container_2d<by_enum::Column> &container_2d<by_enum::Column>::operator=(container_2d &&other) noexcept
{
    if (this != &other)
    {
        rows_ = std::move(other.rows_);
        columns_ = std::move(other.columns_);
        data_ = std::move(other.data_);
    }
    return *this;
}

container_2d<by_enum::Column> &container_2d<by_enum::Column>::operator=(container_2d<by_enum::Row> const &copy)
{
    data_.clear();
    rows_ = copy.rows();
    columns_ = copy.columns();

    for (std::size_t c = 0; c < columns_; ++c)
    {
        data_.emplace_back(std::vector<double>(static_cast<std::size_t>(rows_)));
        for (std::size_t r = 0; r < rows_; ++r)
        {
            data_[c][r] = copy(r, c);
        }
    }
    return *this;
}

std::size_t container_2d<by_enum::Column>::rows() const
{
    return rows_;
}
std::size_t container_2d<by_enum::Column>::columns() const
{
    return columns_;
}
std::size_t container_2d<by_enum::Column>::total_size() const
{
    return rows_ * columns_;
}

void container_2d<by_enum::Column>::from_data(std::vector<double> const &data)
{
    auto const total_size = rows_ * columns_;
    std::size_t tid{};
    LSS_ASSERT(total_size == data.size(), "Data are not of the correct size");
    for (std::size_t c = 0; c < columns_; ++c)
    {
        for (std::size_t r = 0; r < rows_; ++r)
        {
            tid = r + c * rows_;
            data_[c][r] = data[tid];
        }
    }
}

double container_2d<by_enum::Column>::operator()(std::size_t row_idx, std::size_t col_idx) const
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    return data_[col_idx][row_idx];
}

std::vector<double> container_2d<by_enum::Column>::operator()(std::size_t col_idx) const
{
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    return data_[col_idx];
}

double container_2d<by_enum::Column>::at(std::size_t row_idx, std::size_t col_idx) const
{
    return operator()(row_idx, col_idx);
}

std::vector<double> container_2d<by_enum::Column>::at(std::size_t col_idx) const
{
    return operator()(col_idx);
}

void container_2d<by_enum::Column>::operator()(std::size_t col_idx, std::vector<double> const &cont)
{
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    LSS_ASSERT(cont.size() == rows_, "Outside of row range");
    data_[col_idx] = std::move(cont);
}

void container_2d<by_enum::Column>::operator()(std::size_t row_idx, std::size_t col_idx, double value)
{
    LSS_ASSERT(row_idx < rows_, "Outside of row range");
    LSS_ASSERT(col_idx < columns_, "Outside of column range");
    data_[col_idx][row_idx] = value;
}

std::vector<double> const container_2d<by_enum::Column>::data() const
{
    std::vector<double> d(rows_ * columns_);
    auto itr = d.begin();
    for (std::size_t c = 0; c < columns_; ++c)
    {
        auto col = at(c);
        std::copy(col.begin(), col.end(), itr);
        std::advance(itr, rows_);
    }
    return d;
}

} // namespace lss_containers
