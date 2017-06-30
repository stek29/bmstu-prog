#include "weirdthing.h"

WeirdThing::WeirdThing(int ellipsePointCnt)
    : prev(ellipsePointCnt), curr(ellipsePointCnt)
{
    file.open();
    stream = new QDataStream(&file);
}

WeirdThing::~WeirdThing() {
    delete stream;
    file.close();
}

bool WeirdThing::shiftDescs() {
    if (file.atEnd()) return false;

    std::swap(curr.points, prev.points);
    std::swap(curr.pointCount, prev.pointCount);
    std::swap(curr.zCord, prev.zCord);

    *stream >> curr.zCord;
    int pointCount;
    *stream >> pointCount;

    // just in case
    if (curr.pointCount < pointCount) pointCount = curr.pointCount;

    for (int i = 0; i < pointCount; i++) {
        *stream >> curr.points[i].x >> curr.points[i].y;
    }

    return true;
}

void WeirdThing::reset() {
    file.seek(0);
    shiftDescs();
}
