#ifndef SELECTION_MODEL_H
#define SELECTION_MODEL_H

#include <QObject>
#include <QRandomGenerator>
#include <QTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUuid>
#include <QItemSelectionModel>
#include <vector>
#include <unordered_set>

class SelectionModel : public QItemSelectionModel
{
    Q_OBJECT

public:
    SelectionModel(QObject* parent = nullptr) : QItemSelectionModel(parent) {}

signals:
    void cellSelected(int row, int column, const QString& cellData); // define a class to check that enough cells are selected, write code for it and for returning the data as a vector of strings

public slots:
    void handleSelectionChanged(const QItemSelection& selected);
}

#endif