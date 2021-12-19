#include "robin_1d.hpp"

namespace lss
{

robin_1d_builder::robin_1d_builder()
{
}

robin_1d_builder &robin_1d_builder::value(const std::function<double(double)> &value)
{
    value_ = value;
    return *this;
}

robin_1d_builder &robin_1d_builder::linear_value(const std::function<double(double)> &linear_value)
{
    linear_value_ = linear_value;
    return *this;
}

robin_1d_ptr robin_1d_builder::build()
{
    return std::make_shared<robin_1d>(linear_value_, value_);
}

} // namespace lss
