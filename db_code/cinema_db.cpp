#include "cinema_db.h"
#include <QApplication>

QString _getResourcesPath()
{
#if defined(Q_OS_WIN)
    return QApplication::applicationDirPath() + "/resources/";
#elif defined(Q_OS_MACOS)
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
    db.setDatabaseName(_getResourcesPath() + "game.db");
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