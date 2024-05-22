#include "leaderboard.h"

int main() {
    LeaderboardDB db;
    db.createTable();

    // Fixed UUIDs for players
    QString uuid1 = "123e4567-e89b-12d3-a456-426614174000";
    QString uuid2 = "123e4567-e89b-12d3-a456-426614174001";

    // Adding new players
    db.add_player(uuid1, "PlayerOne", 1500, 10);
    db.add_player(uuid2, "PlayerTwo", 1200, 5);

    // Adding the same player (to update rating and games played)
    db.add_player(uuid1, "PlayerOneUpdated", 1600, 12);

    // Fetch and print the leaderboard sorted by name
    // std::vector<std::string> leaderboard = db.sort_by_name();
    // for (const auto& entry : leaderboard) {
    //     std::cout << entry << std::endl;
    // }
    // Save the database to a specified path
    db.save_database("../downloads/leaderboard_backup.db");
    return 0;
}
