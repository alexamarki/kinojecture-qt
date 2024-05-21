#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class Model : public QObject {
    Q_OBJECT
public:
    Model(QObject *parent = nullptr);

    void initGame();
    void loadData(const std::vector<std::pair<std::string, std::string>>& data);
    bool checkGuess(std::string card_id, bool isPrimaryPlayer);
    void updateTurnNum(bool isPrimaryPlayer);
    int getPlayerCardId(bool isPrimaryPlayer) const;

signals:
    void updateEvent();

private:
    QJsonArray dataList;
    std::pair<int, int> turns;
    std::pair<int, int> scores;

};

#endif