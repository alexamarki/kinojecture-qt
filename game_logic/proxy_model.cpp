#include "proxy_model.h"

void ProxyModel::setFilter(int column, const QString& filterString) 
{
    if (column >= 0 && column < columnFilters.size())
        columnFilters[column] = filterString;
    else if (column >= 0) 
    {
        columnFilters.resize(column + 1);
        columnFilters[column] = filterString;
    }
    invalidateFilter();
}

void ProxyModel::clearFilter(int column) 
{
    if (column >= 0 && column < columnFilters.size())
        columnFilters[column].clear();
    invalidateFilter();
}

void ProxyModel::setSortOrder(int column, Qt::SortOrder order)
{
    sort(column, order);
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    for (int column = 0; column < columnFilters.size(); ++column) 
    {
        if (!columnFilters[column].isEmpty()) 
        {
            QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);
            if (!sourceModel()->data(index).toString().contains(columnFilters[column], Qt::CaseInsensitive))
                return false;
        }
    }
    return true;
}

QStringList ProxyModel::getSelectionData()
{
    return selectionModel->getSelectionData();
}

bool checkCount(QStringList data, int limit)
{
    if (data.size() != limit)
        return false;
    return true;
}