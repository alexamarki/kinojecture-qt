#include <gtest/gtest.h>
#include "game_model.h"
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


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}