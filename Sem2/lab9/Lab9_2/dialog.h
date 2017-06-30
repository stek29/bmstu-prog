#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

public slots:
    void onExitClicked();
};

#endif // MAINWINDOW_H
