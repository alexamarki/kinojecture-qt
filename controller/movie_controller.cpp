#include "movie_controller.h"
#include <QObject>
#include "proxy_model.h"

void MovieController::filterByTitleType(const QString& titleType)
{
    model->setFilter(1, titleType, 0);
}

void MovieController::filterByPrimaryTitle(const QString& primaryTitle)
{
    model->setFilter(2, primaryTitle, 0);
}

void MovieController::filterByGenres(const QString& genres)
{
    model->setFilter(3, genres, 0);
}

void MovieController::filterByYearRange(int year, bool exceeding)
{
    QString filterString = QString("%1").arg(year);
    model->setFilter(4, filterString, exceeding ? 1 : -1);
}

void MovieController::filterByRuntime(int runtime, bool exceeding)
{
    QString filterString = QString("%1").arg(runtime);
    model->setFilter(6, filterString, exceeding ? 1 : -1);
}

void MovieController::filterByAverageRating(double averageRating, bool exceeding)
{
    QString filterString = QString("%.2f").arg(averageRating);
    model->setFilter(7, filterString, exceeding ? 1 : -1);
}

void MovieController::submitFilters(const QString& titleType, const QString& primaryTitle, const QString& genres, 
                        int yearLow, int yearUpper, int runtimeLow, int runtimeUpper, double averageRatingLow, double averageRatingUpper)
{
    model->clearAllFilters();
    if (titleType != "")
        this->filterByTitleType(titleType);
    if (primaryTitle != "")
        this->filterByPrimaryTitle(primaryTitle);
    if (genres != "")
        this->filterByGenres(genres);
    if (yearLow != -1)
        this->filterByYearRange(yearLow, false);
    if (yearUpper != -1)
        this->filterByYearRange(yearUpper, true);
    if (runtimeLow != -1)
        this->filterByRuntime(runtimeLow, false);
    if (runtimeUpper != -1)
        this->filterByRuntime(runtimeUpper, true);
    if (averageRatingLow != -1)
        this->filterByAverageRating(averageRatingLow, false);
    if (averageRatingUpper != -1)
        this->filterByAverageRating(averageRatingUpper, true);
}

void MovieController::checkGameData()
{
    if (model->checkCount(model->getSelectionData(), 25))
        emit sufficientGameData(model->getSelectionData());
    else
        emit insufficientGameData();
}

ProxyModel* MovieController::getModelDirect()
{
    return this->model;
}

void MovieController::printHI()
{
    std::cout << "HI" << std::endl;
}