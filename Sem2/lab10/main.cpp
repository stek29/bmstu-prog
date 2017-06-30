#include "dialog.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Force OpenGL 2.1
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(2, 1);
    QSurfaceFormat::setDefaultFormat(format);

    Dialog w;
    w.show();

    return a.exec();
}
