#ifndef POSITIONSQLMODEL_H
#define POSITIONSQLMODEL_H

#include <QtSql>

class PositionSqlModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    PositionSqlModel(QWidget * parent);
    QVariant data(const QModelIndex &item, int role) const;
};

#endif // POSITIONSQLMODEL_H
