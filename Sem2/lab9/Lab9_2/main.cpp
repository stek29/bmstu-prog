#include "dialog.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QSplitter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto splitter = new QSplitter(Qt::Vertical);

    auto dialog1 = new Dialog();
    auto dialog2 = new Dialog();

    splitter->addWidget(dialog1);
    splitter->addWidget(dialog2);

    splitter->show();

    return a.exec();
}
