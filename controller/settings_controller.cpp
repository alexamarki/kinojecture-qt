#include "settings_controller.h"

void SettingsController::changeUsername(const QString &username)
{
    this->model->updateJSON(-1, -1, username);
}

void SettingsController::updateCatcher()
{
    emit dataChanged();
}

QString SettingsController::getUsername() 
{
    return this->model->getUsername();
}
