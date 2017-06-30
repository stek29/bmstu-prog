#pragma once

#include <iostream>
#include <string>

typedef std::string::size_type count_type;

enum class Part {
    Integer,
    Fractional
};

class Number {
public:
    Number() : sValue("0.0") {
        integer = fractional = 0;
        // std::cerr << "+NUMBER DEF CONSTRUCT " << std::endl;
    }

//    Number(const Number& rhs): sValue(rhs.sValue) {
//        integer = rhs.integer;
//        fractional = rhs.fractional;
//        // std::cerr << "+NUMBER COPY CONSTRUCT " << *this << std::endl;
//    }

    Number(std::string sVal) : sValue(sVal) {
        init();
        // std::cerr << "+NUMBER STR CONSTRUCT " << *this << std::endl;
    }

    Number(const char *sVal) : sValue(sVal) {
        init();
        // std::cerr << "+NUMBER CHAR CONSTRUCT " << *this << std::endl;
    }

    inline friend std::ostream& operator<<(std::ostream &os, const Number &num) {
        return (os << num.v());
    }

    inline std::string v() const {
        return sValue;
    }

    count_type getDigitCnt(Part p) const {
        return (p == Part::Integer) ? integer : fractional;
    }

//    ~Number() {
//        // std::cerr << "-NUMBER DES TRUCT " << *this << std::endl;
//    }
private:
    void init() {
        if (sValue[0] != '+' && sValue[0] != '-') {
            // VERY INEFFICIENT!
            sValue = '+' + sValue;
        }

        integer = sValue.length() - 1;
        auto dotPos = sValue.find_first_of('.');
        if (dotPos != std::string::npos) {
            fractional = integer - dotPos;
            integer = dotPos - 1;
        } else {
            fractional = 0;
        }
    }

    count_type integer, fractional;
    std::string sValue;
};