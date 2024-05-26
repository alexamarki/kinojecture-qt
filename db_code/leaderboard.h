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
    std::vector<QString> filter_by_prefix(const QString& prefix);
    std::vector<QString> filter_by_rating_greater(int min_rating);
    std::vector<QString> filter_by_rating_less(int max_rating);
    bool is_player_in_leaderboard(const QString& uuid);
    void add_player(const QString& uuid, const QString& nickname, int rating = 0, int games_played = 1);
    void update_player_rating(const QString& uuid, int rating_points);
    std::vector<QString> sort_by_name();
    std::vector<QString> sort_by_games_played();
    std::vector<QString> sort_by_rating();
    void save_database(const std::string& filepath);

private:
    QSqlDatabase db;
    static std::vector<QString> query_to_vector(QSqlQuery& query);
};

