#include <array>
#include <exception>
#include <iomanip>

template <typename T, unsigned M, unsigned N>
class Matrix {
protected:
    std::array<T, M*N> buffer = {};
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
