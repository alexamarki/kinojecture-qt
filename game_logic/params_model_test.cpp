#include <gtest/gtest.h>
#include "params_model.h"
#include "params_model.сpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QFile>
#include <QTextStream>

// Test fixture for ParamsModel class
class ParamsModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = new ParamsModel();
        createTestFiles();
    }

    void TearDown() override {
        delete model;
        removeTestFiles();
    }

    void createTestFiles() {
        QString playerData = R"(
        {
            "uuid": "12345",
            "username": "testuser"
        })";
        QString gameParams = R"(
        {
            "sfx_volume": 50,
            "colour_scheme": 1
        })";
        QFile filePlayer("../data/parameters/player_data.json");
        if (filePlayer.open(QIODevice::WriteOnly)) {
            QTextStream stream(&filePlayer);
            stream << playerData;
            filePlayer.close();
        }
        QFile fileParams("../data/parameters/game_parameters.json");
        if (fileParams.open(QIODevice::WriteOnly)) {
            QTextStream stream(&fileParams);
            stream << gameParams;
            fileParams.close();
        }
    }

    void removeTestFiles() {
        QFile::remove("../data/parameters/player_data.json");
        QFile::remove("../data/parameters/game_parameters.json");
    }

    ParamsModel* model;
};

// Test readJSON function
TEST_F(ParamsModelTest, ReadJSONTest) {
    QJsonObject jsonObj = model->readJSON("../data/parameters/player_data.json");
    EXPECT_EQ(jsonObj["uuid"].toString(), "12345");
    EXPECT_EQ(jsonObj["username"].toString(), "testuser");
}

// Test updateJSON function
TEST_F(ParamsModelTest, UpdateJSONTest) {
    model->updateJSON(75, 2, "newuser");

    QJsonObject jsonObjPlayer = model->readJSON("../data/parameters/player_data.json");
    EXPECT_EQ(jsonObjPlayer["username"].toString(), "newuser");

    QJsonObject jsonObjSettings = model->readJSON("../data/parameters/game_parameters.json");
    EXPECT_EQ(jsonObjSettings["sfx_volume"].toInt(), 75);
    EXPECT_EQ(jsonObjSettings["colour_scheme"].toInt(), 2);
}

// Test writeJSON function
TEST_F(ParamsModelTest, WriteJSONTest) {
    QString filePath = "../data/parameters/test_write.json";
    QString jsonData = R"({"key":"value"})";
    model->writeJSON(filePath, jsonData);

    QFile file(filePath);
    ASSERT_TRUE(file.open(QIODevice::ReadOnly));
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();

    EXPECT_EQ(content, jsonData);
    QFile::remove(filePath);
}

// Test getUsername function
TEST_F(ParamsModelTest, GetUsernameTest) {
    QString username = model->getUsername();
    EXPECT_EQ(username, "testuser");
}

// Test getSFXVolume function
TEST_F(ParamsModelTest, GetSFXVolumeTest) {
    int volume = model->getSFXVolume();
    EXPECT_EQ(volume, 50);
}

// Test getColourScheme function
TEST_F(ParamsModelTest, GetColourSchemeTest) {
    int scheme = model->getColourScheme();
    EXPECT_EQ(scheme, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
