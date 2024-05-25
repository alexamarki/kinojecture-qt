#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {}

// controller - gameloop - functions
void Controller::startGame() 
{
    model->initGame();
    emit showRulesScreen();
}

void Controller::onCardSelected(int cardIndex) 
{
    model->addCardToSelection(cardIndex);
}

void Controller::onCardDeselected(int cardIndex) 
{
    model->removeCardFromSelection(cardIndex);
}

std::pair<std::string, std::string> Controller::onCardHovered(int cardIndex) 
{
    std::pair<std::string, std::string> movieData = model->getData(cardIndex);
    return movieData;
}

std::pair<int, int> Controller::getRandomisedCards()
{
    return {model->getPlayerCardId(true), model->getPlayerCardId(false)};
}

void Controller::onMakeGuess(int cardIndex);
{
    model->updateTurnNum(isPrimaryPlayer);
    model->checkGuess(cardIndex, isPrimaryPlayer);
}

void Controller::onExitToMainMenu(bool includeSecondaryPlayer=false, QString sndUsername="");
{   
    addToLeaderboard(includeSecondaryPlayer, sndUsername);
    emit exitToMainMenu();
}

void Controller::addToLeaderboard(bool includeSecondaryPlayer, QString sndUsername)
{
    model->saveScores(includeSecondaryPlayer, sndUsername);
}

void Controller::onTurnOverEnd()
{
    emit showGameScreen();
}

void Controller::onCardsLowered() 
{
    model->updateTurnNum(isPrimaryPlayer);
    model->lowerCards(isPrimaryPlayer);
}

bool Controller::getPlayerTurn() 
{
    return isPrimaryPlayer;
}
void Controller::invertPlayerTurn() 
{
    isPrimaryPlayer = !isPrimaryPlayer;
}

// controller - gameloop - slots

void Controller::onTurnOver() 
{
    invertPlayerTurn();
    emit showTurnOverScreen();
}

void Controller::onGameOver()
{
    emit showGameOverScreen();
}

void Controller::onLowerFail()
{
    emit promptLowerFailPopup();
}