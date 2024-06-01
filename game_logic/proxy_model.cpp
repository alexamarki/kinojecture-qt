#include "proxy_model.h"


void ProxyModel::setRowLimit(int limit) {
    if (limit != rowLimit) {
        rowLimit = limit;
        invalidateFilter(); // Invalidate the filter to reapply with the new limit
    }
}

int ProxyModel::rowCount(const QModelIndex &parent) const {
    return 100;
    // if (parent.isValid()) // For tree structures
    //     return 0;

    // int actualRowCount = QSortFilterProxyModel::rowCount(parent);
    
    // // Return the lesser of the actual row count or the row limit
    // return (rowLimit > 0 && actualRowCount > rowLimit) ? rowLimit : actualRowCount;
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
    if (sourceRow >= rowLimit) {
        return false;
    }

    for (int column = 0; column < columnFilters.size(); ++column) {
        if (!columnFilters[column].isEmpty()) {
            if (columnFiltersType[column] == 0) {
                QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);
                if (!sourceModel()->data(index).toString().contains(columnFilters[column], Qt::CaseInsensitive)) {
                    return false;
                }
            } else if (columnFiltersType[column] == 1) { 
                QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);
                if (sourceModel()->data(index).toFloat() < columnFilters[column].toFloat()) {
                    return false;
                }
            } else if (columnFiltersType[column] == -1) { 
                QModelIndex index = sourceModel()->index(sourceRow, column, sourceParent);
                if (sourceModel()->data(index).toFloat() > columnFilters[column].toFloat()) {
                    return false;
                }
            }
        }
    }
    return true;
}

void ProxyModel::setFilter(int column, const QString& filterString, const int filterType) {
    if (column >= 0 && column < columnFilters.size()) {
        columnFilters[column] = filterString;
        columnFiltersType[column] = filterType;
    } else if (column >= 0) {
        columnFilters.resize(column + 1);
        columnFilters[column] = filterString;
        columnFiltersType.resize(column + 1);
        columnFiltersType[column] = filterType;
    }
    invalidateFilter();
}

void ProxyModel::clearFilter(int column) {
    if (column >= 0 && column < columnFilters.size()) {
        columnFilters[column].clear();
    }
    invalidateFilter();
}

void ProxyModel::clearAllFilters() {
    columnFilters.clear();
    columnFiltersType.clear();
    invalidateFilter();
}

void ProxyModel::setSortOrder(int column, Qt::SortOrder order) {
    sort(column, order);
}

QStringList ProxyModel::getSelectionData() {
    return selectionModel->getSelectionData();
}

bool ProxyModel::checkCount(QStringList data, int limit) {
    return data.size() == limit;
}
