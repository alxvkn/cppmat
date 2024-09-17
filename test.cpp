#include <iostream>
#include "Matrix.hpp"

#define dbgout(expr) do { std::cout << #expr":\n" << (expr) << std::endl; } while (0)
#define log(msg) do { std::cout << msg << std::endl; } while (0)

int main() {
    // Matrix<double, 3, 4> mat {
    //     { 9, 8, 7, 6 },
    //     { 5, 4, 3, 2 },
    //     { 1, 2, 3, 4 },
    // };
    // dbgout(mat);
    // mat[1, 2] = 3.3;
    // dbgout(mat);
    //
    // const Matrix<double, 3, 4> negative_mat {
    //     { -1, -1, -1, -1 },
    //     { -1, -1, -1, -1 },
    //     { -1, -1, -1, -1 },
    // };
    // dbgout(negative_mat);
    //
    // dbgout(mat - negative_mat);
    //
    // dbgout(mat + negative_mat);
    //
    // dbgout(mat * 2);
    // dbgout(mat / 2);

    // try {
    //     dbgout(mat / 0);
    // } catch(std::exception e) {
    //     log("exception thrown when trying to divide mat by 0");
    // }

    // try {
    //     mat[0, 0] = 2;
    // } catch (std::exception e) {
    //     log("exception thrown when trying to set value at [0, 0]");
    // }
    // dbgout(mat);

    // Matrix<char, -1, 0> invalid_mat{};
    // std::cout << invalid_mat << std::endl;

    // Matrix<double, 1, 4> row;
    // row[1, 1] = 1;
    // row[1, 2] = 2;
    // row[1, 3] = 3;
    // row[1, 4] = 4;
    // dbgout(row);
    //
    // dbgout(row.transpose());

    // Matrix<double, 3, 2> A {
    //     { 5, 2 },
    //     { 7, 8 },
    //     { 3, -2 },
    // };
    //
    // Matrix<double, 2, 4> B {
    //     { 1, 2, 3, 6 },
    //     { 1, 2, 5, 2 },
    // };
    //
    // dbgout(A);
    // dbgout(B);
    // dbgout(A * B);

    Matrix<double, 3, 3> square_mat {
        { 3, 3, 3 },
        { 3, 3, 3 },
        { 3, 3, 3 },
    };
    dbgout(square_mat);
    dbgout(square_mat.pow(2));
    dbgout(square_mat.pow(1));
    dbgout(square_mat.pow(0));

    auto identity_mat = Matrix<double, 2, 2>::Identity();
    dbgout(identity_mat);

    return 0;
}
