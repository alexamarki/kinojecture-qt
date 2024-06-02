#include "cinema_db.h"
#include <QApplication>

QString getResourcesPath()
{
#if defined(Q_OS_WIN)
    return QApplication::applicationDirPath() + "/";
#elif defined(Q_OS_OSX)
    return QApplication::applicationDirPath() + "/../Resources/";
#elif defined(Q_OS_LINUX)
    return QApplication::applicationDirPath() + "/../share/yourapplication/";
#else
    return QApplication::applicationDirPath() + "/";
#endif
}

CinemaDB::CinemaDB() 
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/sotov/kinojecture-qt/data/game.db");
    if (!db.open()) {
        std::cerr << "Cannot open database: " << db.lastError().text().toStdString() << std::endl;
    }
}

CinemaDB::~CinemaDB() 
{
    db.close();
}

QSqlDatabase CinemaDB::getDB() 
{
    return db;
}