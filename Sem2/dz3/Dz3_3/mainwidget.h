#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStringListModel>
#include "model.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void on_addButton_clicked();
    void inputDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &);

private:
    void setError(int row);

    Ui::MainWidget *ui;
    Model *inputModel;
    Model *resultsModel;
};

#endif // MAINWIDGET_H
