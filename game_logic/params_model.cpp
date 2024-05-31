#include "params_model.h"
#include "../db_code/leaderboard.h"

QJsonObject ParamsModel::readJSON(const QString &filePath) 
{
    QFile file(filePath);
    QTextStream stream(&file);
    QJsonDocument doc = QJsonDocument::fromJson(stream.readAll().toUtf8());
    QJsonObject jsonObj = doc.object();
    return jsonObj;
}

void ParamsModel::updateJSON(int sfxVolume=-1, int colourScheme=-1, QString username="") 
{
    QJsonObject jsonObj_player = readJSON(PATH_JSON_PLAYER);
    QJsonObject jsonObj_settings = readJSON(PATH_JSON_PARAMS);
    if (sfxVolume != -1 and sfxVolume >= 0 and sfxVolume <= 100)
        jsonObj_settings["sfx_volume"] = sfxVolume;
    if (colourScheme != -1)
        jsonObj_settings["colour_scheme"] = colourScheme;
    if (username != "")
        jsonObj_player["username"] = username; 
    LeaderboardDB leaderDB;
    leaderDB.rename_player(jsonObj_player["uuid"].toString(), username);
    QJsonDocument updatedFile_player(jsonObj_player);
    this->writeJSON(PATH_JSON_PLAYER, QString::fromUtf8(updatedFile_player.toJson()));
    QJsonDocument updatedFile_settings(jsonObj_settings);
    this->writeJSON(PATH_JSON_PARAMS, QString::fromUtf8(updatedFile_settings.toJson()));
    emit updateSettings();
}

void ParamsModel::writeJSON(const QString &filePath, const QString &jsonData) 
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << jsonData;
        file.close();
    }
}

QString ParamsModel::getUsername()
{
    QJsonObject jsonObj_player = readJSON(PATH_JSON_PLAYER);
    return jsonObj_player["username"].toString();
}
int ParamsModel::getSFXVolume()
{
    QJsonObject jsonObj_settings = readJSON(PATH_JSON_PARAMS);
    return jsonObj_settings["sfx_volume"].toInt();
}
int ParamsModel::getColourScheme()
{
    QJsonObject jsonObj_settings = readJSON(PATH_JSON_PARAMS);
    return jsonObj_settings["colour_scheme"].toInt();
}
