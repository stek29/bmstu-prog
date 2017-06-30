#include <QtWidgets/QMessageBox>
#include <QtWidgets/QSplitter>
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(onExitClicked()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onExitClicked() {
    if (QMessageBox::question(
                this,
                QString(),
                QString("Закрыть?"),
                QMessageBox::Yes|QMessageBox::No
                ))
    {
        auto parent = dynamic_cast<QSplitter *>(parentWidget());
        if (parent != nullptr && parent->count() == 1) {
            emit(parent->close());
        } else {
            emit(close());
        }
    }
}
