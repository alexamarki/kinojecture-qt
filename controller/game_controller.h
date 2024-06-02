#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <QObject>
#include "../game_logic/game_model.h"

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(QObject *parent = nullptr) : QObject(parent) {
        this->model = new Model(this);
    }

    // gameloop controllers
    void startGame(const std::vector<std::pair<std::string, std::string>>& data);
    void onCardSelected(int cardIndex); //when card is selected BBBBBBBBBBBBBBBBBB
    void onCardDeselected(int cardIndex); //when card is deselected BBBBBBBBBBBBBBBBBBB
    std::pair<std::string, std::string> onCardHovered(int cardIndex);
    void onCardsLowered(); //when we make a guess button BBBBBBBBBBBBBBBBB
    std::pair<int, int> getRandomisedCards();
    std::unordered_set<int> getLowered(bool isPrimaryPlayer); //returns a set of card indices BBBBBBBBBBBBBBBBBBBBBBB
    void onMakeGuess(int cardIndex);
    void onExitToMainMenu(bool includeSecondaryPlayer, QString sndUsername); //from game over screen  
    void addToLeaderboard(bool includeSecondaryPlayer, QString sndUsername);
    bool getPlayerTurn();
    void invertPlayerTurn();
    void onTurnOverEnd();
    Model *model;

public slots:
    // gameloop controller slots
    void onTurnOver(); // link to Model::turnOverEvent()
    void onGameOver(); // link to Model::endEvent()
    void onLowerFail(); // link to Model::lowerFail() - you chose to many cards (pop up)

signals: // to connect to View SLOTS, which are yet to be implemented
    // gameloop controller signals
    void showRulesScreen(); //empty screen (only label + next button) -> next -> cards display (4) AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    void introduceRandomisedCards(); // called in a View function, not here 
    void showGameScreen(); //show game screen AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    void promptLowerFailPopup();
    void showTurnOverScreen(); //players turn -> next (onTurnOverEnd()) AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    void showGameOverScreen();
    void exitToMainMenu(); 

private:
    bool isPrimaryPlayer = true;
};

#endif