#ifndef MODEL_H
#define MODEL_H

#include <QStringListModel>

class Model: public QStringListModel {
public:
    explicit Model(QObject *parent = nullptr);

    void setHeaders(const QStringList &aheaders);

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    Qt::ItemFlags flags(const QModelIndex &index) const {
        auto res = QStringListModel::flags(index);
        if (forceReadonly) {
            res &= ~Qt::ItemIsEditable;
        }
        return res;
    }

    void setReadOnly(bool forceRO) {
        forceReadonly = forceRO;
    }

private:
    QStringList headers;
    bool forceReadonly;
};

#endif // MODEL_H