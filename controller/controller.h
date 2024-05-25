#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>
#include "../game_logic/game_model.h"

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(Model *model, QObject *parent = nullptr);

    void startGame();
    void onCardSelected(int cardIndex);
    void onCardDeselected(int cardIndex);
    void onCardHovered(int cardIndex);
    void onCardsLowered();
    void onRandomisedCardScreen(bool forPrimaryPlayer);
    void onMakeGuess();
    void onExitToMainMenu();
    void addToLeaderboard(bool includeSecondaryPlayer);
    bool getPlayerTurn();
    void invertPlayerTurn();
    void onTurnOverEnd();
    // TODO: include functions for the leaderboard, settings and game creation pages

public slots:
    void onTurnOver(); // link to Model::turnOverEvent()
    void onGameOver(); // link to Model::endEvent()
    void onLowerFail(); // link to Model::lowerFail()

signals: // to connect to View SLOTS, which are yet to be implemented
    void showRulesScreen();
    void introduceRandomisedCards();
    void showGameScreen();
    void promptLowerFailPopup();
    void showTurnOverScreen();
    void showGameOverScreen();
    void exitToMainMenu();

private:
    Model *model;
    bool isPrimaryPlayer = true;
};

void Controller::startGame() 
{
    model->initGame();
}

void Controller::onCardSelected(int cardIndex) 
{
    model->addCardToSelection(cardIndex);
}

void Controller::onCardDeselected(int cardIndex) 
{
    model->removeCardFromSelection(cardIndex);
}

void Controller::onCardHovered(int cardIndex) 
{
    std::pair<std::string, std::string> movieData = model->getData(cardIndex);
    // ???????????
}
void Controller::onCardsLowered() 
{
    model->lowerCards();
}

bool Controller::getPlayerTurn() 
{
    return isPrimaryPlayer;
}
void Controller::invertPlayerTurn() 
{
    isPrimaryPlayer = !isPrimaryPlayer;
}

void Controller::onTurnOver() 
{
    invertPlayerTurn();
    emit showTurnOverScreen();
}

#endif