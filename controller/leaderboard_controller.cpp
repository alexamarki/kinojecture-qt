#include "leaderboard_controller.h"

void LeaderboardController::exportLeaderboard(const std::string &filepath)
{
    this->lead->save_database(filepath);
    emit successfullyExported();
}

ProxyModel* LeaderboardController::getModelDirect()
{
    return this->model;
}
