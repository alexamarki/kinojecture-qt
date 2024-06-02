#include "leaderboard.h"
#include <QApplication>

QString getResourcesPath()
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

LeaderboardDB::LeaderboardDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("/Users/alexamarki/Desktop/kinojecture-qt-local/data/leaderboard.db");
    db.setDatabaseName(getResourcesPath() + "leaderboard.db");
    if (!db.open()) {
        std::cerr << "Cannot open database: " << db.lastError().text().toStdString() << std::endl;
    }
}

LeaderboardDB::~LeaderboardDB() 
{
    db.close();
}

void LeaderboardDB::createTable() 
{
    QSqlQuery query(db);
    QString create_table_query = "CREATE TABLE IF NOT EXISTS leaderboard("
                                 "uuid TEXT PRIMARY KEY,"
                                 "nickname TEXT,"
                                 "rating INT,"
                                 "games_played INT);";
    query.prepare(create_table_query);
    if (!query.exec())
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
    }
}

bool LeaderboardDB::is_player_in_leaderboard(const QString& uuid)
{
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM leaderboard WHERE uuid = :uuid;");
    query.bindValue(":uuid", uuid);
    if (!query.exec() || !query.next()) 
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }
    return query.value(0).toInt() > 0;
}

void LeaderboardDB::add_player(const QString& uuid, const QString& nickname, int rating, int games_played) 
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO leaderboard (uuid, nickname, rating, games_played) VALUES (:uuid, :nickname, :rating, :games_played)");
    query.bindValue(":uuid", uuid);
    query.bindValue(":nickname", nickname);
    query.bindValue(":rating", rating);
    query.bindValue(":games_played", games_played);
    if (!query.exec())
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
    }
}

void LeaderboardDB::update_player_rating(const QString& uuid, int rating_points) 
{
    QSqlQuery query(db);
    query.prepare("UPDATE leaderboard SET rating = rating + :rating_points, games_played = games_played + 1 WHERE uuid = :uuid;");
    query.bindValue(":rating_points", rating_points);
    query.bindValue(":uuid", uuid);
    if (!query.exec())
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
    }
}

void LeaderboardDB::rename_player(const QString& uuid, const QString& new_nickname) 
{
    QSqlQuery query(db);
    query.prepare("UPDATE leaderboard SET nickname = :new_nickname WHERE uuid = :uuid;");
    query.bindValue(":new_nickname", new_nickname);
    query.bindValue(":uuid", uuid);
    if (!query.exec())
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
    }
}

void LeaderboardDB::save_database(const std::string& filepath) 
{
    try
    {
        std::filesystem::copy("../data/leaderboard.db", filepath, std::filesystem::copy_options::overwrite_existing);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}

QSqlDatabase LeaderboardDB::getDB() 
{
    return db;
}