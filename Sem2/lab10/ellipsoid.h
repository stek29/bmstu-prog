#ifndef ELLIPSOID_H
#define ELLIPSOID_H
#include "weirdthing.h"

class Ellipsoid : public WeirdThing
{
public:
    using WeirdThing::WeirdThing;

    void recalculate();
};

#endif // ELLIPSOID_H