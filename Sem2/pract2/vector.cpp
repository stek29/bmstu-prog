//#include <cstdlib>
//#include <algorithm>
//#include <array>
//#include "vector.h"
//
//template <typename T, typename Scalar=T>
//MyVector<T, Scalar> &operator=(const MyVector<T, Scalar> &rhs) {
//        _len = rhs._len;
//        for (auto i = 0; i < _len; i++) _cords[i] = rhs._cords[i];
//        return *this;
//    };
//
//    MyVector(const Vect &rhs): MyVector(rhs, rhs._len) {};
//
//    MyVector(const Vect &rhs, size_t to_size)
//            : _len(to_size)
//            , _cords(nullptr)
//    {
//        _cords = new T[_len];
//        auto min_l = (rhs._len < _len) ? rhs._len : _len;
//        size_t i;
//        for (i = 0; i < min_l; i++)
//            _cords[i] = rhs._cords[i];
//        for (; i < _len; i++) _cords[i] = T();
//    }
//
//    friend Vect operator+(const Vect &left, const Vect &right) {
//        auto to_size = (left._len > right._len) ? left._len : right._len;
//        auto result = Vect(left, to_size);
//        return result += right;
//    }
//
//    Vect &operator+=(const Vect &rhs) {
//        for (auto i = 0; i < ((_len < rhs._len) ? _len : rhs._len); i++)
//            _cords[i] += rhs._cords[i];
//        return *this;
//    }
//    friend Vect operator-(const Vect &left, const Vect &right) {
//        auto to_size = (left._len > right._len) ? left._len : right._len;
//        auto result = Vect(left, to_size);
//        return result -= right;
//    }
//
//    Vect &operator-=(const Vect &rhs) {
//        for (auto i = 0; i < ((_len < rhs._len) ? _len : rhs._len); i++)
//            _cords[i] -= rhs._cords[i];
//        return *this;
//    }
//
//    friend Vect operator*(const Scalar lhs, const Vect &rhs) {
//        auto result(rhs);
//        return result * lhs;
//    }
//
//    Vect operator*(const Scalar rhs) {
//        auto result(*this);
//        return result *= rhs;
//    }
//
//    Vect &operator*=(const Scalar rhs) {
//        for (auto i = 0; i < _len; i++)
//            _cords[i] *= rhs;
//        return *this;
//    }
//
//    bool operator==(const Vect &rhs) {
//        bool equal = _len == rhs._len;
//        for (auto i = 0; equal && i < _len; i++)
//            equal = _cords[i] == rhs._cords[i];
//        return equal;
//    }
//
//    friend std::ostream &operator<<(std::ostream &os, const Vect &obj) {
//        for (auto i = 0; i < obj._len; i++)
//            os << obj._cords[i] << ' ';
//        return os;
//    }
//
//    friend std::istream &operator>>(std::istream &is, Vect &obj) {
//        for (auto i = 0; i < obj._len; i++)
//            is >> obj._cords[i];
//        return is;
//    }
//
//    ~MyVector() {
//        if (_cords != nullptr)
//            delete[] _cords;
//    }
//
//protected:
//    T *_cords;
//    size_t _len;
//
//};