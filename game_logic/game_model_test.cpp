#include <gtest/gtest.h>
#include "game_model.h"
#include "game_model.cpp"
#include <vector>
#include <utility>
#include <QString>

// Test fixture for Model class
class ModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = new Model();
    }

    void TearDown() override {
        delete model;
    }

    Model* model;
};

// Test initialization of the game with data
TEST_F(ModelTest, InitGameTest) {
    std::vector<std::pair<std::string, std::string>> data = {{"card1", "desc1"}, {"card2", "desc2"}};
    model->initGame(data);
    
    EXPECT_EQ(data.size(), model->dataList.size());
    EXPECT_NE(model->getPlayerCardId(true), model->getPlayerCardId(false)); // Ensure that ids are different
}

// Test loadData function
TEST_F(ModelTest, LoadDataTest) {
    std::vector<std::pair<std::string, std::string>> data = {{"card1", "desc1"}, {"card2", "desc2"}};
    model->loadData(data);

    EXPECT_EQ(data.size(), model->dataList.size());
    EXPECT_EQ(data[0].first, model->dataList[0].first);
}

// Test getData function
TEST_F(ModelTest, GetDataTest) {
    std::vector<std::pair<std::string, std::string>> data = {{"card1", "desc1"}, {"card2", "desc2"}};
    model->loadData(data);

    auto result = model->getData(0);
    EXPECT_EQ(result.first, "card1");
    EXPECT_EQ(result.second, "desc1");
}

// Test checkGuess function
TEST_F(ModelTest, CheckGuessTest) {
    std::vector<std::pair<std::string, std::string>> data = {{"card1", "desc1"}, {"card2", "desc2"}};
    model->initGame(data);
    
    int cardId = model->getPlayerCardId(true);

    EXPECT_NO_THROW(model->checkGuess(cardId, true));
    EXPECT_NO_THROW(model->checkGuess(cardId, false));
}

// Test lowerCards function
TEST_F(ModelTest, LowerCardsTest) {
    std::vector<std::pair<std::string, std::string>> data = {{"card1", "desc1"}, {"card2", "desc2"}};
    model->initGame(data);

    model->addCardToSelection(0);
    model->lowerCards(true);

    EXPECT_EQ(model->getLowered(true).size(), 1);
}

// Test awardScores function
TEST_F(ModelTest, AwardScoresTest) {
    std::vector<std::pair<std::string, std::string>> data = {{"card1", "desc1"}, {"card2", "desc2"}};
    model->initGame(data);
    
    model->awardScores(true, true);
    EXPECT_GT(model->scores.first, 0);

    model->awardScores(false, true);
    EXPECT_LT(model->scores.first, 0);
}

// Test updateUUID function
TEST_F(ModelTest, UpdateUUIDTest) {
    // Mock readJSON and writeJSON functions if necessary to avoid file I/O
    // Assuming readJSON and writeJSON are mocked
    
    model->updateUUID();
    // Add expectations for the UUID update
}

// Test updateUsername function
TEST_F(ModelTest, UpdateUsernameTest) {
    // Mock readJSON and writeJSON functions if necessary to avoid file I/O
    // Assuming readJSON and writeJSON are mocked
    
    QString username = "testuser";
    model->updateUsername(username);
    // Add expectations for the username update
}

// Test saveScores function
TEST_F(ModelTest, SaveScoresTest) {
    // Mock necessary database interactions and file I/O
    // Assuming necessary mocks
    
    model->saveScores(false, "");
    // Add expectations for saving scores
}

// Test readJSON function
TEST_F(ModelTest, ReadJSONTest) {
    // Mock file reading if necessary to avoid file I/O
    // Assuming readJSON is mocked
    
    QString filePath = "path/to/test.json";
    QJsonObject jsonObj = model->readJSON(filePath);
    // Add expectations for JSON reading
}

// Test writeJSON function
TEST_F(ModelTest, WriteJSONTest) {
    // Mock file writing if necessary to avoid file I/O
    // Assuming writeJSON is mocked
    
    QString filePath = "path/to/test.json";
    QString jsonData = "{\"key\":\"value\"}";
    model->writeJSON(filePath, jsonData);
    // Add expectations for JSON writing
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}