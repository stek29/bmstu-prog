#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::abcChanged() {
    auto a = ui->spinBoxA->value();
    auto b = ui->spinBoxB->value();
    auto c = ui->spinBoxC->value();

    emit ui->glWidget->setABC(a, b, c);
}
