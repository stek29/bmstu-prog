#ifndef SORTFILTERPROXYMODEL_H
#define SORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QLineEdit>
#include "animalstuff.h"

class LineEditID : public QLineEdit
{
    Q_OBJECT

public:
    LineEditID(QWidget *parent = 0) : QLineEdit(parent) {
        connect(this, &QLineEdit::textChanged, this, &LineEditID::emitIdTextChanged);
        connect(this, &QLineEdit::textEdited , this, &LineEditID::emitIdTextEdited );
    }
    virtual ~LineEditID(){}

    int getID() { return id; }
    void setID(int _id) { id = _id; }

Q_SIGNALS:
    void idTextChanged(QString, int);
    void idTextEdited (QString, int);

public slots:
    void emitIdTextChanged(QString text) { emit idTextChanged(text, id); }
    void emitIdTextEdited (QString text) { emit idTextEdited (text, id); }

private:
    int id;

};

class ProxyModel : public QSortFilterProxyModel
{
public:
    ProxyModel(QObject *parent = 0);

    bool setFilter(int property, QString filter);
    QString getFilter(int property);
    bool filterAcceptsRow(int sRow, const QModelIndex &sParent) const;

private:
    QVector<QString> filters;

};

#endif // SORTFILTERPROXYMODEL_H