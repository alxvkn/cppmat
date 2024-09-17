#include <array>
#include <cassert>
#include <cstring>
#include <exception>
#include <iomanip>
#include <memory>

template <typename T>
class DynamicMatrix {
protected:
    unsigned _m, _n;
    T* _buffer;
public:
    static DynamicMatrix<T> Identity(unsigned n) {
        DynamicMatrix<T> mat = DynamicMatrix(n, n, {});

        for (unsigned i = 1; i <= mat._n; i++) {
            mat[i, i] = 1;
        }

        return mat;
    };
    DynamicMatrix(unsigned m, unsigned n, std::initializer_list<std::initializer_list<T>> init)
    : _m(m), _n(n), _buffer(new T[m * n]) {
        unsigned i = 0;
        for (const auto& row : init) {
            for (const auto& value : row) {
                _buffer[i++] = value;
            }
        }
    }
   ~DynamicMatrix() {
        delete[] _buffer;
    }

    T& operator[](unsigned i, unsigned j) {
        if (i < 1 or i > _m or j < 1 or j > _n) {
            throw std::exception();
        }
        return (T&)_buffer[_n * (i-1) + (j-1)];
    }

    const T& operator[](unsigned i, unsigned j) const {
        if (i < 1 or i > _m or j < 1 or j > _n) {
            throw std::exception();
        }
        return (const T&)_buffer[_n * (i-1) + (j-1)];
    }

    
    DynamicMatrix<T> transpose() const {
        DynamicMatrix<T> mat = DynamicMatrix(_n, _m, {});

        for (unsigned i = 1; i <= _m; i++) {
            for (unsigned j = 1; j <= _n; j++) {
                mat[j, i] = (*this)[i, j];
            }
        }

        return mat;
    }

    // TODO: operators +=, -=, *=, /=
    DynamicMatrix<T> operator+(const DynamicMatrix<T>& b) const {
        DynamicMatrix<T> mat = DynamicMatrix(_m, _n, {});

        for (unsigned i = 1; i <= _m; i++) {
            for (unsigned j = 1; j <= _n; j++) {
                mat[i, j] = (*this)[i, j] + b[i, j];
            }
        }

        return mat;
    }

    DynamicMatrix<T> operator-(const DynamicMatrix<T>& b) const {
        DynamicMatrix<T> mat = DynamicMatrix(_m, _n, {});

        for (unsigned i = 1; i <= _m; i++) {
            for (unsigned j = 1; j <= _n; j++) {
                mat[i, j] = (*this)[i, j] - b[i, j];
            }
        }

        return mat;
    }

    DynamicMatrix<T> operator*(const T b) const {
        DynamicMatrix<T> mat = DynamicMatrix(_m, _n, {});

        for (unsigned i = 1; i <= _m; i++) {
            for (unsigned j = 1; j <= _n; j++) {
                mat[i, j] = (*this)[i, j] * b;
            }
        }

        return mat;
    }

    DynamicMatrix<T> operator*(const DynamicMatrix<T>& b) const {
        assert(_n == b._m);
        DynamicMatrix<T> mat = DynamicMatrix(_m, b._n, {});

        for (unsigned i = 1; i <= _m; i++) {
            for (unsigned j = 1; j <= b._n; j++) {
                for (unsigned k = 1; k <= _n; k++) {
                    mat[i, j] += (*this)[i, k] * b[k, j];
                }
            }
        }

        return mat;
    }

    DynamicMatrix<T> operator/(const T b) const {
        if (b == 0) throw std::exception();

        DynamicMatrix<T> mat = DynamicMatrix(_m, _n, {});

        for (unsigned i = 1; i <= _m; i++) {
            for (unsigned j = 1; j <= _n; j++) {
                mat[i, j] = (*this)[i, j] / b;
            }
        }

        return mat;
    }

    DynamicMatrix<T> pow(const unsigned power) const {
        assert(_m == _n);

        if (power == 0) return DynamicMatrix<T>::Identity(_n);

        DynamicMatrix<T> mat = (*this);

        for (unsigned i = 1; i < power; i++) {
            mat = mat * (*this);
        }

        return mat;
    }

    friend std::ostream& operator<<(std::ostream& out, const DynamicMatrix<T>& mat) {
        // out << "T: " << typeid(T).name() << ", M: " << M << ", N: " << N << std::endl;
        for (unsigned i = 1; i <= mat._m; i++) {
            out << (i == 1 ? "( " : "  ");
            for (unsigned j = 1; j <= mat._n; j++) {
                // TODO: smart padding
                out << std::setw(4) << mat[i, j] << " ";
            }
            out << (i == mat._m ? ")" : "\n");
        }
        return out;
    };
};


