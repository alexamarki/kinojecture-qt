#include "leaderboard.h"

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <sstream>
#include <string>


int main() {
    LeaderboardDB db;
    db.createTable();

    // Fixed UUIDs for players
    std::string uuid1 = "123e4567-e89b-12d3-a456-426614174000";
    std::string uuid2 = "123e4567-e89b-12d3-a456-426614174001";

    // Adding new players
    db.add_player(uuid1, "PlayerOne", 1500, 10);
    db.add_player(uuid2, "PlayerTwo", 1200, 5);

    // Adding the same player (to update rating and games played)
    db.add_player(uuid1, "PlayerOneUpdated", 1600, 12);

    // Fetch and print the leaderboard sorted by name
    std::vector<std::string> leaderboard = db.sort_by_name();
    for (const auto& entry : leaderboard) {
        std::cout << entry << std::endl;
    }
    // Save the database to a specified path
    db.save_database("C:/Users/shubs/Downloads/leaderboard_backup.db");
    return 0;
}
