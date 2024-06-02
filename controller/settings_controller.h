#ifndef SETTINGS_CONTROLLER_H
#define SETTINGS_CONTROLLER_H

#include <QObject>
#include "../game_logic/params_model.h"

class SettingsController : public QObject {
    Q_OBJECT

public:
    SettingsController(QObject *parent = nullptr) 
    {
        this->model = new ParamsModel();
    }

    QString getUsername();

public slots:
    void changeUsername(const QString &username);
    void updateCatcher(); // receives an update settings signal and emits a dataChanged() signal

signals: // to connect to View SLOTS, which are yet to be implemented
    void dataChanged();

private:
    ParamsModel *model;
};

#endif