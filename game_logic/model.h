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
    void awardScores(bool isCorrect, bool isPrimaryPlayer);
    void saveScores(bool includeSecondPlayer);
    int getPlayerCardId(bool isPrimaryPlayer);

signals:
    void updateEvent();

private:
    std::vector<std::pair<std::string, std::string>> dataList;
    std::pair<int, int> ids;
    std::pair<int, int> turns;
    std::pair<int, int> scores;
    bool localGame = true;
    const float INCORRECT_PRIMARY_WEIGHT = 0.6; // the fraction of points deducted from the score of a player who loses because of their incorrect guess
    const float CORRECT_OTHER_WEIGHT = 0.4; // the fraction of points deducted from the score of a player who loses because of the other player's correct guess
    const float INCORRECT_OTHER_WEIGHT = 0.6; // the fraction of points awarded to the player who wins because of the otehr player's incorrect guess
    const int MAX_GAME_POINTS = 5000;
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
    awardScores(correctGuess, isPrimaryPlayer);
    return correctGuess;
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

void Model::saveScores(bool includeSecondPlayer)
{
    if (localGame)
    {

        if (includeSecondPlayer)
        {

        }
    }
}

int Model::getPlayerCardId(bool isPrimaryPlayer)
{
    return isPrimaryPlayer ? ids.first: ids.second;
}

#endif