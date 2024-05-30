#include "cinema_db.h"

CinemaDB::CinemaDB(const QString& db_path) 
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cinema_db");
    if (!db.open()) {
        std::cerr << "Cannot open database: " << db.lastError().text().toStdString() << std::endl;
    }
}

CinemaDB::~CinemaDB() 
{
    db.close();
}