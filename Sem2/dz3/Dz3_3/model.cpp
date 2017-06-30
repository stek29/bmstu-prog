#include "model.h"

Model::Model(QObject *parent)
    : QStringListModel(parent)
    , headers()
    , forceReadonly(false)
{
}

void Model::setHeaders(const QStringList &aheaders) {
    headers = aheaders;
    emit headerDataChanged(Qt::Vertical, 0, rowCount());
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const {
    QVariant result;

    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        if (section < headers.size()) {
            result = headers.at(section);
        } else {
            result = section + 1;
        }
    }

    return result;
}