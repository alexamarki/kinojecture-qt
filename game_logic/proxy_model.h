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

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    ProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent) {}

    void setFilter(int column, const QString& filterString);
    void clearFilter(int column);
    void setSortOrder(int column, Qt::SortOrder order);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QVector<QString> columnFilters;
}

#endif