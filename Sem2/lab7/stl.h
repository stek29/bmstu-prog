#ifndef LABS_STL_H
#define LABS_STL_H

#include <set>
#include <functional>

#include "number.h"

class NumberSorter {
public:
    NumberSorter(): mSet() {}
    void feed(int number);
    bool exec(std::function<bool(int)> func);
private:
    std::multiset<Number> mSet;
};

#endif //LABS_STL_H
