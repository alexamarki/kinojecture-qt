#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>
#include <QRandomGenerator>
#include <QTime>

class Model : public QObject 
{
    Q_OBJECT
public:
    Model(QObject *parent = nullptr);

    void initGame();
    void loadData(const std::vector<std::pair<std::string, std::string>>& data);
    bool checkGuess(int cardNum, bool isPrimaryPlayer);
    void updateTurnNum(bool isPrimaryPlayer);
    void updateScores();
    int getPlayerCardId(bool isPrimaryPlayer);

signals:
    void updateEvent();

private:
    std::vector<std::pair<std::string, std::string>> dataList;
    std::pair<int, int> ids;
    std::pair<int, int> turns;
    std::pair<int, int> scores;

};

void Model::initGame() 
{
    QRandomGenerator generator = QRandomGenerator(static_cast<uint>(QTime::currentTime().msec()));
    ids.first = generator.generate() % dataList.size();
    ids.second = generator.generate() % dataList.size();
    emit updateEvent();
}

bool Model::checkGuess(int cardNum, bool isPrimaryPlayer) 
{
    int checkNum = isPrimaryPlayer ? ids.first : ids.second;
    bool correctGuess = (cardNum == checkNum);
    updateTurnNum(isPrimaryPlayer);
    return correctGuess;
} 

void Model::updateTurnNum(bool isPrimaryPlayer) 
{
    if (isPrimaryPlayer)
        turns.first++;
    else
        turns.second++;
}

int Model::getPlayerCardId(bool isPrimaryPlayer)
{
    return isPrimaryPlayer ? ids.first: ids.second;
}

#endif