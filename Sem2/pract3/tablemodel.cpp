#include <QDebug>
#include "tablemodel.h"


TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{
    animals.append({"К1", "О1.1", "С1.1.1", "В1.1.1.1"});
    animals.append({"К1", "О1.1", "С1.1.1", "В1.1.1.2"});
    animals.append({"К1", "О1.1", "С1.1.1", "В1.1.1.3"});
    animals.append({"К1", "О1.1", "С1.1.2", "В1.1.2.1"});
    animals.append({"К1", "О1.2", "С1.2.1", "В1.2.1.1"});
    animals.append({"К2", "О2.1", "С2.1.1", "В2.1.1.1"});
    animals.append({"К2", "О2.2", "С2.2.1", "В2.2.1.1"});
    animals.append({"К2", "О2.3", "С2.3.1", "В2.3.1.1"});
    animals.append({"К2", "О2.4", "С2.4.1", "В2.4.1.1"});
    animals.append({"К3", "О3.1", "С3.1.1", "В3.1.1.1"});
    animals.append({"К3", "О3.1", "С3.1.1", "В3.1.1.2"});
    animals.append({"К3", "О3.1", "С3.1.2", "В3.1.2.1"});
}

int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return animals.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 4; // klass, otryad, semeistvo, vid
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < A_PROP_COUNT)
            return animalHeaders[section];
    } else {
        return QString::number(section + 1);
    }
    return QVariant();
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        if (index.row() < animals.size() && index.row() >= 0) {
            return getAnimalProperty(animals[index.row()], index.column());
        }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        if (index.row() < animals.size() && index.row() >= 0) {
             auto prop = getAnimalProperty(animals[index.row()], index.column());
             if (prop != nullptr) {
                 *prop = value;
                 emit dataChanged(index, index);
                 return true;
             }
        }
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    auto flags = QAbstractTableModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent) {
    qDebug() << "insert" << row << ' ' << count;
    if (row < 0 || row > animals.size())
        return false;
    beginInsertRows(parent, row, row + count - 1);
    //qDebug() << animals;
    animals.insert(row, count, Animal());
    //qDebug() << animals;
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (row < 0 || (row + count) > animals.size())
        return false;
    beginRemoveRows(parent, row, row + count - 1);
    //qDebug() << animals;
    animals.remove(row, count);
    //qDebug() << animals;
    endRemoveRows();
    return true;
}