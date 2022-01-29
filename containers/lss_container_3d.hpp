/**

    @file      lss_container_3d.hpp
    @brief     Represents 3D row, column and layer-wise container
    @details   ~
    @author    Michal Sara
    @date      4.01.2022
    @copyright © Michal Sara, 2022. All right reserved.

**/
#pragma once

#pragma once
#if !defined(_LSS_CONTAINER_3D_HPP_)
#define _LSS_CONTAINER_3D_HPP_

#include "../common/lss_enumerations.hpp"
#include "../common/lss_macros.hpp"
#include "../common/lss_utility.hpp"
#include "lss_container_2d.hpp"
#include <typeinfo>
#include <vector>

namespace lss_containers
{

using lss_enumerations::by_enum;
using lss_utility::container_t;
using lss_utility::sptr_t;

class container_3d_base
{
  protected:
    std::size_t rows_;
    std::size_t columns_;
    std::size_t layers_;

  public:
    explicit container_3d_base();
    explicit container_3d_base(std::size_t rows, std::size_t columns, std::size_t layers);

    virtual ~container_3d_base();

    virtual void from_data(std::vector<double> const &data) = 0;
    virtual container_t const data() const = 0;

    LSS_API std::size_t rows() const;
    LSS_API std::size_t columns() const;
    LSS_API std::size_t layers() const;
    LSS_API std::size_t total_size() const;
};

template <by_enum by> class container_3d
{
};

/**

    @class   container_3d
    @brief   rowplane-wise 3D conatiner object
    @details ~

**/
template <> class container_3d<by_enum::RowPlane> : public container_3d_base
{
  private:
    std::vector<container_2d<by_enum::Column>> data_;

    explicit container_3d();

  public:
    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers);
    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value);

    ~container_3d();

    container_3d(container_3d const &copy);
    container_3d(container_3d &&other) noexcept;
    container_3d(container_3d<by_enum::ColumnPlane> const &copy);
    container_3d(container_3d<by_enum::LayerPlane> const &copy);

    container_3d &operator=(container_3d const &copy);
    container_3d &operator=(container_3d &&other) noexcept;
    container_3d &operator=(container_3d<by_enum::ColumnPlane> const &copy);
    container_3d &operator=(container_3d<by_enum::LayerPlane> const &copy);

    LSS_API void from_data(std::vector<double> const &data) override;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @param  lay_idx
        @retval value from container_3d at potision (row_idx,col_idx,lay_idx)
    **/
    LSS_API double operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const;

    /**
        @brief
        @param  row_idx
        @retval row plane container from container_3d at position (row_idx)
    **/
    LSS_API container_2d<by_enum::Column> operator()(std::size_t row_idx) const;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @param  lay_idx
        @retval value from container_3d at potision (row_idx,col_idx,lay_idx)
    **/
    LSS_API double at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const;

    /**
        @brief
        @param  row_idx
        @retval row plane container from container_3d at potision (row_idx)
    **/
    LSS_API container_2d<by_enum::Column> at(std::size_t row_idx) const;

    /**
        @brief place row plane container at position (row_idx)
        @param row_idx
        @param cont
    **/
    LSS_API void operator()(std::size_t row_idx, container_2d<by_enum::Column> const &cont);

    /**
        @brief place value at position (row_idx,col_idx,lay_idx)
        @param row_idx
        @param col_idx
        @param lay_idx
        @param value
    **/
    LSS_API void operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx, double value);

    /**
        @brief
        @retval data as flat vector row-wise
    **/
    LSS_API container_t const data() const override;
};

/**

    @class   container_3d
    @brief   columnplane-wise 3D conatiner object
    @details ~

**/
template <> class container_3d<by_enum::ColumnPlane> : public container_3d_base
{
  private:
    std::vector<container_2d<by_enum::Column>> data_;

    explicit container_3d();

  public:
    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers);
    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value);

    ~container_3d();

    container_3d(container_3d const &copy);
    container_3d(container_3d &&other) noexcept;
    container_3d(container_3d<by_enum::RowPlane> const &copy);
    container_3d(container_3d<by_enum::LayerPlane> const &copy);

    container_3d &operator=(container_3d const &copy);
    container_3d &operator=(container_3d &&other) noexcept;
    container_3d &operator=(container_3d<by_enum::RowPlane> const &copy);
    container_3d &operator=(container_3d<by_enum::LayerPlane> const &copy);

    LSS_API void from_data(std::vector<double> const &data) override;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @param  lay_idx
        @retval value from container_3d at potision (row_idx,col_idx,lay_idx)
    **/
    LSS_API double operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const;

    /**
        @brief
        @param  col_idx
        @retval column container from container_3d at position (col_idx)
    **/
    LSS_API container_2d<by_enum::Column> operator()(std::size_t col_idx) const;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @param  lay_idx
        @retval value from container_3d at potision (row_idx,col_idx,lay_idx)
    **/
    LSS_API double at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const;

    /**
        @brief
        @param  col_idx
        @retval column container from container_3d at potision (col_idx)
    **/
    LSS_API container_2d<by_enum::Column> at(std::size_t col_idx) const;

    /**
        @brief place column container at position (col_idx)
        @param col_idx
        @param cont
    **/
    LSS_API void operator()(std::size_t col_idx, container_2d<by_enum::Column> const &cont);

    /**
        @brief place value at position (row_idx,col_idx,lay_idx)
        @param row_idx
        @param col_idx
        @param lay_idx
        @param value
    **/
    LSS_API void operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx, double value);

    /**
        @brief
        @retval data as flat vector row-wise
    **/
    LSS_API container_t const data() const override;
};

/**

    @class   container_3d
    @brief   layerplane-wise 3D conatiner object
    @details ~

**/
template <> class container_3d<by_enum::LayerPlane> : public container_3d_base
{
  private:
    std::vector<container_2d<by_enum::Row>> data_;

    explicit container_3d();

  public:
    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers);
    explicit container_3d(std::size_t rows, std::size_t columns, std::size_t layers, double value);

    ~container_3d();

    container_3d(container_3d const &copy);
    container_3d(container_3d &&other) noexcept;
    container_3d(container_3d<by_enum::RowPlane> const &copy);
    container_3d(container_3d<by_enum::ColumnPlane> const &copy);

    container_3d &operator=(container_3d const &copy);
    container_3d &operator=(container_3d &&other) noexcept;
    container_3d &operator=(container_3d<by_enum::RowPlane> const &copy);
    container_3d &operator=(container_3d<by_enum::ColumnPlane> const &copy);

    LSS_API void from_data(std::vector<double> const &data) override;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @param  lay_idx
        @retval value from container_3d at potision (row_idx,col_idx,lay_idx)
    **/
    LSS_API double operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const;

    /**
        @brief
        @param  lay_idx
        @retval layer container from container_3d at position (lay_idx)
    **/
    LSS_API container_2d<by_enum::Row> operator()(std::size_t lay_idx) const;

    /**
        @brief
        @param  row_idx
        @param  col_idx
        @param  lay_idx
        @retval value from container_3d at potision (row_idx,col_idx,lay_idx)
    **/
    LSS_API double at(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx) const;

    /**
        @brief
        @param  lay_idx
        @retval layer container from container_3d at potision (lay_idx)
    **/
    LSS_API container_2d<by_enum::Row> at(std::size_t lay_idx) const;

    /**
        @brief place layer container at position (lay_idx)
        @param lay_idx
        @param cont
    **/
    LSS_API void operator()(std::size_t lay_idx, container_2d<by_enum::Row> const &cont);

    /**
        @brief place value at position (row_idx,col_idx,lay_idx)
        @param row_idx
        @param col_idx
        @param lay_idx
        @param value
    **/
    LSS_API void operator()(std::size_t row_idx, std::size_t col_idx, std::size_t lay_idx, double value);

    /**
        @brief
        @retval data as flat vector row-wise
    **/
    LSS_API container_t const data() const override;
};

using rmatrix_3d = container_3d<by_enum::RowPlane>;
using cmatrix_3d = container_3d<by_enum::ColumnPlane>;
using lmatrix_3d = container_3d<by_enum::LayerPlane>;

using rmatrix_3d_ptr = sptr_t<rmatrix_3d>;
using cmatrix_3d_ptr = sptr_t<cmatrix_3d>;
using lmatrix_3d_ptr = sptr_t<lmatrix_3d>;

} // namespace lss_containers

#endif ///_LSS_CONTAINER_3D_HPP_
