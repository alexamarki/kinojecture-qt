#include <gtest/gtest.h>
#include <QStandardItemModel>
#include "selection_model.h"
#include "selection_model.cpp"

// Test Fixture for SelectionModel
class SelectionModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a standard item model with test data
        sourceModel = new QStandardItemModel(3, 3);
        sourceModel->setItem(0, 0, new QStandardItem("Alice"));
        sourceModel->setItem(1, 0, new QStandardItem("Bob"));
        sourceModel->setItem(2, 0, new QStandardItem("Charlie"));

        sourceModel->setItem(0, 1, new QStandardItem("25"));
        sourceModel->setItem(1, 1, new QStandardItem("30"));
        sourceModel->setItem(2, 1, new QStandardItem("35"));

        sourceModel->setItem(0, 2, new QStandardItem("Engineer"));
        sourceModel->setItem(1, 2, new QStandardItem("Doctor"));
        sourceModel->setItem(2, 2, new QStandardItem("Artist"));

        // Initialize a selection model with the standard item model
        selectionModel = new SelectionModel(sourceModel);
    }

    void TearDown() override {
        delete selectionModel;
        delete sourceModel;
    }

    QStandardItemModel* sourceModel;
    SelectionModel* selectionModel;
};

// Test handleSelectionChanged function
TEST_F(SelectionModelTest, HandleSelectionChangedTest) {
    QItemSelection selection;
    selection.select(sourceModel->index(0, 0), sourceModel->index(0, 2));
    selectionModel->handleSelectionChanged(selection);

    QStringList selectionData = selectionModel->getSelectionData();
    EXPECT_EQ(selectionData.size(), 3);
    EXPECT_EQ(selectionData[0], "Alice");
    EXPECT_EQ(selectionData[1], "25");
    EXPECT_EQ(selectionData[2], "Engineer");
}

// Test getSelectionData function
TEST_F(SelectionModelTest, GetSelectionDataTest) {
    QItemSelection selection;
    selection.select(sourceModel->index(1, 0), sourceModel->index(1, 2));
    selectionModel->handleSelectionChanged(selection);

    QStringList selectionData = selectionModel->getSelectionData();
    EXPECT_EQ(selectionData.size(), 3);
    EXPECT_EQ(selectionData[0], "Bob");
    EXPECT_EQ(selectionData[1], "30");
    EXPECT_EQ(selectionData[2], "Doctor");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
