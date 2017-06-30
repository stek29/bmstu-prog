#pragma once

#include <exception>
#include <functional>
#include <iostream>

namespace My {
    enum class NumberType {
        Int, Double
    };

    class Number {
    public:
        Number(NumberType _type) : type(_type), ptr(nullptr)
        { };

        Number(int val = 0) : type(NumberType::Int) {
            init<int>(&val);
        }

        Number(double val) : type(NumberType::Double) {
            init<double>(&val);
        }

        Number(const Number &num) : type(num.type) {
            if (num.type == NumberType::Int) {
                init<int>(num.ptr);
            } else { // num.type == NumberType::Double
                init<double>(num.ptr);
            }
        }

        explicit operator int () const {
            if (type == NumberType::Int) {
                return *reinterpret_cast<int *>(ptr);
            } else { // type == NumberType::Double
                return static_cast<double>(*this);
            }
        }
        explicit operator double () const {
            if (type == NumberType::Double) {
                return *reinterpret_cast<double *>(ptr);
            } else { // type == NumberType::Int
                return static_cast<int>(*this);
            }
        }

        bool operator>(const Number &rhs) {
            if (type == NumberType::Int && rhs.type == NumberType::Int) {
                return static_cast<int>(*this) > static_cast<int>(rhs);
            } else { // type or rhs.type is NumberType::Double (or both)
                return static_cast<double>(*this) > static_cast<double>(rhs);
            }
        }

        bool operator==(const Number &rhs) {
            if (type == rhs.type) {
                if (type == NumberType::Int) {
                    return static_cast<int>(*this) == static_cast<int>(rhs);
                } else { // type (and rhs.type) are NumberType::Double
                    return static_cast<double>(*this) == static_cast<double>(rhs);
                }
            } else {
                return false;
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const Number &obj) {
            if (obj.type == NumberType::Int) {
                return os << static_cast<int>(obj) << 'I';
            } else { // type == NumberType::Double
                return os << static_cast<double>(obj) << 'D';
            }
        }

        friend std::istream &operator>>(std::istream &is, Number &obj) {
            obj.deinit();
            if (obj.type == NumberType::Int) {
                int val; is >> val;
                obj.init<int>(&val);
            } else { // obj.type == NumberType::Double
                double val; is >> val;
                obj.init<double>(&val);
            }
            return is;
        }

        ~Number() {
            deinit();
        }

    private:
        template<typename T>
         void init(const void *src) {
            ptr = malloc(sizeof(T));
            memcpy(ptr, src, sizeof(T));
        }

        void deinit() {
            if (ptr != nullptr) {
                free(ptr);
            }
        }

        NumberType type;
        void *ptr;

    };
}