#ifndef DRAWERWIDGET_H
#define DRAWERWIDGET_H

#include "hyperboloid.h"
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class DrawerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
    DrawerWidget(QWidget * parent = 0);

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    bool event(QEvent *e);

    /// Reloads matrices and emits update
    void updateGLMatrices();

public slots:
    void setABC(double _a, double _b, double _c);

private:
    Hyperboloid hyper;

    QPoint lastPos;
    int xRot, yRot, zRot;
    int zoom;
    bool hasNativeGestures = false;

};

#endif // DRAWERWIDGET_H