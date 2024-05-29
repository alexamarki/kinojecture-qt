#include "selection_model.h"
#include <QModelIndex>

void SelectionModel::handleSelectionChanged(const QItemSelection& selected)
{
    QModelIndexList selectedIndexes = selected.indexes();
    for (const QModelIndex& index : selectedIndexes) 
    {
        int row = index.row();
        int column = index.column();
        QString cellData = data(index, Qt::DisplayRole).toString();
        emit cellSelected(row, column, cellData);
    }
}