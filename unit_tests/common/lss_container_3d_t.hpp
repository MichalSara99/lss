#if !defined(_CONTAINER_3D_T_HPP_)
#define _CONTAINER_3D_T_HPP_

#include "../../containers/lss_container_3d.hpp"
#include <iostream>
#include <random>
#include <string>

using lss_containers::container_3d;
using lss_enumerations::by_enum;

void print_container(container_3d<by_enum::Row> const &cn, std::string const &str = "")
{
    std::cout << str << ":\n";
    for (std::size_t l = 0; l < cn.layers(); ++l)
    {
        for (std::size_t r = 0; r < cn.rows(); ++r)
        {
            for (std::size_t c = 0; c < cn.columns(); ++c)
            {
                std::cout << cn(r, c, l) << ",";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void basic_rcontainer_3d_test()
{

    auto const rows = 3;
    auto const cols = 4;
    auto const lays = 2;

    container_3d<by_enum::Row> matr3d(rows, cols, lays);
    // 0.layer:
    matr3d(0, 0, 0, 0);
    matr3d(0, 1, 0, 1);
    matr3d(0, 2, 0, 2);
    matr3d(0, 3, 0, 3);
    //
    matr3d(1, 0, 0, 4);
    matr3d(1, 1, 0, 5);
    matr3d(1, 2, 0, 6);
    matr3d(1, 3, 0, 7);
    //
    matr3d(2, 0, 0, 8);
    matr3d(2, 1, 0, 9);
    matr3d(2, 2, 0, 10);
    matr3d(2, 3, 0, 11);
    // 1.layer:
    matr3d(0, 0, 1, 12);
    matr3d(0, 1, 1, 13);
    matr3d(0, 2, 1, 14);
    matr3d(0, 3, 1, 15);
    //
    matr3d(1, 0, 1, 16);
    matr3d(1, 1, 1, 17);
    matr3d(1, 2, 1, 18);
    matr3d(1, 3, 1, 19);
    //
    matr3d(2, 0, 1, 20);
    matr3d(2, 1, 1, 21);
    matr3d(2, 2, 1, 22);
    matr3d(2, 3, 1, 23);

    print_container(matr3d, "matr3d");
    std::cout << "number of rows: " << matr3d.rows() << "\n";
    std::cout << "number of columns: " << matr3d.columns() << "\n";
    std::cout << "number of layers: " << matr3d.layers() << "\n";

    auto const data = matr3d.data();
    std::cout << "data: \n";
    for (auto const &e : data)
    {
        std::cout << e << ",";
    }
    std::cout << "\n";
    auto const &rl21 = matr3d.at(2, 1);
    std::cout << "row: 2, layer: 1: \n";
    for (auto const &e : rl21)
    {
        std::cout << e << ",";
    }
    std::cout << "\n";

    std::cout << "Construct 3D matrix from data:\n";
    std::uniform_real_distribution<double> uni(1.0, 20.0);
    std::random_device rd;
    std::size_t total = rows * cols * lays;
    std::vector<double> v(total);
    std::generate(v.begin(), v.end(), [&]() { return uni(rd); });
    for (std::size_t t = 0; t < total; ++t)
    {
        std::cout << v[t] << ",";
    }
    std::cout << "\n";
    matr3d.from_data(v);
    print_container(matr3d, "new matr3d");
}

void basic_ccontainer_3d_test()
{
    auto const rows = 3;
    auto const cols = 4;
    auto const lays = 2;

    container_3d<by_enum::Column> matc3d(rows, cols, lays);
    // 0.layer:
    matc3d(0, 0, 0, 0);
    matc3d(0, 1, 0, 1);
    matc3d(0, 2, 0, 2);
    matc3d(0, 3, 0, 3);
    //
    matc3d(1, 0, 0, 4);
    matc3d(1, 1, 0, 5);
    matc3d(1, 2, 0, 6);
    matc3d(1, 3, 0, 7);
    //
    matc3d(2, 0, 0, 8);
    matc3d(2, 1, 0, 9);
    matc3d(2, 2, 0, 10);
    matc3d(2, 3, 0, 11);
    // 1.layer:
    matc3d(0, 0, 1, 12);
    matc3d(0, 1, 1, 13);
    matc3d(0, 2, 1, 14);
    matc3d(0, 3, 1, 15);
    //
    matc3d(1, 0, 1, 16);
    matc3d(1, 1, 1, 17);
    matc3d(1, 2, 1, 18);
    matc3d(1, 3, 1, 19);
    //
    matc3d(2, 0, 1, 20);
    matc3d(2, 1, 1, 21);
    matc3d(2, 2, 1, 22);
    matc3d(2, 3, 1, 23);

    print_container(matc3d, "matc3d");
    std::cout << "number of rows: " << matc3d.rows() << "\n";
    std::cout << "number of columns: " << matc3d.columns() << "\n";
    std::cout << "number of layers: " << matc3d.layers() << "\n";

    auto const data = matc3d.data();
    std::cout << "data: \n";
    for (auto const &e : data)
    {
        std::cout << e << ",";
    }
    std::cout << "\n";
    auto const &cl21 = matc3d.at(2, 1);
    std::cout << "column: 2, layer: 1: \n";
    for (auto const &e : cl21)
    {
        std::cout << e << ",";
    }
    std::cout << "\n";

    std::cout << "Construct 3D matrix from data:\n";
    std::uniform_real_distribution<double> uni(1.0, 20.0);
    std::random_device rd;
    std::size_t total = rows * cols * lays;
    std::vector<double> v(total);
    std::generate(v.begin(), v.end(), [&]() { return uni(rd); });
    for (std::size_t t = 0; t < total; ++t)
    {
        std::cout << v[t] << ",";
    }
    std::cout << "\n";
    matc3d.from_data(v);
    print_container(matc3d, "new matc3d");
}

void basic_lcontainer_3d_test()
{
    auto const rows = 3;
    auto const cols = 4;
    auto const lays = 2;

    container_3d<by_enum::Layer> matl3d(rows, cols, lays);
    // 0.layer:
    matl3d(0, 0, 0, 0);
    matl3d(0, 1, 0, 1);
    matl3d(0, 2, 0, 2);
    matl3d(0, 3, 0, 3);
    //
    matl3d(1, 0, 0, 4);
    matl3d(1, 1, 0, 5);
    matl3d(1, 2, 0, 6);
    matl3d(1, 3, 0, 7);
    //
    matl3d(2, 0, 0, 8);
    matl3d(2, 1, 0, 9);
    matl3d(2, 2, 0, 10);
    matl3d(2, 3, 0, 11);
    // 1.layer:
    matl3d(0, 0, 1, 12);
    matl3d(0, 1, 1, 13);
    matl3d(0, 2, 1, 14);
    matl3d(0, 3, 1, 15);
    //
    matl3d(1, 0, 1, 16);
    matl3d(1, 1, 1, 17);
    matl3d(1, 2, 1, 18);
    matl3d(1, 3, 1, 19);
    //
    matl3d(2, 0, 1, 20);
    matl3d(2, 1, 1, 21);
    matl3d(2, 2, 1, 22);
    matl3d(2, 3, 1, 23);

    print_container(matl3d, "matl3d");
    std::cout << "number of rows: " << matl3d.rows() << "\n";
    std::cout << "number of columns: " << matl3d.columns() << "\n";
    std::cout << "number of layers: " << matl3d.layers() << "\n";

    auto const data = matl3d.data();
    std::cout << "data: \n";
    for (auto const &e : data)
    {
        std::cout << e << ",";
    }
    std::cout << "\n";
    auto const &rc21 = matl3d.at(2, 1);
    std::cout << "row: 2, column: 1: \n";
    for (auto const &e : rc21)
    {
        std::cout << e << ",";
    }
    std::cout << "\n";

    std::cout << "Construct 3D matrix from data:\n";
    std::uniform_real_distribution<double> uni(1.0, 20.0);
    std::random_device rd;
    std::size_t total = rows * cols * lays;
    std::vector<double> v(total);
    std::generate(v.begin(), v.end(), [&]() { return uni(rd); });
    for (std::size_t t = 0; t < total; ++t)
    {
        std::cout << v[t] << ",";
    }
    std::cout << "\n";
    matl3d.from_data(v);
    print_container(matl3d, "new matl3d");
}

#endif ///_CONTAINER_3D_T_HPP_
