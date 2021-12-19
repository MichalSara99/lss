#include "container_2d.hpp"

namespace lss
{

rmatrix_builder::rmatrix_builder()
{
}

rmatrix_builder &rmatrix_builder::rows(std::size_t rows)
{
    rows_ = rows;
    return *this;
}

rmatrix_builder &rmatrix_builder::columns(std::size_t columns)
{
    columns_ = columns;
    return *this;
}

rmatrix_builder &rmatrix_builder::default_value(double value)
{
    dvalue_ = value;
    return *this;
}

rmatrix_ptr rmatrix_builder::build()
{
    return std::make_shared<rmatrix>(rows_, columns_, dvalue_);
}

cmatrix_builder::cmatrix_builder()
{
}

cmatrix_builder &cmatrix_builder::rows(std::size_t rows)
{
    rows_ = rows;
    return *this;
}

cmatrix_builder &cmatrix_builder::columns(std::size_t columns)
{
    columns_ = columns;
    return *this;
}

cmatrix_builder &cmatrix_builder::default_value(double value)
{
    dvalue_ = value;
    return *this;
}

cmatrix_ptr cmatrix_builder::build()
{
    return std::make_shared<cmatrix>(rows_, columns_, dvalue_);
}

} // namespace lss
