#include "game_model.h"

void Model::loadData(const std::vector<std::pair<std::string, std::string>>& data)
{
    this->dataList = data;
}

std::pair<std::string, std::string> Model::getData(int cardNum)
{
    return dataList[cardNum];
}

void Model::initGame(const std::vector<std::pair<std::string, std::string>>& data) 
{
    QRandomGenerator generator = QRandomGenerator(static_cast<uint>(QTime::currentTime().msec()));
    loadData(data);
    ids.first = generator.generate() % dataList.size();
    ids.second = generator.generate() % dataList.size();
}

void Model::checkGuess(int cardNum, bool isPrimaryPlayer) 
{
    int checkNum = isPrimaryPlayer ? ids.first : ids.second;
    bool correctGuess = (cardNum == checkNum);
    updateTurnNum(isPrimaryPlayer);
    awardScores(correctGuess, isPrimaryPlayer);
    emit endEvent();
} 

void Model::lowerCards(bool isPrimaryPlayer)
{
    int cardsLeft = dataList.size() - _tempSelectedCards.size() - (isPrimaryPlayer ? loweredPrimary.size() : loweredSecondary.size());
    if (cardsLeft > 1)
    {
        (isPrimaryPlayer ? loweredPrimary : loweredSecondary).insert(_tempSelectedCards.begin(), _tempSelectedCards.end());
        _tempSelectedCards.clear();
        this->updateTurnNum(isPrimaryPlayer);
        emit turnOverEvent();
    }
    else if (cardsLeft == 1)
    {
        for (int num = 0; num < dataList.size(); num++) {
            if ((isPrimaryPlayer ? loweredPrimary : loweredSecondary).find(num) == (isPrimaryPlayer ? loweredPrimary : loweredSecondary).end()) {
                this->updateTurnNum(isPrimaryPlayer);
                this->checkGuess(num, isPrimaryPlayer);
                _tempSelectedCards.clear();
                break;
            }
        }
    }
    else {
        _tempSelectedCards.clear();
        emit lowerFail();
    }
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
    QByteArray fileData = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObj = jsonDoc.object();
    return jsonObj;
}

QString Model::updateJSON(const QString &filePath, QString uuid="", QString username="", int points=0) 
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
    LeaderboardDB leaderDB;
    leaderDB.rename_player(jsonObj["uuid"].toString(), username);
    QJsonDocument updatedFile(jsonObj);
    return updatedFile.toJson();
}

void Model::updateUUID() 
{
    QJsonObject jsonObj = readJSON(PATH_JSON_PLAYER);
    if (jsonObj["uuid"] == "")
    {
        QUuid quuid = QUuid::createUuid();
        QString quuidString = quuid.toString();
        this->writeJSON(PATH_JSON_PLAYER, updateJSON(PATH_JSON_PLAYER, quuidString, "", 0));
    }
}

void Model::updateUsername(QString username) 
{
    QJsonObject jsonObj = readJSON(PATH_JSON_PLAYER);
    this->writeJSON(PATH_JSON_PLAYER, updateJSON(PATH_JSON_PLAYER, "", username, 0)); // need to make this update the DB as well, also separate into a different file, as this function is practically cloned in settings_model
}

void Model::saveScores(bool includeSecondPlayer, QString snd_name="")
{
    QString quuid = readJSON(PATH_JSON_PLAYER)["uuid"].toString();
    QString qnick = readJSON(PATH_JSON_PLAYER)["username"].toString(); 
    LeaderboardDB db;
    db.createTable();
    if (db.is_player_in_leaderboard(quuid))
        db.update_player_rating(quuid, scores.first);
    else 
        db.add_player(quuid, qnick, scores.first);
    QString to_replace = updateJSON(PATH_JSON_PLAYER, "", "", scores.first);
    writeJSON(PATH_JSON_PLAYER, to_replace);
    if (includeSecondPlayer)
    {
        if (localGame)
        {
            int postfix = 1;
            while (true) 
            {
                if (db.is_player_in_leaderboard(quuid + QString::fromStdString(std::to_string(postfix))))
                    postfix++;
            }
            QString quuid_secondary = quuid + QString::fromStdString(std::to_string(postfix));
            db.add_player(quuid_secondary, snd_name, scores.second);
        } 
    }
}

int Model::getPlayerCardId(bool isPrimaryPlayer)
{
    return isPrimaryPlayer ? ids.first : ids.second;
}

void Model::addCardToSelection(int cardNum)
{
    _tempSelectedCards.insert(cardNum);
}

void Model::removeCardFromSelection(int cardNum)
{
    _tempSelectedCards.erase(cardNum);
}

std::unordered_set<int> Model::getLowered(bool isPrimaryPlayer)
{
    return isPrimaryPlayer ? this->loweredPrimary : this->loweredSecondary;
}

void Model::writeJSON(const QString &filePath, const QString &jsonData) 
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << jsonData;
        file.close();
    }
}
