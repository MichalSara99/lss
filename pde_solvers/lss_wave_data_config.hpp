#if !defined(_LSS_WAVE_DATA_CONFIG_HPP_)
#define _LSS_WAVE_DATA_CONFIG_HPP_

#include <functional>

#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"

namespace lss_pde_solvers
{

using lss_utility::sptr_t;

/**
    1D wave_coefficient_data_config structure
 */
struct wave_coefficient_data_config_1d
{
  private:
    std::function<double(double, double)> a_coeff_;
    std::function<double(double, double)> b_coeff_;
    std::function<double(double, double)> c_coeff_;
    std::function<double(double, double)> d_coeff_;

    explicit wave_coefficient_data_config_1d() = delete;

    void initialize();

  public:
    explicit wave_coefficient_data_config_1d(std::function<double(double, double)> const &a_coefficient,
                                             std::function<double(double, double)> const &b_coefficient,
                                             std::function<double(double, double)> const &c_coefficient,
                                             std::function<double(double, double)> const &d_coefficient);

    LSS_API std::function<double(double, double)> const &a_coefficient() const;

    LSS_API std::function<double(double, double)> const &b_coefficient() const;

    LSS_API std::function<double(double, double)> const &c_coefficient() const;

    LSS_API std::function<double(double, double)> const &d_coefficient() const;
};

/**
    2D wave_coefficient_data_config structure
 */
struct wave_coefficient_data_config_2d
{
};

using wave_coefficient_data_config_1d_ptr = sptr_t<wave_coefficient_data_config_1d>;

using wave_coefficient_data_config_2d_ptr = sptr_t<wave_coefficient_data_config_2d>;

/**
    1D wave_initial_data_config structure
 */
struct wave_initial_data_config_1d
{
  private:
    std::function<double(double)> first_initial_condition_;
    std::function<double(double)> second_initial_condition_;

    explicit wave_initial_data_config_1d() = delete;

  public:
    explicit wave_initial_data_config_1d(std::function<double(double)> const &first_initial_condition,
                                         std::function<double(double)> const &second_initial_condition);

    LSS_API std::function<double(double)> const &first_initial_condition() const;

    LSS_API std::function<double(double)> const &second_initial_condition() const;
};

/**
    2D wave_initial_data_config structure
 */
struct wave_initial_data_config_2d
{
};

using wave_initial_data_config_1d_ptr = sptr_t<wave_initial_data_config_1d>;

using wave_initial_data_config_2d_ptr = sptr_t<wave_initial_data_config_2d>;

/**
    1D wave_source_data_config structure
 */
struct wave_source_data_config_1d
{
  private:
    std::function<double(double, double)> wave_source_;

    explicit wave_source_data_config_1d() = delete;

  public:
    explicit wave_source_data_config_1d(std::function<double(double, double)> const &wave_source);

    LSS_API std::function<double(double, double)> const &wave_source() const;
};

/**
    2D wave_source_data_config structure
 */
struct wave_source_data_config_2d
{
};

using wave_source_data_config_1d_ptr = sptr_t<wave_source_data_config_1d>;

using wave_source_data_config_2d_ptr = sptr_t<wave_source_data_config_2d>;

/**
    1D wave_data_config structure
 */
struct wave_data_config_1d
{
  private:
    wave_coefficient_data_config_1d_ptr coefficient_data_cfg_;
    wave_initial_data_config_1d_ptr initial_data_cfg_;
    wave_source_data_config_1d_ptr source_data_cfg_;

    void initialize();

    explicit wave_data_config_1d() = delete;

  public:
    explicit wave_data_config_1d(wave_coefficient_data_config_1d_ptr const &coefficient_data_config,
                                 wave_initial_data_config_1d_ptr const &initial_data_config,
                                 wave_source_data_config_1d_ptr const &source_data_config = nullptr);

    ~wave_data_config_1d();

    LSS_API wave_source_data_config_1d_ptr const &source_data_config() const;

    LSS_API std::function<double(double)> const &first_initial_condition() const;

    LSS_API std::function<double(double)> const &second_initial_condition() const;

    LSS_API std::function<double(double, double)> const &a_coefficient() const;

    LSS_API std::function<double(double, double)> const &b_coefficient() const;

    LSS_API std::function<double(double, double)> const &c_coefficient() const;

    LSS_API std::function<double(double, double)> const &d_coefficient() const;
};

/**
    2D heat_data_config structure
 */
struct wave_data_config_2d
{
};

using wave_data_config_1d_ptr = sptr_t<wave_data_config_1d>;

using wave_data_config_2d_ptr = sptr_t<wave_data_config_2d>;

} // namespace lss_pde_solvers

#endif ///_LSS_WAVE_DATA_CONFIG_HPP_
