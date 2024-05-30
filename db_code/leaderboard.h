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

class LeaderboardDB 
{
public:
    LeaderboardDB(const QString& db_path = "../data/leaderboard.db");
    ~LeaderboardDB();

    void createTable();
    void sql_exec(const QString& query);
    void replace_player_data(const QString& filepath);
    void merge_player_data(const QString& filepath);
    bool is_player_in_leaderboard(const QString& uuid);
    void add_player(const QString& uuid, const QString& nickname, int rating = 0, int games_played = 1);
    void update_player_rating(const QString& uuid, int rating_points);
    void save_database(const std::string& filepath);
    void rename_player(const QString& uuid, const QString& new_nickname);

private:
    QSqlDatabase db;
    static std::vector<QString> query_to_vector(QSqlQuery& query);
};
