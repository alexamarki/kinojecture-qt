#include "people_controller.h"
#include <QObject>
#include "../game_logic/proxy_model.h"

void PeopleController::filterByPrimaryName(const QString& primaryName)
{
    model->setFilter(1, primaryName, 0);
}

void PeopleController::filterByBirthYear(int birthYear, bool exceeding)
{
    QString filterString = QString("%1").arg(birthYear);
    model->setFilter(2, filterString, exceeding? 1 : -1);
}

void PeopleController::filterByDeathYear(int deathYear, bool exceeding)
{
    QString filterString = QString("%1").arg(deathYear);
    model->setFilter(3, filterString, exceeding? 1 : -1);
}

void PeopleController::filterByJob(const QString& job)
{
    model->setFilter(4, job, 0);
}

void PeopleController::submitFilters(const QString& primary_job_filter, const QString& primaryName, int birthYear, int deathYear, const QString& job)
{
    model->clearAllFilters();
    this->filterByJob(primary_job_filter);
    if (!primaryName.isEmpty())
        this->filterByPrimaryName(primaryName);
    if (birthYear!= 0)
        this->filterByBirthYear(birthYear, false);
    if (deathYear!= 0)
        this->filterByDeathYear(deathYear, false);
    if (!job.isEmpty())
        this->filterByJob(job);
}

void PeopleController::checkGameData()
{
    if (model->checkCount(model->getSelectionData(), 25))
        emit sufficientGameData(model->getSelectionData());
    else
        emit insufficientGameData();
}

ProxyModel* PeopleController::getModelDirect()
{
    return this->model;
}