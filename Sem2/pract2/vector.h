#include <cstdlib>
#include <iostream>

/*
 * T has to have various operators:
 * - T &operator+=(const T&)
 * - T &operator-=(const T&)
 * - T &operator*=(const Scalar)
 * - T &operator =(const T&)
 * - friend std::istream &operator>>(std::istream,       T&)
 * - friend std::ostream &operator<<(std::ostream, const T&)
 */
template <typename T, typename Scalar=T>
class MyVector {
    using Vect = MyVector<T, Scalar>;
public:
    // Constructors
    MyVector() = delete;

    MyVector(size_t len)
            : _len(len)
            ,_cords(nullptr)
    {
        _cords = new T[_len];
        for (auto i = 0; i < _len; i++) _cords[i] = T();
    }

    MyVector(const Vect &rhs): MyVector(rhs, rhs._len) {};

    MyVector(const Vect &rhs, size_t to_size)
            : _len(to_size)
            , _cords(nullptr)
    {
        _cords = new T[_len];
        auto min_l = (rhs._len < _len) ? rhs._len : _len;
        size_t i;
        for (i = 0; i < min_l; i++)
            _cords[i] = rhs._cords[i];
        for (; i < _len; i++) _cords[i] = T();
    }

    ~MyVector() {
        if (_cords != nullptr)
            delete[] _cords;
    }

    Vect &operator=(const Vect &rhs) {
        for (auto i = 0; i < ((_len < rhs._len) ? _len : rhs._len); i++)
            _cords[i] = rhs._cords[i];
        return *this;
    }


    // Addition
    Vect &operator+=(const Vect &rhs) {
        for (auto i = 0; i < ((_len < rhs._len) ? _len : rhs._len); i++)
            _cords[i] += rhs._cords[i];
        return *this;
    }
    friend Vect operator+(const Vect &left, const Vect &right) {
        auto to_size = (left._len > right._len) ? left._len : right._len;
        auto result = Vect(left, to_size);
        return result += right;
    }

    // Subtraction
    friend Vect operator-(const Vect &left, const Vect &right) {
        auto to_size = (left._len > right._len) ? left._len : right._len;
        auto result = Vect(left, to_size);
        return result -= right;
    }

    Vect &operator-=(const Vect &rhs) {
        for (auto i = 0; i < ((_len < rhs._len) ? _len : rhs._len); i++)
            _cords[i] -= rhs._cords[i];
        return *this;
    }
    friend Vect operator*(const Scalar lhs, const Vect &rhs) {
        auto result(rhs);
        return result * lhs;
    }

    // Multiplication
    Vect operator*(const Scalar rhs) {
        auto result(*this);
        return result *= rhs;
    }
    Vect &operator*=(const Scalar rhs) {
        for (auto i = 0; i < _len; i++)
            _cords[i] *= rhs;
        return *this;
    }

    // Comparsion
    bool operator==(const Vect &rhs) {
        bool equal = _len == rhs._len;
        for (auto i = 0; equal && i < _len; i++)
            equal = _cords[i] == rhs._cords[i];
        return equal;
    }

    // Input/Output
    friend std::ostream &operator<<(std::ostream &os, const Vect &obj) {
        os << 'V' << obj._len << '[';
        for (auto i = 0; i < obj._len; i++)
            os << obj._cords[i] << '|';
        return os << ']';
    }
    friend std::istream &operator>>(std::istream &is, Vect &obj) {
        for (auto i = 0; i < obj._len; i++)
            is >> obj._cords[i];
        return is;
    }

protected:
    T *_cords;
    const size_t _len;

};