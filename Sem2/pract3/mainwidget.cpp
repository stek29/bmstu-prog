#include "mainwidget.h"
#include "animalstuff.h"
#include "tablemodel.h"
#include "proxymodel.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QDebug>
#include <QSet>
#include <QMap>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    createWidgets();

    mdl->setSourceModel(srcMdl);
    tableView->setModel(mdl);
    tableView->setSortingEnabled(true);
}

void MainWidget::createWidgets() {
    // models for table
    mdl = new ProxyModel(this);
    srcMdl = new TableModel(this);
    // table
    tableView = new QTableView(this);

    // buttons
    auto btnLayout = new QHBoxLayout();
    {
        auto addButton = new QPushButton(this);
        addButton->setText("+");
        auto removeButton = new QPushButton(this);
        removeButton->setText("-");

        btnLayout->addWidget(addButton);
        btnLayout->addWidget(removeButton);

        connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButton_clicked()));
        connect(removeButton, SIGNAL(clicked()), this, SLOT(on_removeButton_clicked()));
    }

    // task3
    auto task3Layout = new QVBoxLayout();
    {
        task31 = new LineEditID(this);
        task31->setPlaceholderText("Семейство #1");
        task32 = new LineEditID(this);
        task32->setPlaceholderText("Семейство #2");
        task3Layout->addWidget(task31);
        task3Layout->addWidget(task32);

        auto btn = new QPushButton(this);
        btn->setText("Сравн. Ч. Видов");
        task3Layout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, &MainWidget::task3);
    }

    // task4
    auto task4Layout = new QVBoxLayout();
    {
        auto btn = new QPushButton(this);
        btn->setText("График");
        connect(btn, &QPushButton::clicked, this, &MainWidget::task4);
        task4Layout->addWidget(btn);
    }

    // filters
    auto filterLayout = new QHBoxLayout();
    {
        filters.reserve(A_PROP_COUNT);
        for (int i = 0; i < A_PROP_COUNT; i++) {
            auto le = new LineEditID(this);
            filters.append(le);
            le->setID(i);
            le->setPlaceholderText(animalHeaders[i]);
            connect(le, &LineEditID::idTextEdited, this, &MainWidget::filterEdited);
            filterLayout->addWidget(le);
        }
    }

    auto left = new QVBoxLayout();
    left->addLayout(task3Layout);
    left->addLayout(task4Layout);
    left->addLayout(btnLayout);

    auto top = new QHBoxLayout();
    top->addWidget(tableView, 1);
    top->addLayout(left);

    auto widLayout = new QVBoxLayout(this);
    widLayout->addLayout(top);
    widLayout->addLayout(filterLayout);
}

void MainWidget::on_addButton_clicked() {
    auto idxs = tableView->selectionModel()->selection().indexes();
    mdl->insertRows(idxs.isEmpty() ? mdl->rowCount() : idxs.first().row() , 1);
}

void MainWidget::on_removeButton_clicked() {
    auto idxs = tableView->selectionModel()->selection().indexes();
    if (!idxs.isEmpty()) {
        mdl->removeRows(idxs.first().row(), 1);
    }
}

void MainWidget::filterEdited(QString filter, int prop) {
    mdl->setFilter(prop, filter);
}

void MainWidget::task3() {
    filters[A_VID]->setText(QString());
    mdl->setFilter(A_VID, QString());
    tableView->hide();

    auto sem1 = task31->text();
    mdl->setFilter(A_SEMEYSTVO, sem1);
    auto sem1cnt = mdl->rowCount();
    auto sem2 = task32->text();
    mdl->setFilter(A_SEMEYSTVO, sem2);
    auto sem2cnt = mdl->rowCount();

    auto semf = (sem1cnt > sem2cnt) ? sem1 : sem2;
    filters[A_SEMEYSTVO]->setText(semf);
    mdl->setFilter(A_SEMEYSTVO, semf);

    tableView->show();
}

void MainWidget::task4() {
    for (int i = A_KLASS; i < A_PROP_COUNT; i++) {
        filters[i]->setText(QString());
        mdl->setFilter(i, QString());
    }

    using Otryads = QSet<QString>;
    QMap<QString, Otryads> data;

    int rc = mdl->rowCount();
    for (int i = 0; i < rc; i++) {
        auto kls = mdl->data(mdl->index(i, A_KLASS)).toString();
        auto otr = mdl->data(mdl->index(i, A_OTRYAD)).toString();
        data[kls].insert(otr);
    }

    auto series = new QBarSeries();
    QMapIterator<QString, Otryads> iter(data);
    while(iter.hasNext()) {
        iter.next();
        auto set = new QBarSet(iter.key());
        *set << iter.value().size();
        series->append(set);
    }

    auto chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Количество отрядов в классе");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();

    auto axisX = new QBarCategoryAxis();
    axisX->append("");
    chart->setAxisX(axisX, series);
    auto axisY = new QValueAxis();
    chart->setAxisY(axisY, series);
    axisY->applyNiceNumbers();

    auto chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContentsOnFirstShow);
    chartView->show();
}
