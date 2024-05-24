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

    void initGame();
    void loadData(const std::vector<std::pair<std::string, std::string>>& data);
    void checkGuess(int cardNum, bool isPrimaryPlayer);
    void checkSkippable(std::vector<int> lowering, bool isPrimaryPlayer);
    void updateTurnNum(bool isPrimaryPlayer);
    void awardScores(bool isCorrect, bool isPrimaryPlayer);
    void saveScores(bool includeSecondPlayer);
    int getPlayerCardId(bool isPrimaryPlayer);
    QJsonObject readJSON(const QString& filePath);
    QJsonObject updateJSON(int points);
    void updateUUID(QString UUID);
    void updateUsername(QString username);

signals:
    void updateEvent();
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

void Model::loadData(const std::vector<std::pair<std::string, std::string>>& data)
{
    this->dataList = data;
}

void Model::initGame() 
{
    QRandomGenerator generator = QRandomGenerator(static_cast<uint>(QTime::currentTime().msec()));
    ids.first = generator.generate() % dataList.size();
    ids.second = generator.generate() % dataList.size();
    emit updateEvent();
}

void Model::checkGuess(int cardNum, bool isPrimaryPlayer) 
{
    int checkNum = isPrimaryPlayer ? ids.first : ids.second;
    bool correctGuess = (cardNum == checkNum);
    updateTurnNum(isPrimaryPlayer);
    awardScores(correctGuess, isPrimaryPlayer);
    emit endEvent();
} 

void Model::checkSkippable(std::vector<int> lowering, bool isPrimaryPlayer)
{
    int cardsLeft = dataList.size() - lowering.size() - (isPrimaryPlayer ? loweredPrimary.size() : loweredSecondary.size());
    if (cardsLeft > 1)
    {
        (isPrimaryPlayer ? loweredPrimary : loweredSecondary).insert(lowering.begin(), lowering.end());
        emit updateEvent();
    }
    else if (cardsLeft == 1)
    {
        for (int num = 0; num < dataList.size(); num++) {
            if ((isPrimaryPlayer ? loweredPrimary : loweredSecondary).find(num) == (isPrimaryPlayer ? loweredPrimary : loweredSecondary).end()) {
                this->checkGuess(num, isPrimaryPlayer);
                break;
            }
        }
    }
    else
        emit lowerFail();
}

void Model::updateTurnNum(bool isPrimaryPlayer) 
{
    if (isPrimaryPlayer)
        turns.first++;
    else
        turns.second++;
}

void Model::awardScores(bool isCorrect, bool isPrimaryPlayer)
{
    double maxPointTotal = MAX_GAME_POINTS * ((isPrimaryPlayer ? turns.first : turns.second) / dataList.size());
    if (isPrimaryPlayer)
    {
        scores.first = isCorrect ? maxPointTotal : (-maxPointTotal * INCORRECT_PRIMARY_WEIGHT);
        scores.second = isCorrect ? (-maxPointTotal * CORRECT_OTHER_WEIGHT) : (maxPointTotal * INCORRECT_OTHER_WEIGHT);
    }
    else
    {
        scores.second = isCorrect ? maxPointTotal : (-maxPointTotal * INCORRECT_PRIMARY_WEIGHT);
        scores.first = isCorrect ? (-maxPointTotal * CORRECT_OTHER_WEIGHT) : (maxPointTotal * INCORRECT_OTHER_WEIGHT);
    }
}

QJsonObject Model::readJSON(const QString &filePath) 
{
    QFile file(filePath);
    QTextStream stream(&file);
    QJsonDocument doc = QJsonDocument::fromJson(stream.readAll().toUtf8());
    QJsonObject jsonObj = doc.object();
    return jsonObj;
}

QJsonObject Model::updateJSON(const QString &filePath, QString uuid="", QString username="", int points=0) 
{
    QJsonObject jsonObj = readJSON(filePath);
    if (points != 0)
    {
        int currentScore = jsonObj["personal_score"].toInt();
        jsonObj["personal_score"] = currentScore + points;
    }
    if (uuid != "")
        jsonObj["uuid"] = uuid;
    if (username != "")
        jsonObj["username"] = username;
    QJsonDocument updatedFile(jsonObj);
    return QString::fromUtf8(updatedFile.toJson());
}

void Model::updateUUID() 
{
    QJsonObject jsonObj = readJSON(PATH_JSON_PLAYER);
    if (jsonObj["uuid"] == 0)
    {
        QUuid quuid = QUuid::createUuid();
        QString quuidString = quuid.toString();
    }
    writeJsonFile(PATH_JSON_PLAYER, updateJSON(PATH_JSON_PLAYER, uuid=quuidString));
}

void Model::updateUsername(QString username) 
{
    QJsonObject jsonObj = readJSON(PATH_JSON_PLAYER);
    writeJsonFile(PATH_JSON_PLAYER, updateJSON(PATH_JSON_PLAYER, username=username));
}

void Model::saveScores(bool includeSecondPlayer, QString snd_name="")
{
    std::string uuid = readJSON(PATH_JSON_PLAYER)["uuid"].toString();
    std::string nick = readJSON(PATH_JSON_PLAYER)["username"].toString();;  
    LeaderboardDB db;
    db.createTable();
    QString quuid = QString::fromStdString(uuid);
    QString qnick = QString::fromStdString(nick);
    if (db.is_player_in_leaderboard(quuid))
        db.update_player_rating(quuid, scores.first);
    else 
        db.add_player(quuid, qnick, scores.first);
    QJsonObject to_replace = updateJSON(PATH_JSON_PLAYER, points=scores.first);
    writeJsonFile(PATH_JSON_PLAYER, to_replace)
    if (includeSecondPlayer)
    {
        if (localGame)
        {
            int postfix = 1;
            while (true) 
            {
                if (db.is_player_in_leaderboard(QString::fromStdString(uuid + std::to_string(postfix))))
                    postfix++;
            }
            QString quuid_secondary = QString::fromStdString(uuid + std::to_string(postfix));
            db.add_player(quuid_secondary, snd_name, scores.second);
        } 
    }
}

int Model::getPlayerCardId(bool isPrimaryPlayer)
{
    return isPrimaryPlayer ? ids.first : ids.second;
}

#endif