#include "drawerwidget.h"
#include <QDebug>
#include <cmath>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QMatrix4x4>
#include <glu.h>


namespace {

bool kek=true;

const auto NormFact = 8;
const auto pointCount = 30;

inline int normalizeAngle(int angle) {
    angle %= 360 * NormFact * 2;
    if (angle < -180 * NormFact * 2) angle += 360 * NormFact * 2;
    return angle;
}

void setVertices(const EllipseDesc* curr, const EllipseDesc* prev, bool invertZ = false) {
    bool prevNotNull = prev != nullptr;

    // Get min
    auto pointCount = curr->pointCount;
    if (prevNotNull && prev->pointCount < pointCount)
        pointCount = prev->pointCount;

    GLdouble currZ = invertZ ? -curr->zCord : curr->zCord;
    GLdouble prevZ = 0;
    if (prevNotNull)
        prevZ = invertZ ? -prev->zCord : prev->zCord;

    // draw 4 parts of ellipse(s)
    int i;
    for (i=0; i < pointCount; i++) { // 1 (+, +)
        glVertex3d(+curr->points[i].x, +curr->points[i].y, currZ);
    if (prevNotNull)
        glVertex3d(+prev->points[i].x, +prev->points[i].y, prevZ);
    }
    for (i--; i >= 0; i--) { // 2 (-, +)
        glVertex3d(-curr->points[i].x, +curr->points[i].y, currZ);
    if (prevNotNull)
        glVertex3d(-prev->points[i].x, +prev->points[i].y, prevZ);
    }
    for (i++; i < pointCount; i++) { // 3 (-, -)
        glVertex3d(-curr->points[i].x, -curr->points[i].y, currZ);
    if (prevNotNull)
        glVertex3d(-prev->points[i].x, -prev->points[i].y, prevZ);
    }
    for (i--; i >= 0; i--) { // 4 (+, -)
        glVertex3d(+curr->points[i].x, -curr->points[i].y, currZ);
    if (prevNotNull)
        glVertex3d(+prev->points[i].x, -prev->points[i].y, prevZ);
    }
}
}

DrawerWidget::DrawerWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , hyper(pointCount)
    , xRot(-45 * NormFact * 2), yRot(0), zRot(0)
    , zoom(10 * NormFact * 2)
{
    hyper.setABC(1, 1, 1);
}

void DrawerWidget::initializeGL() {
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    // Blending
//    glEnable(GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // For better perfomance
    glShadeModel(GL_FLAT);

    glLineWidth(2);
    glPointSize(3);
    glClearColor(1, 1, 1, 1);
    glColor4f(0, 0, 0, 0.6f);

    update();

    //glEnable(GL_LIGHTING);

    // Ambient lighting
    GLfloat global_ambient[] = { 0.6f, 0.6f, 0.f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat light0spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0spec);
    glEnable(GL_LIGHT0);

    glEnable (GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    //glMaterialf(GL_FRONT, GL_SHININESS, 0);
}

void DrawerWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    hyper.reset();

    updateGLMatrices();
    while(hyper.shiftDescs()) {
        glColor4f(1, 0, 0, 0.6f);
        glBegin(GL_LINES);
        setVertices(&hyper.curr, nullptr, false);
        glEnd();
        glColor4f(0, 0, 1, 0.6f);
        glBegin(GL_LINES);
        setVertices(&hyper.curr, nullptr, true);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
        glColor4f(1, 1, 0, 0.6f);
        setVertices(&hyper.curr, &hyper.prev, false);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glColor4f(0, 1, 1, 0.6f);
        setVertices(&hyper.curr, &hyper.prev, true);
        glEnd();
    }

    glPopMatrix();
//
//    glBegin(GL_LINES);
//    int m = 40, n = 40, r = 5;
//    float c = 0;
//    for (int i=0; i<n; i++) {
//        glColor4f(c, 0, float(fabs(double(1-c))), 0.6f);
//        c += 1.f/40;
//        for (int j=0; j<m; j++) {
//            float degi1 = 2*M_PI*i/n;
//            float degi2 = 2*M_PI*(i+1)/m;
//            float degj1 = M_PI*j/m;
//            float degj2 = M_PI*(j+1)/m;

//            float x1 = r*sin(degj1);
//            float x2 = r*sin(degj2);
//            float z1 = r*(log(tan(degj1/2))+cos(degj1));
//            float z2 = r*(log(tan(degj2/2))+cos(degj2));

//            //glColor4f(1, 0, 0, 0.6f);
//            glVertex3d(x1*cos(degi1), z1, x1*sin(degi1));
//            //glColor4f(1, 1, 0, 0.6f);
//            glVertex3d(x2*cos(degi1), z2, x2*sin(degi1));
//            //glColor4f(0, 1, 0, 0.6f);
//            glVertex3d(x1*cos(degi1), z1, x1*sin(degi1));
//            //glColor4f(0, 1, 1, 0.6f);
//            glVertex3d(x1*cos(degi2), z1, x1*sin(degi2));
//        }
//    }
//    glEnd();
//    glPopMatrix();
    //#00FFFF
    //#FFFF00
}

void DrawerWidget::resizeGL(int width, int height) {
    Q_UNUSED(width); Q_UNUSED(height);
    update();
}

void DrawerWidget::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void DrawerWidget::mouseMoveEvent(QMouseEvent *event) {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

    if (!hasNativeGestures) {
        if (event->buttons() & Qt::LeftButton) {
            xRot = normalizeAngle(xRot + NormFact/2 * dy);
            yRot = normalizeAngle(yRot + NormFact/2 * dx);
        } else if (event->buttons() & Qt::RightButton) {
            xRot = normalizeAngle(xRot + NormFact/2 * dy);
            zRot = normalizeAngle(zRot + NormFact/2 * dx);
        }
    } else {
        zRot = normalizeAngle(zRot + NormFact/2 * dy);
    }
    update();
    lastPos = event->pos();
}

void DrawerWidget::wheelEvent(QWheelEvent *event) {
    if (!hasNativeGestures) {
        zoom += event->angleDelta().y();
    } else {
        // x and y swapped -- that's intended!
        xRot = normalizeAngle(xRot + NormFact/2 * event->angleDelta().y());
        yRot = normalizeAngle(yRot + NormFact/2 * event->angleDelta().x());
    }
    update();
}

void DrawerWidget::updateGLMatrices() {
    makeCurrent();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    {
    glPushMatrix();
    auto normZoom = GLdouble(zoom) / NormFact;
    // To avoid scaling
    auto aspectRatio = 1.0 * width() / height();
    if (aspectRatio >= 1)
        glOrtho(-normZoom * aspectRatio,
                 normZoom * aspectRatio,
                -normZoom,
                 normZoom,
                -30.0, 30.0);
    else
        glOrtho(-normZoom,
                 normZoom,
                -normZoom / aspectRatio,
                 normZoom / aspectRatio,
                -30.0, 30.0);
    auto light_cord = static_cast<float>(GLdouble(zoom) / NormFact / 2);
    QVector3D lightV = {light_cord, light_cord, light_cord};

    if (!kek) {
        QMatrix4x4 m = {0,0,0,0,
                        0,0,0,0,
                        0,0,0,0,
                        0,0,0,1};
        m.rotate(-GLfloat(xRot) / NormFact, 1, 0, 0);
        m.rotate(-GLfloat(yRot) / NormFact, 0, 1, 0);
        m.rotate(-GLfloat(zRot) / NormFact, 0, 0, 1);

        lightV = m.inverted() * lightV;
    }
    //qDebug() << lightV;
    float lposv[] = {0, 0, 0, 1};
    //float lposv[] = {0, 0, 0, 1};

    float color[] = {0, 1, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);
    glBegin(GL_POINTS); glVertex3fv(lposv); glEnd();
    color[0]=color[1]=color[2]=0;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

    glLightfv(GL_LIGHT0, GL_POSITION, lposv);
    //float lspotv[] = {-lightV.x(), -lightV.y(), -30};
    //float lspotv[] = {-lposv[0], -lposv[1], -lposv[1], 0};
    float lspotv[] = {-1,-1,-1,0};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lspotv);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 40);
    glPopMatrix();
    }

    glPushMatrix();

    auto normZoom = GLdouble(zoom) / NormFact;
    // To avoid scaling
    auto aspectRatio = 1.0 * width() / height();
    if (aspectRatio >= 1)
        glOrtho(-normZoom * aspectRatio,
                 normZoom * aspectRatio,
                -normZoom,
                 normZoom,
                -30.0, 30.0);
    else
        glOrtho(-normZoom,
                 normZoom,
                -normZoom / aspectRatio,
                 normZoom / aspectRatio,
                -30.0, 30.0);

    glTranslatef(3,3,3);

    glRotatef(GLfloat(xRot) / NormFact, 1, 0, 0);
    glRotatef(GLfloat(yRot) / NormFact, 0, 1, 0);
    glRotatef(GLfloat(zRot) / NormFact, 0, 0, 1);
    //emit update();
}

bool DrawerWidget::event(QEvent *e) {
    bool handled = false;
    if (e->type() == QEvent::Type::NativeGesture) {
        hasNativeGestures = true;
        auto ev = static_cast<QNativeGestureEvent*>(e);
        switch(ev->gestureType()) {
            //case Qt::PanNativeGesture:
            case Qt::ZoomNativeGesture:
                // "our" zoom is inverted
                zoom -= static_cast<int>(ev->value() * 100 * NormFact);
                update();
                break;
            case Qt::RotateNativeGesture:
                zRot = normalizeAngle
                        (zRot + static_cast<int>(ev->value() * NormFact));
                update();
                break;
            case Qt::SwipeNativeGesture:
            default:
                break;
        };
    };
    return handled || QOpenGLWidget::event(e);
}

void DrawerWidget::setABC(double _a, double _b, double _c) {
    hyper.setABC(_a, _b, _c);

    kek = !kek;
    emit update();
}
