#ifndef HYPERBOLOID_H
#define HYPERBOLOID_H
#include "weirdthing.h"

class Hyperboloid: public WeirdThing {
public:
    using WeirdThing::WeirdThing;

    void recalculate();
};

#endif // HYPERBOLOID_H