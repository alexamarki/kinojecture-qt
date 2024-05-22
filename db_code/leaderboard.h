#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVariant>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class LeaderboardDB 
{
public:
    LeaderboardDB(const QString& db_path = "../data/leaderboard.db");
    ~LeaderboardDB();

    void createTable();
    void sql_exec(const QString& query);
    void replace_player_data(const QString& filepath);
    void merge_player_data(const QString& filepath);
    std::vector<QString> filter_by_prefix(const QString& prefix);
    std::vector<QString> filter_by_rating_greater(int min_rating);
    std::vector<QString> filter_by_rating_less(int max_rating);
    bool is_player_in_leaderboard(const QString& uuid);
    void add_player(const QString& uuid, const QString& nickname, int rating = 0, int games_played = 1);
    void update_player_rating(const QString& uuid, const QString& nickname, int rating_points);
    std::vector<QString> sort_by_name();
    std::vector<QString> sort_by_games_played();
    std::vector<QString> sort_by_rating();
    void save_database(const QString& filepath);

private:
    QSqlDatabase db;
    static std::vector<QString> query_to_vector(QSqlQuery& query);
};

LeaderboardDB::LeaderboardDB(const QString& db_path) 
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);
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
    QString create_table_query = "CREATE TABLE IF NOT EXISTS leaderboard("
                                     "uuid TEXT PRIMARY KEY,"
                                     "nickname TEXT,"
                                     "rating INT,"
                                     "games_played INT);";
    sql_exec(create_table_query);
}

void LeaderboardDB::sql_exec(const QString& query) 
{
    QSqlQuery q;
    if (!q.exec(query)) 
    {
        std::cerr << "SQL error: " << q.lastError().text().toStdString() << std::endl;
    }
}

void LeaderboardDB::replace_player_data(const QString& db_filepath) 
{
    sql_exec("DELETE FROM leaderboard;");

    QSqlDatabase source_db = QSqlDatabase::addDatabase("QSQLITE", "source_connection");
    source_db.setDatabaseName(db_filepath);
    if (!source_db.open()) 
    {
        std::cerr << "Cannot open source database: " << source_db.lastError().text().toStdString() << std::endl;
        return;
    }

    QSqlQuery query(source_db);
    if (!query.exec("SELECT uuid, nickname, rating, games_played FROM leaderboard;")) 
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
        source_db.close();
        return;
    }

    while (query.next()) 
    {
        QString uuid = query.value(0).toString();
        QString nickname = query.value(1).toString();
        int rating = query.value(2).toInt();
        int games_played = query.value(3).toInt();
        add_player(uuid, nickname, rating, games_played);
    }

    source_db.close();
}

void LeaderboardDB::merge_player_data(const QString& db_filepath) 
{
    QSqlDatabase source_db = QSqlDatabase::addDatabase("QSQLITE", "source_connection");
    source_db.setDatabaseName(db_filepath);
    if (!source_db.open()) 
    {
        std::cerr << "Cannot open source database: " << source_db.lastError().text().toStdString() << std::endl;
        return;
    }

    QSqlQuery query(source_db);
    if (!query.exec("SELECT uuid, nickname, rating, games_played FROM leaderboard;")) 
    {
        std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
        source_db.close();
        return;
    }

    while (query.next()) 
    {
        QString uuid = query.value(0).toString();
        QString nickname = query.value(1).toString();
        int rating = query.value(2).toInt();
        int games_played = query.value(3).toInt();

        if (is_player_in_leaderboard(uuid)) 
        {
            QString update_query = QString("UPDATE leaderboard SET rating = rating + %1, games_played = games_played + %2 WHERE uuid = '%3';")
                                   .arg(rating).arg(games_played).arg(uuid);
            sql_exec(update_query);
        } 
        else 
        {
            add_player(uuid, nickname, rating, games_played);
        }
    }

    source_db.close();
}

bool LeaderboardDB::is_player_in_leaderboard(const QString& uuid)
{
    QSqlQuery query;
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
    if (is_player_in_leaderboard(uuid)) 
    {
        QString update_query = QString("UPDATE leaderboard SET rating = rating + %1, games_played = games_played + %2, nickname = '%3' WHERE uuid = '%4';")
                               .arg(rating).arg(games_played).arg(nickname).arg(uuid);
        sql_exec(update_query);
    } 
    else 
    {
        QSqlQuery query;
        query.prepare("INSERT INTO leaderboard (uuid, nickname, rating, games_played) VALUES (:uuid, :nickname, :rating, :games_played);");
        query.bindValue(":uuid", uuid);
        query.bindValue(":nickname", nickname);
        query.bindValue(":rating", rating);
        query.bindValue(":games_played", games_played);
        if (!query.exec())
            std::cerr << "Failed to execute statement: " << query.lastError().text().toStdString() << std::endl;
    }
}

void LeaderboardDB::update_player_rating(const QString& uuid, const QString& nickname, int rating_points) 
{
    QString update_query = QString("UPDATE leaderboard SET rating = rating + %1, games_played = games_played + 1, nickname = '%2' WHERE uuid = '%3';")
                           .arg(rating_points).arg(nickname).arg(uuid);
    sql_exec(update_query);
}

void LeaderboardDB::save_database(const QString& filepath) 
{
    QSqlDatabase backup_db = QSqlDatabase::addDatabase("QSQLITE", "backup_connection");
    backup_db.setDatabaseName(filepath);
    if (!backup_db.open()) 
    {
        std::cerr << "Cannot open backup database: " << backup_db.lastError().text().toStdString() << std::endl;
        return;
    }
    if (!db.transaction() || !backup_db.transaction()) 
    {
        std::cerr << "Failed to start transaction: " << db.lastError().text().toStdString() << std::endl;
        return;
    }
    QString backup_query = "ATTACH DATABASE '" + filepath + "' AS backup_db; "
                           "BEGIN; "
                           "DELETE FROM backup_db.leaderboard; "
                           "INSERT INTO backup_db.leaderboard SELECT * FROM main.leaderboard; "
                           "COMMIT; "
                           "DETACH DATABASE backup_db;";
    sql_exec(backup_query);

    if (!db.commit() || !backup_db.commit()) 
    {
        std::cerr << "Failed to commit transaction: " << db.lastError().text().toStdString() << std::endl;
        return;
    }

    backup_db.close();
}

