#include "dirichlet_1d.hpp"

namespace lss
{

dirichlet_1d_builder::dirichlet_1d_builder()
{
}

dirichlet_1d_builder &dirichlet_1d_builder::value(const std::function<double(double)> &value)
{
    value_ = value;
    return *this;
}

dirichlet_1d_ptr dirichlet_1d_builder::build()
{
    return std::make_shared<dirichlet_1d>(value_);
}

} // namespace lss
