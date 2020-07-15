#include "positionsqlmodel.h"

PositionSqlModel::PositionSqlModel(QWidget * parent) : QSqlQueryModel(parent)
{

}

QVariant PositionSqlModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);

    if (value.isValid() && role == Qt::DisplayRole && item.column() == 3) {
        if (value.toBool())
            value.setValue(QString("Да"));
        else
            value.setValue(QString("Нет"));
    }
    return value;
}
