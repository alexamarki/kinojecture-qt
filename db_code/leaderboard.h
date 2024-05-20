#include <sqlite3.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class LeaderboardDB {
public:
    LeaderboardDB(const std::string& db_path = "../data/leaderboard.db");
    ~LeaderboardDB();

    void createTable();
    void sql_exec(const std::string& query, sqlite3_callback callback = nullptr, void* pArg = nullptr);
    void replace_player_data(const std::string& filepath);
    void merge_player_data(const std::string& filepath);
    std::vector<std::string> filter_by_prefix(const std::string& prefix);
    std::vector<std::string> filter_by_rating_greater(int min_rating);
    std::vector<std::string> filter_by_rating_less(int max_rating);
    bool is_player_in_leaderboard(const std::string& uuid);
    void add_player(const std::string& uuid, const std::string& nickname, int rating = 0, int games_played = 1);
    void update_player_rating(const std::string& uuid, const std::string& nickname, int rating_points);
    std::vector<std::string> sort_by_name();
    std::vector<std::string> sort_by_games_played();
    std::vector<std::string> sort_by_rating();
    void save_database(const std::string& filepath);

private:
    sqlite3* db;
    int exit;
    static int callback(void* data, int argc, char** argv, char** azColName);
};

LeaderboardDB::LeaderboardDB(const std::string& db_path) {
    exit = sqlite3_open(db_path.c_str(), &db);
    if (exit) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    }
}

LeaderboardDB::~LeaderboardDB() {
    sqlite3_close(db);
}

void LeaderboardDB::createTable() {
    std::string create_table_query = "CREATE TABLE IF NOT EXISTS leaderboard("
                                     "uuid TEXT PRIMARY KEY,"
                                     "nickname TEXT,"
                                     "rating INT,"
                                     "games_played INT);";
    sql_exec(create_table_query);
}

void LeaderboardDB::sql_exec(const std::string& query, sqlite3_callback callback, void* pArg) {
    char* queryError;
    exit = sqlite3_exec(db, query.c_str(), callback, pArg, &queryError);
    if (exit != SQLITE_OK) {
        std::cerr << "SQL error: " << queryError << std::endl;
        sqlite3_free(queryError);
    }
}

void LeaderboardDB::replace_player_data(const std::string& db_filepath) {
    std::string clear_table_query = "DELETE FROM leaderboard;";
    sql_exec(clear_table_query);

    sqlite3* source_db;
    exit = sqlite3_open(db_filepath.c_str(), &source_db);
    if (exit) {
        std::cerr << "Cannot open source database: " << sqlite3_errmsg(source_db) << std::endl;
        return;
    }

    std::string query = "SELECT uuid, nickname, rating, games_played FROM leaderboard;";
    sqlite3_stmt* stmt;
    exit = sqlite3_prepare_v2(source_db, query.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(source_db) << std::endl;
        sqlite3_close(source_db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string uuid = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string nickname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int rating = sqlite3_column_int(stmt, 2);
        int games_played = sqlite3_column_int(stmt, 3);
        add_player(uuid, nickname, rating, games_played);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(source_db);
}

void LeaderboardDB::merge_player_data(const std::string& db_filepath) {
    sqlite3* source_db;
    exit = sqlite3_open(db_filepath.c_str(), &source_db);
    if (exit) {
        std::cerr << "Cannot open source database: " << sqlite3_errmsg(source_db) << std::endl;
        return;
    }

    std::string query = "SELECT uuid, nickname, rating, games_played FROM leaderboard;";
    sqlite3_stmt* stmt;
    exit = sqlite3_prepare_v2(source_db, query.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(source_db) << std::endl;
        sqlite3_close(source_db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string uuid = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string nickname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int rating = sqlite3_column_int(stmt, 2);
        int games_played = sqlite3_column_int(stmt, 3);

        if (is_player_in_leaderboard(uuid)) {
            std::string update_query = "UPDATE leaderboard SET rating = rating + " + std::to_string(rating) + 
                                       ", games_played = games_played + " + std::to_string(games_played) +
                                       " WHERE uuid = '" + uuid + "';";
            sql_exec(update_query);
        } else {
            add_player(uuid, nickname, rating, games_played);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(source_db);
}

bool LeaderboardDB::is_player_in_leaderboard(const std::string& uuid) {
    std::string query = "SELECT COUNT(*) FROM leaderboard WHERE uuid = '" + uuid + "';";
    sqlite3_stmt* stmt;
    exit = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (exit != SQLITE_OK) {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count > 0;
}

void LeaderboardDB::add_player(const std::string& uuid, const std::string& nickname, int rating, int games_played) {
    if (is_player_in_leaderboard(uuid)) {
        std::string update_query = "UPDATE leaderboard SET rating = rating + " + std::to_string(rating) + 
                                   ", games_played = games_played + " + std::to_string(games_played) +
                                   ", nickname = '" + nickname + "'" +
                                   " WHERE uuid = '" + uuid + "';";
        sql_exec(update_query);
    } else {
        std::string insert_query = "INSERT INTO leaderboard (uuid, nickname, rating, games_played) VALUES ('" 
                                    + uuid + "', '" + nickname + "', " + std::to_string(rating) + ", " + std::to_string(games_played) + ");";
        sql_exec(insert_query);
    }
}

void LeaderboardDB::update_player_rating(const std::string& uuid, const std::string& nickname, int rating_points) {
    std::string update_query = "UPDATE leaderboard SET rating = rating + " + std::to_string(rating_points) + 
                               ", games_played = games_played + 1" +
                               ", nickname = '" + nickname + "'" +
                               " WHERE uuid = '" + uuid + "';";
    sql_exec(update_query);
}

int LeaderboardDB::callback(void* data, int argc, char** argv, char** azColName) {
    auto* results = static_cast<std::vector<std::string>*>(data);
    std::ostringstream oss;
    for (int i = 0; i < argc; i++) {
        oss << (argv[i] ? argv[i] : "NULL") << (i < argc - 1 ? ", " : "");
    }
    results->push_back(oss.str());
    return 0;
}

std::vector<std::string> LeaderboardDB::sort_by_name() {
    std::string query = "SELECT * FROM leaderboard ORDER BY nickname ASC;";
    std::vector<std::string> results;
    sql_exec(query, callback, &results);
    return results;
}

std::vector<std::string> LeaderboardDB::sort_by_games_played() {
    std::string query = "SELECT * FROM leaderboard ORDER BY games_played DESC;";
    std::vector<std::string> results;
    sql_exec(query, callback, &results);
    return results;
}

std::vector<std::string> LeaderboardDB::sort_by_rating() {
    std::string query = "SELECT * FROM leaderboard ORDER BY rating DESC;";
    std::vector<std::string> results;
    sql_exec(query, callback, &results);
    return results;
}

std::vector<std::string> LeaderboardDB::filter_by_prefix(const std::string& prefix) {
    std::string query = "SELECT * FROM leaderboard WHERE nickname LIKE '" + prefix + "%';";
    std::vector<std::string> results;
    sql_exec(query, callback, &results);
    return results;
}

std::vector<std::string> LeaderboardDB::filter_by_rating_greater(int min_rating) {
    std::string query = "SELECT * FROM leaderboard WHERE rating >= " + std::to_string(min_rating) + ";";
    std::vector<std::string> results;
    sql_exec(query, callback, &results);
    return results;
}

std::vector<std::string> LeaderboardDB::filter_by_rating_less(int max_rating) {
    std::string query = "SELECT * FROM leaderboard WHERE rating <= " + std::to_string(max_rating) + ";";
    std::vector<std::string> results;
    sql_exec(query, callback, &results);
    return results;
}

void LeaderboardDB::save_database(const std::string& filepath) {
    sqlite3* backup_db;
    exit = sqlite3_open(filepath.c_str(), &backup_db);
    if (exit != SQLITE_OK) {
        std::cerr << "Cannot open backup database: " << sqlite3_errmsg(backup_db) << std::endl;
        return;
    }

    sqlite3_backup* backup = sqlite3_backup_init(backup_db, "main", db, "main");
    if (backup) {
        sqlite3_backup_step(backup, -1);
        sqlite3_backup_finish(backup);
    }
    sqlite3_close(backup_db);
}