#include "proxymodel.h"
#include "animalstuff.h"

ProxyModel::ProxyModel(QObject *parent):
    QSortFilterProxyModel(parent)
{
    filters.insert(0, A_PROP_COUNT, QString());
}

bool ProxyModel::filterAcceptsRow(int sRow, const QModelIndex &sParent) const {
    for (int i = 0; i < A_PROP_COUNT; i++) {
        if (!filters[i].isNull() && !filters[i].isEmpty()) {
            auto ind = sourceModel()->index(sRow, i, sParent);
            auto data = sourceModel()->data(ind).toString();
            if (data.toUpper() != filters[i]) return false;
        }
    }

    return true;
}

bool ProxyModel::setFilter(int prop, QString filter) {
    if (prop >= 0 && prop < filters.size()) {
        filters[prop] = filter.toUpper();
        invalidateFilter();
        return true;
    } else {
        return false;
    }
}

QString ProxyModel::getFilter(int prop) {
    if (prop >= 0 && prop < filters.size()) {
        return filters[prop];
    }
    return QString();
}
