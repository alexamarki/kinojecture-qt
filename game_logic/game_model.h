#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "../db_code/leaderboard.h"
#include <QObject>
#include <QRandomGenerator>
#include <QTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUuid>
#include <vector>
#include <unordered_set>

class Model : public QObject 
{
    Q_OBJECT
public:
    Model(QObject *parent = nullptr);

    // game model functions
    void initGame();
    void loadData(const std::vector<std::pair<std::string, std::string>>& data);
    void updateTurnNum(bool isPrimaryPlayer);
    // GMF - cards
    void addCardToSelection(int cardNum);
    void removeCardFromSelection(int cardNum);
    void lowerCards(bool isPrimaryPlayer);
    void checkGuess(int cardNum, bool isPrimaryPlayer);
    int getPlayerCardId(bool isPrimaryPlayer);
    std::pair<std::string, std::string> getData(int cardNum);
    // GMF - scoring
    void awardScores(bool isCorrect, bool isPrimaryPlayer);
    void saveScores(bool includeSecondPlayer);
    // local data modification
    void updateUUID(QString UUID);
    void updateUsername(QString username);
    // JSON functions
    QJsonObject readJSON(const QString& filePath);
    QJsonObject updateJSON(const QString &filePath, QString uuid, QString username, int points);
    

signals:
    void turnOverEvent();
    void endEvent();
    void lowerFail();

private:
    std::vector<std::pair<std::string, std::string>> dataList;
    std::pair<int, int> ids;
    std::pair<int, int> turns = {0, 0};
    std::pair<int, int> scores;
    std::unordered_set<int> _tempSelectedCards;
    std::unordered_set<int> loweredPrimary;
    std::unordered_set<int> loweredSecondary;
    bool localGame = true;
    const float INCORRECT_PRIMARY_WEIGHT = 0.6; // the fraction of points deducted from the score of a player who loses because of their incorrect guess
    const float CORRECT_OTHER_WEIGHT = 0.4; // the fraction of points deducted from the score of a player who loses because of the other player's correct guess
    const float INCORRECT_OTHER_WEIGHT = 0.6; // the fraction of points awarded to the player who wins because of the otehr player's incorrect guess
    const int MAX_GAME_POINTS = 5000;
    const QString PATH_JSON_PLAYER = "../data/parameters/player_data.json";
};

#endif