#include "lss_heat_data_transform.hpp"

namespace lss_pde_solvers
{

void heat_data_transform_1d::initialize(heat_data_config_1d_ptr const &heat_data_config,
                                        grid_transform_config_1d_ptr const grid_transform_config)
{
    auto const A = heat_data_config->a_coefficient();
    auto const B = heat_data_config->b_coefficient();
    auto const C = heat_data_config->c_coefficient();
    auto const a = grid_transform_config->a_derivative();
    auto const b = grid_transform_config->b_derivative();
    auto const init = heat_data_config->initial_condition();
    auto const &src_cfg = heat_data_config->source_data_config();
    std::function<double(double, double)> src = nullptr;
    if (src_cfg)
    {
        src = src_cfg->heat_source();
        is_heat_source_set_ = true;
        src_coeff_ = [=](double t, double zeta) {
            auto const x = grid_1d::transformed_value(grid_transform_config, zeta);
            return src(t, x);
        };
    }
    a_coeff_ = [=](double t, double zeta) {
        auto const x = grid_1d::transformed_value(grid_transform_config, zeta);
        return (A(t, x) / (a(zeta) * a(zeta)));
    };

    b_coeff_ = [=](double t, double zeta) {
        auto const x = grid_1d::transformed_value(grid_transform_config, zeta);
        auto const a_val = a(zeta);
        auto const first = B(t, x) / a_val;
        auto const second = (A(t, x) * b(zeta)) / (a_val * a_val * a_val);
        return (first - second);
    };

    c_coeff_ = [=](double t, double zeta) {
        auto const x = grid_1d::transformed_value(grid_transform_config, zeta);
        return C(t, x);
    };

    init_coeff_ = [=](double zeta) {
        auto const x = grid_1d::transformed_value(grid_transform_config, zeta);
        return init(x);
    };
}

heat_data_transform_1d::heat_data_transform_1d(heat_data_config_1d_ptr const &heat_data_config,
                                               grid_transform_config_1d_ptr const grid_transform_config)
{
    initialize(heat_data_config, grid_transform_config);
}

heat_data_transform_1d ::~heat_data_transform_1d()
{
}

bool const &heat_data_transform_1d::is_heat_source_set() const
{
    return is_heat_source_set_;
}

std::function<double(double, double)> heat_data_transform_1d::heat_source() const
{
    return (is_heat_source_set() == true) ? src_coeff_ : nullptr;
}

std::function<double(double)> const &heat_data_transform_1d::initial_condition() const
{
    return init_coeff_;
}

std::function<double(double, double)> const &heat_data_transform_1d::a_coefficient() const
{
    return a_coeff_;
}

std::function<double(double, double)> const &heat_data_transform_1d::b_coefficient() const
{
    return b_coeff_;
}

std::function<double(double, double)> const &heat_data_transform_1d::c_coefficient() const
{
    return c_coeff_;
}

void heat_data_transform_2d::initialize(heat_data_config_2d_ptr const &heat_data_config,
                                        grid_transform_config_2d_ptr const &grid_transform_config)
{
    auto const A = heat_data_config->a_coefficient();
    auto const B = heat_data_config->b_coefficient();
    auto const C = heat_data_config->c_coefficient();
    auto const D = heat_data_config->d_coefficient();
    auto const E = heat_data_config->e_coefficient();
    auto const F = heat_data_config->f_coefficient();
    auto const a = grid_transform_config->a_derivative();
    auto const b = grid_transform_config->b_derivative();
    auto const c = grid_transform_config->c_derivative();
    auto const d = grid_transform_config->d_derivative();
    auto const init = heat_data_config->initial_condition();
    auto const &src_cfg = heat_data_config->source_data_config();
    std::function<double(double, double, double)> src = nullptr;
    if (src_cfg)
    {
        src = src_cfg->heat_source();
        is_heat_source_set_ = true;
        src_coeff_ = [=](double t, double zeta, double eta) {
            auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
            auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
            return src(t, x, y);
        };
    }
    a_coeff_ = [=](double t, double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        return (A(t, x, y) / (a(zeta) * a(zeta)));
    };

    b_coeff_ = [=](double t, double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        return (B(t, x, y) / (b(eta) * b(eta)));
    };

    c_coeff_ = [=](double t, double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        return (C(t, x, y) / (a(zeta) * b(eta)));
    };

    d_coeff_ = [=](double t, double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        auto const a_val = a(zeta);
        auto const first = D(t, x, y) / a_val;
        auto const second = (A(t, x, y) * c(zeta)) / (a_val * a_val * a_val);
        return (first - second);
    };

    e_coeff_ = [=](double t, double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        auto const b_val = b(eta);
        auto const first = E(t, x, y) / b_val;
        auto const second = (B(t, x, y) * d(eta)) / (b_val * b_val * b_val);
        return (first - second);
    };

    f_coeff_ = [=](double t, double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        return F(t, x, y);
    };

    init_coeff_ = [=](double zeta, double eta) {
        auto const x = grid_2d::transformed_value_1(grid_transform_config, zeta);
        auto const y = grid_2d::transformed_value_2(grid_transform_config, eta);
        return init(x, y);
    };
}

heat_data_transform_2d::heat_data_transform_2d(heat_data_config_2d_ptr const &heat_data_config,
                                               grid_transform_config_2d_ptr const &grid_transform_config)
{
    initialize(heat_data_config, grid_transform_config);
}

heat_data_transform_2d ::~heat_data_transform_2d()
{
}

bool const &heat_data_transform_2d::is_heat_source_set() const
{
    return is_heat_source_set_;
}

std::function<double(double, double, double)> heat_data_transform_2d::heat_source() const
{
    return (is_heat_source_set() == true) ? src_coeff_ : nullptr;
}

std::function<double(double, double)> const &heat_data_transform_2d::initial_condition() const
{
    return init_coeff_;
}

std::function<double(double, double, double)> const &heat_data_transform_2d::a_coefficient() const
{
    return a_coeff_;
}

std::function<double(double, double, double)> const &heat_data_transform_2d::b_coefficient() const
{
    return b_coeff_;
}

std::function<double(double, double, double)> const &heat_data_transform_2d::c_coefficient() const
{
    return c_coeff_;
}

std::function<double(double, double, double)> const &heat_data_transform_2d::d_coefficient() const
{
    return d_coeff_;
}

std::function<double(double, double, double)> const &heat_data_transform_2d::e_coefficient() const
{
    return e_coeff_;
}

std::function<double(double, double, double)> const &heat_data_transform_2d::f_coefficient() const
{
    return f_coeff_;
}

} // namespace lss_pde_solvers
