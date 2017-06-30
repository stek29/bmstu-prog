#include "hyperboloid.h"
#include <cmath>

void Hyperboloid::recalculate() {
    EllipseDesc::point_t point;
    double zCord;
    const auto pointCount = curr.pointCount;
    const auto ba_coef = b/a;

    // [Z,pointCount,[x,y]*pointCount]...
    file.seek(0);
    for (auto t = 0; t <= 30; t++) {
        zCord = c * sinh(t/10.);
        *stream << zCord;

        auto new_a = a * cosh(t/10.);
        auto new_a_sq = new_a*new_a;

        const auto xstep = new_a/pointCount;
        auto x = new_a + xstep;
        *stream << pointCount;
        for (auto i = 0; i < pointCount; i++) {
            x -= xstep;
            auto y = ba_coef * sqrt(new_a_sq - x*x);
            point.x = x;
            point.y = y;
            *stream << point.x << point.y;
        }
    }
}
