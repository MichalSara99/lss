#if !defined(_CONTAINER_2D_HPP_)
#define _CONTAINER_2D_HPP_

#include <functional>

#include "../../../common/lss_macros.hpp"
#include "../../../common/lss_utility.hpp"
#include "../../../containers/lss_container_2d.hpp"

namespace lss
{

using rmatrix = lss_containers::rmatrix;
using rmatrix_ptr = lss_containers::rmatrix_ptr;
using cmatrix = lss_containers::cmatrix;
using cmatrix_ptr = lss_containers::cmatrix_ptr;

struct rmatrix_builder
{
  private:
    std::size_t rows_;
    std::size_t columns_;
    double dvalue_;

  public:
    LSS_API explicit rmatrix_builder();

    LSS_API rmatrix_builder &rows(std::size_t rows);

    LSS_API rmatrix_builder &columns(std::size_t columns);

    LSS_API rmatrix_builder &default_value(double value);

    LSS_API rmatrix_ptr build();
};

struct cmatrix_builder
{
  private:
    std::size_t rows_;
    std::size_t columns_;
    double dvalue_;

  public:
    LSS_API explicit cmatrix_builder();

    LSS_API cmatrix_builder &rows(std::size_t rows);

    LSS_API cmatrix_builder &columns(std::size_t columns);

    LSS_API cmatrix_builder &default_value(double value);

    LSS_API cmatrix_ptr build();
};

} // namespace lss

#endif ///_CONTAINER_2D_HPP_
