#ifndef PEOPLE_CONTROLLER_H
#define PEOPLE_CONTROLLER_H

#include <QObject>
#include "../game_logic/proxy_model.h"
#include "game_controller.h"
#include "../db_code/cinema_db.h"

class PeopleController : public QObject {
    Q_OBJECT

public:
    PeopleController(ProxyModel *model, QObject *parent = nullptr);
    
    void submitFilters(const QString& primaryName, int birthYear, int deathYear, const QString& job);
    void filterByPrimaryName(const QString& primaryName);
    void filterByBirthYear(int birthYear, bool exceeding);
    void filterByDeathYear(int deathYear, bool exceeding);
    void filterByJob(const QString& job);

public slots:
    void checkGameData();

signals: // to connect to View SLOTS, which are yet to be implemented
    void sufficientGameData();
    void insufficientGameData();

private:
    ProxyModel *model;
};

#endif