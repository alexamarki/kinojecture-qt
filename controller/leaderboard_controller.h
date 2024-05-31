#ifndef LEADERBOARD_CONTROLLER_H
#define LEADERBOARD_CONTROLLER_H

#include <QObject>
#include "../db_code/leaderboard.h"
#include <QSqlTableModel>
#include <QStringList>
#include "../game_logic/proxy_model.h"

class LeaderboardController : public QObject {
    Q_OBJECT

public:
    LeaderboardController(QObject *parent = nullptr) 
    {
        this->lead = new LeaderboardDB();
        QSqlTableModel *tableModel = new QSqlTableModel(nullptr, lead->getDB());
        tableModel->setTable("leaderboard");
        ProxyModel *proxyModel = new ProxyModel(tableModel);
        this->model = proxyModel;
    }
    ProxyModel* getModelDirect();

public slots:
    void exportLeaderboard (const std::string &filepath);

signals: // to connect to View SLOTS, which are yet to be implemented
    void successfullyExported();

private:
    LeaderboardDB *lead;
    ProxyModel *model;
};

#endif