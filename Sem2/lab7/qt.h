#ifndef LABS_STL_H
#define LABS_STL_H

#include <QMultiMap>
#include <functional>

#include "number.h"

class NumberSorter {
public:
    NumberSorter(): qMMap() {}
    void feed(int number);
    bool exec(std::function<bool(int)> func);
private:
    QMultiMap<Number, bool> qMMap;
};

#endif //LABS_STL_H
