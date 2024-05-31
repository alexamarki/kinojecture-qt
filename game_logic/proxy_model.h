#ifndef PROXY_MODEL_H
#define PROXY_MODEL_H

#include <QObject>
#include <QRandomGenerator>
#include <QTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUuid>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QModelIndex>
#include <vector>
#include <unordered_set>
#include "selection_model.h"

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyModel(QSqlTableModel* sourceModel, QObject* parent = nullptr) : QSortFilterProxyModel(parent)
    {
        selectionModel = new SelectionModel(this);
        setSourceModel(sourceModel);
        setSelectionModel(selectionModel);
        // connect(selectionModel, &SelectionModel::cellSelected, this, &ProxyModel::handleCellSelected);
    }

    void setFilter(int column, const QString& filterString, const int filterType);
    void clearFilter(int column);
    void clearAllFilters();
    void setSortOrder(int column, Qt::SortOrder order);
    QStringList getSelectionData();
    bool checkCount(QStringList data, int limit);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    SelectionModel* selectionModel;
    QVector<QString> columnFilters;
    QVector<int> columnFiltersType;

// private slots:
//     void handleCellSelected(int row, int column, const QString& cellData);
};

#endif