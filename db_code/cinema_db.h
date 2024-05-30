#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>
#include <QFile>
#include <QIODevice>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class CinemaDB 
{
public:
    CinemaDB(const QString& db_path = "../data/game.db");
    ~CinemaDB();

    void createTable();

private:
    QSqlDatabase db;
};
