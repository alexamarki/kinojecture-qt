#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>
#include "../game_logic/game_model.h"

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(Model *model, QObject *parent = nullptr);



private:
    Model *model;
    bool isPrimaryPlayer = true;
};

#endif