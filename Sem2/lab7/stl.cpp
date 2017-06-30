#include "stl.h"

void NumberSorter::feed(int number) {
    mSet.insert(number);
}

bool NumberSorter::exec(std::function<bool(int)> func) {
    bool fail = false;
    for(auto it = mSet.cbegin(); !fail && it != mSet.cend(); ++it) {
        fail = !func(*it);
    }
    return !fail;
}