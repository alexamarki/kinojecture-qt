#include "leaderboard.h"

int main() {
    LeaderboardDB leaderboard("../data/leaderboard.db");
    leaderboard.createTable();

    // Example usage: Replace player data from file
    leaderboard.replace_player_data("../data/players_replace.csv");

    // Example usage: Merge player data from file
    leaderboard.merge_player_data("../data/players_merge.csv");

    return 0;
}