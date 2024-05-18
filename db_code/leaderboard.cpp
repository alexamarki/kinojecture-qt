#include "leaderboard.h"

int main() {
    LeaderboardDB leaderboard("../data/leaderboard.db");
    leaderboard.createTable();

    // Adding initial data
    leaderboard.add_player("player1", 1500); // Games default to 1
    leaderboard.add_player("player2", 1600, 20);
    leaderboard.add_player("player3", 1700, 30);
    leaderboard.add_player("player1", 1500); // Duplicate player for testing

    // Displaying initial data
    std::cout << "Initial data:" << std::endl;
    for (const auto& row : leaderboard.sort_by_name()) {
        std::cout << row << std::endl;
    }

    // Creating temporary database for replacement
    LeaderboardDB temp_replace_db("../data/temp_replace.db");
    temp_replace_db.createTable();
    temp_replace_db.add_player("player4", 1800);
    temp_replace_db.add_player("player5", 1900, 50);

    // Replacing old data with new data
    leaderboard.replace_player_data("../data/temp_replace.db");

    // Displaying data after replacement
    std::cout << "\nData after replace:" << std::endl;
    for (const auto& row : leaderboard.sort_by_name()) {
        std::cout << row << std::endl;
    }

    // Creating temporary database for merging
    LeaderboardDB temp_merge_db("../data/temp_merge.db");
    temp_merge_db.createTable();
    temp_merge_db.add_player("player1", 200, 5); // Duplicate player for testing merge
    temp_merge_db.add_player("player6", 2000, 60);

    // Merging data
    leaderboard.merge_player_data("../data/temp_merge.db");

    // Displaying data after merging
    std::cout << "\nData after merge:" << std::endl;
    for (const auto& row : leaderboard.sort_by_name()) {
         std::cout << row << std::endl;
    }

    // Sorting and displaying data
    std::cout << "\nSorted by name:" << std::endl;
    for (const auto& row : leaderboard.sort_by_name()) {
        std::cout << row << std::endl;
    }

    std::cout << "\nSorted by games played:" << std::endl;
    for (const auto& row : leaderboard.sort_by_games_played()) {
        std::cout << row << std::endl;
    }

    std::cout << "\nSorted by rating:" << std::endl;
    for (const auto& row : leaderboard.sort_by_rating()) {
        std::cout << row << std::endl;
    }

    return 0;
}