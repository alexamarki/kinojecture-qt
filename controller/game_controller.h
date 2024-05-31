#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>
#include "../game_logic/game_model.h"

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(Model *model, QObject *parent = nullptr) : QObject(parent) {}

    // gameloop controllers
    void startGame(const std::vector<std::pair<std::string, std::string>>& data);
    void onCardSelected(int cardIndex);
    void onCardDeselected(int cardIndex);
    std::pair<std::string, std::string> onCardHovered(int cardIndex);
    void onCardsLowered();
    std::pair<int, int> getRandomisedCards();
    std::unordered_set<int> getLowered(bool isPrimaryPlayer);
    void onMakeGuess(int cardIndex);
    void onExitToMainMenu(bool includeSecondaryPlayer, QString sndUsername);
    void addToLeaderboard(bool includeSecondaryPlayer, QString sndUsername);
    bool getPlayerTurn();
    void invertPlayerTurn();
    void onTurnOverEnd();

public slots:
    // gameloop controller slots
    void onTurnOver(); // link to Model::turnOverEvent()
    void onGameOver(); // link to Model::endEvent()
    void onLowerFail(); // link to Model::lowerFail()

signals: // to connect to View SLOTS, which are yet to be implemented
    // gameloop controller signals
    void showRulesScreen();
    void introduceRandomisedCards(); // called in a View function, not here
    void showGameScreen();
    void promptLowerFailPopup();
    void showTurnOverScreen();
    void showGameOverScreen();
    void exitToMainMenu();

private:
    Model *model;
    bool isPrimaryPlayer = true;
};

#endif