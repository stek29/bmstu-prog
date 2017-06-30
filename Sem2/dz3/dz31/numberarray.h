#pragma once

#include <initializer_list>
#include <ostream>
#include "number.h"

struct Meta {
    double average;
    size_t minIdx, maxIdx;
    count_type max, min;
};

class NumberArray {
public:
    NumberArray() = delete;
    NumberArray(const NumberArray&) = delete;

    NumberArray(std::initializer_list<Number> list): _size(list.size()) {
        if (size() == 0) {
            throw std::invalid_argument("array can't be empty");
        }

        values = new Number[size()];

        auto it = list.begin();
        size_t idx = 0;

        { // first
            count_type cntInt = (*it).getDigitCnt(Part::Integer);
            integer.average = cntInt;
            integer.minIdx = integer.maxIdx = idx;
            integer.min = integer.max = cntInt;

            count_type cntFract = (*it).getDigitCnt(Part::Fractional);
            fractional.average = cntFract;
            fractional.minIdx = fractional.maxIdx = idx;
            fractional.min = fractional.max = cntFract;

            values[idx] = *it;
        }

        // no need to check list.end(), we know the size
        for(idx++; idx < size(); idx++) {
            it++;
            auto num = *it;

            values[idx] = num;

            count_type cntInt = num.getDigitCnt(Part::Integer);
            integer.average += cntInt;
            if (cntInt > integer.max) {
                integer.maxIdx = idx;
                integer.max = cntInt;
            }
            if (cntInt < integer.min) {
                integer.minIdx = idx;
                integer.min = cntInt;
            }

            count_type cntFract = num.getDigitCnt(Part::Fractional);
            fractional.average += cntFract;
            if (cntFract > fractional.max) {
                fractional.maxIdx = idx;
                fractional.max = cntFract;
            }
            if (cntFract < fractional.min) {
                fractional.minIdx = idx;
                fractional.min = cntFract;
            }
        }

        integer.average /= size();
        fractional.average /= size();
    }

    friend std::ostream& operator<<(std::ostream &os, const NumberArray &arr) {
        for (size_t i = 0; i < arr.size(); i++)
            os << "\t" << i << ": " << arr[i] << '\n';
        return os;
    }

    std::ostream& dump(std::ostream &os) {
        os << "NumberArray begin.\n";
        os << *this;

        auto met = meta(Part::Integer);
        os << "META int:";
        os << "\n\tavg: " << met.average;
        os << "\n\tminI: " << met.minIdx << " (" << met.min << ')';
        os << "\n\tmaxI: " << met.maxIdx << " (" << met.max << ')';
        met = meta(Part::Fractional);
        os << "\nMETA fract:";
        os << "\n\tavg: " << met.average;
        os << "\n\tminI: " << met.minIdx << " (" << met.min << ')';
        os << "\n\tmaxI: " << met.maxIdx << " (" << met.max << ')';

        os << "\nend." << std::endl;

        return os;
    }

    inline Number operator[](int idx) const {
        if (idx < 0 || idx >= size())
            throw std::out_of_range("Invalid index");
        return values[idx];
    }

    inline size_t size() const { return _size; }
    inline Meta meta(Part part) const {
        return (part == Part::Integer) ? integer : fractional;
    }

    ~NumberArray() {
        delete[] values;
    }

private:
    Meta integer, fractional;

    size_t _size;
    Number *values;

};