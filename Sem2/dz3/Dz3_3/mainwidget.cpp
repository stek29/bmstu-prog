#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QStringListModel>
#include <QDebug>
#include <QMessageBox>
#include <cmath>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    inputModel = new Model();
    connect(inputModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(inputDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

    resultsModel = new Model();
    resultsModel->setHeaders(QStringList({"Максимум",
                                          "Минимум",
                                          "Среднее значение",
                                          "Среднее кв. отклонение"}));

    resultsModel->setStringList(QStringList({"-", "-", "-", "-"}));
    resultsModel->setReadOnly(true);

    ui->inputView->setModel(inputModel);
    ui->resultsView->setModel(resultsModel);
    // Скрываем горизонтальные заголовки
    ui->inputView->horizontalHeader()->hide();
    ui->resultsView->horizontalHeader()->hide();
}

MainWidget::~MainWidget() {
    delete ui;
}

void MainWidget::on_addButton_clicked() {
    inputModel->insertRow(inputModel->rowCount());
}

void MainWidget::inputDataChanged(const QModelIndex &t, const QModelIndex &b, const QVector<int> &r) {
    Q_UNUSED(t); Q_UNUSED(b); Q_UNUSED(r);
    resultsModel->setStringList(QStringList({"-", "-", "-", "-"}));

    auto strings = inputModel->stringList();
    auto n = strings.size();
    if (n < 1) return;

    auto it = strings.begin();

    double current, max, min, average;

    bool ok = false;
    current = (*it).toDouble(&ok);
    if (!ok) { setError(0); return; }
    max = min = average = current;

    for (it++; it != strings.end(); it++) {
        current = (*it).toDouble(&ok);
        if (!ok) { setError(n); return; }
        if (current > max) max = current;
        if (current < min) min = current;
        average += current;
    }

    average /= n;

    QString deviationStr = "-";
    if (n > 1) {
        double deviation = 0;
        for (auto &str : strings) {
            auto diff = str.toDouble() - average;
            deviation += diff * diff;
        }
        deviation = sqrt(deviation / (n - 1));
        deviationStr = QString::number(deviation);
    }

    resultsModel->setStringList({
                                    QString::number(max),
                                    QString::number(min),
                                    QString::number(average),
                                    deviationStr
                                });
}

void MainWidget::setError(int row) {
    ui->inputView->selectionModel()->
            select(ui->inputView->model()->index(row, 0),
                   QItemSelectionModel::ClearAndSelect);
    QMessageBox::critical(this, "Error", "Введено недопустимое значение!");
}
