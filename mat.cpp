#include <exception>
#include <iomanip>
#include <iostream>

#define dbgout(expr) do { std::cout << #expr":\n" << (expr) << std::endl; } while (0)
#define log(msg) do { std::cout << msg << std::endl; } while (0)

template <typename T, unsigned M, unsigned N>
class Matrix {
protected:
    T buffer[M*N] = {};
public:
    Matrix() = default;
    static Matrix<T, N, M> Identity() {
        static_assert(N == M);
        Matrix<T, N, M> mat;

        for (unsigned i = 1; i <= N; i++) {
            mat[i, i] = 1;
        }

        return mat;
    };
    // Matrix(const T** mat) {
    //     for (unsigned i = 0; i < M; i++) {
    //         for (unsigned j = 0; j < N; j++) {
    //             buffer[M * i + j] = mat[M * i + j];
    //         }
    //     }
    // }
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        unsigned i = 0;
        for (const auto& row : init) {
            for (const auto& value : row) {
                buffer[i++] = value;
            }
        }
    }
   ~Matrix() {}

    T& operator[](unsigned i, unsigned j) {
        if (i < 1 or i > M or j < 1 or j > N) {
            throw std::exception();
        }
        return (T&)buffer[N * (i-1) + (j-1)];
    }

    const T& operator[](unsigned i, unsigned j) const {
        if (i < 1 or i > M or j < 1 or j > N) {
            throw std::exception();
        }
        return (const T&)buffer[N * (i-1) + (j-1)];
    }

    
    Matrix<T, N, M> transpose() const {
        Matrix<T, N, M> mat = Matrix<T, N, M>();

        for (unsigned i = 1; i <= M; i++) {
            for (unsigned j = 1; j <= N; j++) {
                mat[j, i] = (*this)[i, j];
            }
        }

        return mat;
    }

    // TODO: operators +=, -=, *=, /=
    Matrix<T, M, N> operator+(const Matrix<T, M, N>& b) const {
        Matrix<T, M, N> mat;

        for (unsigned i = 1; i <= M; i++) {
            for (unsigned j = 1; j <= N; j++) {
                mat[i, j] = (*this)[i, j] + b[i, j];
            }
        }

        return mat;
    }

    Matrix<T, M, N> operator-(const Matrix<T, M, N>& b) const {
        Matrix<T, M, N> mat;

        for (unsigned i = 1; i <= M; i++) {
            for (unsigned j = 1; j <= N; j++) {
                mat[i, j] = (*this)[i, j] - b[i, j];
            }
        }

        return mat;
    }

    Matrix<T, M, N> operator*(const T b) const {
        Matrix<T, M, N> mat;

        for (unsigned i = 1; i <= M; i++) {
            for (unsigned j = 1; j <= N; j++) {
                mat[i, j] = (*this)[i, j] * b;
            }
        }

        return mat;
    }

    template <unsigned M_, unsigned N_>
    Matrix<T, M, N_> operator*(const Matrix<T, M_, N_>& b) const {
        static_assert(N == M_);
        Matrix<T, M, N_> mat;

        for (unsigned i = 1; i <= M; i++) {
            for (unsigned j = 1; j <= N_; j++) {
                for (unsigned k = 1; k <= N; k++) {
                    mat[i, j] += (*this)[i, k] * b[k, j];
                }
            }
        }

        return mat;
    }

    Matrix<T, M, N> operator/(const T b) const {
        if (b == 0) throw std::exception();

        Matrix<T, M, N> mat;

        for (unsigned i = 1; i <= M; i++) {
            for (unsigned j = 1; j <= N; j++) {
                mat[i, j] = (*this)[i, j] / b;
            }
        }

        return mat;
    }

    Matrix<T, M, N> pow(const unsigned power) const {
        static_assert(M == N, "Only a square matrix can be raised to a power.");

        if (power == 0) return Matrix<T, M, N>::Identity();

        Matrix<T, M, N> mat = (*this);

        for (unsigned i = 1; i < power; i++) {
            mat = mat * (*this);
        }

        return mat;
    }

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T, M, N>& mat) {
        // out << "T: " << typeid(T).name() << ", M: " << M << ", N: " << N << std::endl;
        for (unsigned i = 1; i <= M; i++) {
            out << (i == 1 ? "( " : "  ");
            for (unsigned j = 1; j <= N; j++) {
                // TODO: smart padding
                out << std::setw(4) << mat[i, j] << " ";
            }
            out << (i == M ? ")" : "\n");
        }
        return out;
    };
};

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
