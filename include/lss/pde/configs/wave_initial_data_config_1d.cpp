#include "wave_initial_data_config_1d.hpp"

namespace lss
{

wave_initial_data_config_1d_builder::wave_initial_data_config_1d_builder()
{
}

wave_initial_data_config_1d_builder &wave_initial_data_config_1d_builder::first_initial_condition(
    std::function<double(double)> const &first_initial_condition)
{
    first_initial_condition_ = first_initial_condition;
    return *this;
}

wave_initial_data_config_1d_builder &wave_initial_data_config_1d_builder::second_initial_condition(
    std::function<double(double)> const &second_initial_condition)
{
    second_initial_condition_ = second_initial_condition;
    return *this;
}

wave_initial_data_config_1d_ptr wave_initial_data_config_1d_builder::build()
{
    return std::make_shared<wave_initial_data_config_1d>(first_initial_condition_, second_initial_condition_);
}

} // namespace lss
