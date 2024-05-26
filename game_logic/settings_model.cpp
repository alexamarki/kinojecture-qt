#include "settings_model.h"

SettingsModel::SettingsModel(QObject *parent) : QObject(parent) {}

QJsonObject SettingsModel::readJSON(const QString &filePath) 
{
    QFile file(filePath);
    QTextStream stream(&file);
    QJsonDocument doc = QJsonDocument::fromJson(stream.readAll().toUtf8());
    QJsonObject jsonObj = doc.object();
    return jsonObj;
}

void SettingsModel::updateJSON(int sfxVolume=-1, int colourScheme=-1, QString username="") 
{
    QJsonObject jsonObj_player = readJSON(PATH_JSON_PLAYER);
    QJsonObject jsonObj_settings = readJSON(PATH_JSON_PARAMS);
    if (sfxVolume != -1 and sfxVolume >= 0 and sfxVolume <= 100)
        jsonObj_settings["sfx_volume"] = sfxVolume;
    if (colourScheme != -1)
        jsonObj_settings["colour_scheme"] = colourScheme;
    if (username != "")
        jsonObj_player["username"] = username; // need to make this update the DB as well
    QJsonDocument updatedFile_player(jsonObj_player);
    writeJsonFile(PATH_JSON_PLAYER, QString::fromUtf8(updatedFile_player.toJson()));
    QJsonDocument updatedFile_settings(jsonObj_settings);
    writeJsonFile(PATH_JSON_PARAMS, QString::fromUtf8(updatedFile_settings.toJson()));
    emit updateSettings();
}

QString SettingsModel::getUsername()
{
    QJsonObject jsonObj_player = readJSON(PATH_JSON_PLAYER);
    return jsonObj_player["username"].toString();
}
int SettingsModel::getSFXVolume()
{
    QJsonObject jsonObj_settings = readJSON(PATH_JSON_PARAMS);
    return jsonObj_settings["sfx_volume"].toInt();
}
int SettingsModel::getColourScheme()
{
    QJsonObject jsonObj_settings = readJSON(PATH_JSON_PARAMS);
    return jsonObj_settings["colour_scheme"].toInt();
}
