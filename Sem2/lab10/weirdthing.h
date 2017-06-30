#ifndef WEIRDTHING_H
#define WEIRDTHING_H
#include <QTemporaryFile>
#include <QDataStream>

class EllipseDesc {
public:
    EllipseDesc() = delete;
    EllipseDesc(const EllipseDesc&) = delete;

    EllipseDesc(int pCnt, double zCrd = 0)
        : pointCount(pCnt)
        , zCord(zCrd)
    {
        points = new point_t[pointCount];
    }

    ~EllipseDesc() {
        if (points != nullptr)
            delete[] points;
    }

    struct point_t { double x, y; };
    int pointCount;
    point_t* points;
    double zCord;
};

class WeirdThing
{
public:
    WeirdThing(int ellipsePointCnt = 30);
    virtual ~WeirdThing();

    void setABC(double _a, double _b, double _c) {
        a = _a; b = _b; c = _c;
        recalculate();
    }

    virtual void recalculate() = 0;
    void reset();

    bool shiftDescs();


    EllipseDesc prev, curr;

protected:
    double a, b, c;
    QTemporaryFile file;
    QDataStream *stream;

};

#endif // WEIRDTHING_H