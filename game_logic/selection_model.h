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
#include <QAbstractProxyModel>
#include <QAbstractItemModel>
#include <vector>
#include <unordered_set>

class SelectionModel : public QItemSelectionModel
{
    Q_OBJECT

public:
    SelectionModel(QAbstractProxyModel* model, QObject* parent = nullptr) : QItemSelectionModel(model, parent) {}

    QStringList getSelectionData();

public slots:
    void handleSelectionChanged(const QItemSelection& selected);

private:
    QStringList selectionData;
};

#endif