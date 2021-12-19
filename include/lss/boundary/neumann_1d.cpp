#include "neumann_1d.hpp"

namespace lss
{

neumann_1d_builder::neumann_1d_builder()
{
}

neumann_1d_builder &neumann_1d_builder::value(const std::function<double(double)> &value)
{
    value_ = value;
    return *this;
}

neumann_1d_ptr neumann_1d_builder::build()
{
    return std::make_shared<neumann_1d>(value_);
}

} // namespace lss
