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

    bool is_player_in_leaderboard(const std::string& nickname);
    void add_player(const std::string& nickname, int rating = 0, int games_played = 0);
    void update_player_rating(const std::string& nickname, int rating_points);

private:
    sqlite3* db;
    int exit;
};

LeaderboardDB::LeaderboardDB(const std::string& db_path) {
    exit = sqlite3_open(db_path.c_str(), &db);
    if (exit) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }
}

LeaderboardDB::~LeaderboardDB() {
    sqlite3_close(db);
}

void LeaderboardDB::createTable() {
    std::string create_table_query = "CREATE TABLE IF NOT EXISTS leaderboard("
                                     "nickname TEXT PRIMARY KEY,"
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
    } else {
        std::cout << "SQL executed successfully" << std::endl;
    }
}

void LeaderboardDB::replace_player_data(const std::string& filepath) {
    std::string clear_table_query = "DELETE FROM leaderboard;";
    sql_exec(clear_table_query);

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filepath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Assuming the first line is the header
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string nickname, rating, games_played;

        std::getline(iss, nickname, ',');
        std::getline(iss, rating, ',');
        std::getline(iss, games_played, ',');

        add_player(nickname, std::stoi(rating), std::stoi(games_played));
    }
}

void LeaderboardDB::merge_player_data(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filepath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Assuming the first line is the header
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string nickname, rating, games_played;

        std::getline(iss, nickname, ',');
        std::getline(iss, rating, ',');
        std::getline(iss, games_played, ',');

        if (is_player_in_leaderboard(nickname)) {
            std::string update_query = "UPDATE leaderboard SET rating = rating + " + rating + 
                                       ", games_played = games_played + " + games_played +
                                       " WHERE nickname = '" + nickname + "';";
            sql_exec(update_query);
        } else {
            add_player(nickname, std::stoi(rating), std::stoi(games_played));
        }
    }
}

bool LeaderboardDB::is_player_in_leaderboard(const std::string& nickname) {
    std::string query = "SELECT COUNT(*) FROM leaderboard WHERE nickname = '" + nickname + "';";
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

void LeaderboardDB::add_player(const std::string& nickname, int rating, int games_played) {
    std::string insert_query = "INSERT INTO leaderboard (nickname, rating, games_played) VALUES ('" 
                                + nickname + "', " + std::to_string(rating) + ", " + std::to_string(games_played) + ");";
    sql_exec(insert_query);
}

void LeaderboardDB::update_player_rating(const std::string& nickname, int rating_points) {
    std::string update_query = "UPDATE leaderboard SET rating = rating + " + std::to_string(rating_points) + 
                               ", games_played = games_played + 1 WHERE nickname = '" + nickname + "';";
    sql_exec(update_query);
}