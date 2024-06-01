#ifndef MOVIE_CONTROLLER_H
#define MOVIE_CONTROLLER_H

#include <QObject>
#include <QSqlTableModel>
#include <QStringList>
#include "../game_logic/proxy_model.h"
#include "../db_code/cinema_db.h"

class MovieController : public QObject {
    Q_OBJECT

public:
    MovieController(QObject *parent = nullptr)
    {
        CinemaDB *database = new CinemaDB("../data/game.db");
        QSqlTableModel *tableModel = new QSqlTableModel(nullptr, database->getDB());
        tableModel->setTable("movies");
        ProxyModel *proxyModel = new ProxyModel(tableModel);
        this->model = proxyModel;
    }
    
    void submitFilters(const QString& titleType, const QString& primaryTitle, const QString& genres, 
                        int yearLow, int yearUpper, int runtimeLow, int runtimeUpper, double averageRatingLow, double averageRatingUpper);
    void filterByTitleType(const QString& titleType);
    void filterByPrimaryTitle(const QString& primaryTitle);
    void filterByGenres(const QString& genres);
    void filterByYearRange(int year, bool exceeding);
    void filterByRuntime(int runtime, bool exceeding);
    void filterByAverageRating(double averageRating, bool exceeding);
    ProxyModel* getModelDirect();

public slots:
    void checkGameData();
    void printHI();

signals: // to connect to View SLOTS, which are yet to be implemented
    void sufficientGameData(QStringList selectionData);
    void insufficientGameData();

private:
    ProxyModel *model;
};

#endif