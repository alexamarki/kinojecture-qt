#include "leaderboard.h"

#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <sstream>
#include <string>
#include <gtest/gtest.h>

class LeaderboardDBTest : public ::testing::Test {
protected:
    void SetUp() override {
        db = new LeaderboardDB(":memory:");
        db->createTable();
    }

    void TearDown() override {
        delete db;
    }

    LeaderboardDB* db;
};

TEST_F(LeaderboardDBTest, CreateTableTest) {
    std::vector<std::string> results = db->sort_by_name();
    ASSERT_EQ(results.size(), 0);
}

TEST_F(LeaderboardDBTest, AddPlayerTest) {
    db->add_player("1234", "player1", 100, 10);
    std::vector<std::string> results = db->sort_by_name();
    ASSERT_EQ(results.size(), 1);
    ASSERT_TRUE(results[0].find("player1") != std::string::npos);
}

TEST_F(LeaderboardDBTest, UpdatePlayerRatingTest) {
    db->add_player("1234", "player1", 100, 10);
    db->update_player_rating("1234", "player1", 50);
    std::vector<std::string> results = db->sort_by_rating();
    ASSERT_EQ(results.size(), 1);
    ASSERT_TRUE(results[0].find("150") != std::string::npos); 
}

TEST_F(LeaderboardDBTest, FilterByPrefixTest) {
    db->add_player("1234", "player1", 100, 10);
    db->add_player("1235", "tester", 150, 20);
    std::vector<std::string> results = db->filter_by_prefix("pla");
    ASSERT_EQ(results.size(), 1);
    ASSERT_TRUE(results[0].find("player1") != std::string::npos);
}

TEST_F(LeaderboardDBTest, SortByGamesPlayedTest) {
    db->add_player("1234", "player1", 100, 10);
    db->add_player("1235", "player2", 150, 20);
    std::vector<std::string> results = db->sort_by_games_played();
    ASSERT_EQ(results.size(), 2);
    ASSERT_TRUE(results[0].find("player2") != std::string::npos); 
}

TEST_F(LeaderboardDBTest, IsPlayerInLeaderboardTest) {
    db->add_player("1234", "player1", 100, 10);
    bool exists = db->is_player_in_leaderboard("1234");
    ASSERT_TRUE(exists);
    exists = db->is_player_in_leaderboard("5678");
    ASSERT_FALSE(exists);
}

TEST_F(LeaderboardDBTest, ReplacePlayerDataTest) {
    LeaderboardDB temp_db(":memory:");
    temp_db.createTable();
    temp_db.add_player("1234", "player1", 100, 10);
    temp_db.add_player("1235", "player2", 200, 20);
    temp_db.save_database("temp.db");

    db->replace_player_data("temp.db");
    std::vector<std::string> results = db->sort_by_name();
    ASSERT_EQ(results.size(), 2);
    ASSERT_TRUE(results[0].find("player1") != std::string::npos);
    ASSERT_TRUE(results[1].find("player2") != std::string::npos);

    std::remove("temp.db");
}

TEST_F(LeaderboardDBTest, MergePlayerDataTest) {
    LeaderboardDB temp_db(":memory:");
    temp_db.createTable();
    temp_db.add_player("1234", "player1", 100, 10);
    temp_db.add_player("1235", "player2", 200, 20);
    temp_db.save_database("temp.db");

    db->add_player("1234", "player1", 100, 10);  
    db->merge_player_data("temp.db");
    std::vector<std::string> results = db->sort_by_name();
    ASSERT_EQ(results.size(), 2);
    ASSERT_TRUE(results[0].find("player1") != std::string::npos);
    ASSERT_TRUE(results[1].find("player2") != std::string::npos);
    ASSERT_TRUE(results[0].find("200") != std::string::npos); 

    std::remove("temp.db");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
