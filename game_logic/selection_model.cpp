#include "selection_model.h"
#include <QModelIndex>

void SelectionModel::handleSelectionChanged(const QItemSelection& selected)
{
    QModelIndexList selectedIndexes = selected.indexes();
    for (const QModelIndex& index : selectedIndexes) 
    {
        int row = index.row();
        int columnCount = index.model()->columnCount();
        QStringList rowData;
        for (int column = 0; column < columnCount; ++column) {
            QModelIndex cellIndex = index.sibling(row, column);
            QString cellData = cellIndex.data(Qt::DisplayRole).toString();
            rowData.append(cellData);
        }
        this->selectionData = rowData;
        if (this->isSelected(index))
            this->select(index.parent(), QItemSelectionModel::Deselect);
        else
            this->select(index.parent(), QItemSelectionModel::Select | QItemSelectionModel::Rows);
    }
}

QStringList SelectionModel::getSelectionData()
{
    return selectionData;
}