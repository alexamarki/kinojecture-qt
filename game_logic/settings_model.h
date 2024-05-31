#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <vector>

class SettingsModel : public QObject 
{
    Q_OBJECT
public:
    SettingsModel(QObject *parent = nullptr);

    // settings model functions
    QJsonObject readJSON(const QString& filePath);
    void updateJSON(int sfxVolume, int colourScheme, QString username);
    QString getUsername();
    int getSFXVolume(); // pass for now
    int getColourScheme(); // pass for now

signals:
    void updateSettings(); // to update name + the colour scheme

private:
    const QString PATH_JSON_PARAMS = "../data/parameters/game_parameters.json";
    const QString PATH_JSON_PLAYER = "../data/parameters/player_data.json";
};

#endif