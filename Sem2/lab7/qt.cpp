#include "qt.h"

void NumberSorter::feed(int number) {
    qMMap.insert(number, false);
}

bool NumberSorter::exec(std::function<bool(int)> func) {
    bool fail = false;
    for(auto it = qMMap.begin(); !fail && it != qMMap.end(); ++it) {
        fail = !func(it.key());
    }
    return !fail;
}