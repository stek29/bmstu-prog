#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTableView>

class TableModel;
class ProxyModel;
class LineEditID;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void filterEdited(QString, int);
    void task3();
    void task4();

private:
    void createWidgets();

    QTableView *tableView;

    TableModel *srcMdl;
    ProxyModel *mdl;

    QVector<LineEditID*> filters;
    LineEditID *task31, *task32;
};

#endif // MAINWIDGET_H
