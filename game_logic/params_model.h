#ifndef PARAMS_MODEL_H
#define PARAMS_MODEL_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <vector>

class ParamsModel : public QObject 
{
    Q_OBJECT
public:
    ParamsModel(QObject *parent = nullptr) : QObject(parent) {}

    // settings model functions
    QJsonObject readJSON(const QString& filePath);
    void updateJSON(int sfxVolume, int colourScheme, QString username);
    void writeJSON(const QString &filePath, const QString &jsonData);
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