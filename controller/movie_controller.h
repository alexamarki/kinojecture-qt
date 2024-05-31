#ifndef MOVIE_CONTROLLER_H
#define MOVIE_CONTROLLER_H

#include <QObject>
#include "../game_logic/proxy_model.h"
#include "game_controller.h"
#include "../db_code/cinema_db.h"

class MovieController : public QObject {
    Q_OBJECT

public:
    MovieController(ProxyModel *model, QObject *parent = nullptr);
    
    void submitFilters(const QString& titleType, const QString& primaryTitle, const QString& genres, 
                        int yearLow, int yearUpper, int runtimeLow, int runtimeUpper, double averageRatingLow, double averageRatingUpper);
    void filterByTitleType(const QString& titleType);
    void filterByPrimaryTitle(const QString& primaryTitle);
    void filterByGenres(const QString& genres);
    void filterByYearRange(int year, bool exceeding);
    void filterByRuntime(int runtime, bool exceeding);
    void filterByAverageRating(double averageRating, bool exceeding);

public slots:
    void checkGameData();

signals: // to connect to View SLOTS, which are yet to be implemented
    void sufficientGameData();
    void insufficientGameData();

private:
    ProxyModel *model;
};

#endif