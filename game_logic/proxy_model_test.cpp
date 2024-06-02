#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "proxy_model.h"
#include "proxy_model.cpp"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QStandardItem>

using ::testing::Return;
using ::testing::NiceMock;

class MockSqlTableModel : public QSqlTableModel {
    Q_OBJECT
public:
    MockSqlTableModel(QObject* parent = nullptr) : QSqlTableModel(parent) {}
    MOCK_METHOD(QVariant, data, (const QModelIndex &index, int role), (const, override));
};

class ProxyModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a mock source model
        mockModel = new NiceMock<MockSqlTableModel>();
        // Initialize ProxyModel with the mock source model
        proxyModel = new ProxyModel(mockModel);

        // Populate the mock model with test data
        QStandardItemModel* testModel = new QStandardItemModel(3, 3);
        testModel->setItem(0, 0, new QStandardItem("Alice"));
        testModel->setItem(1, 0, new QStandardItem("Bob"));
        testModel->setItem(2, 0, new QStandardItem("Charlie"));

        testModel->setItem(0, 1, new QStandardItem("25"));
        testModel->setItem(1, 1, new QStandardItem("30"));
        testModel->setItem(2, 1, new QStandardItem("35"));

        testModel->setItem(0, 2, new QStandardItem("Engineer"));
        testModel->setItem(1, 2, new QStandardItem("Doctor"));
        testModel->setItem(2, 2, new QStandardItem("Artist"));

        // Set the mock model data to return data from the test model
        ON_CALL(*mockModel, data(::testing::_)).WillByDefault([testModel](const QModelIndex &index) {
            return testModel->data(index);
        });

        proxyModel->setSourceModel(testModel);
    }

    void TearDown() override {
        delete proxyModel;
        delete mockModel;
    }

    ProxyModel* proxyModel;
    NiceMock<MockSqlTableModel>* mockModel;
};

// Test setFilter function
TEST_F(ProxyModelTest, SetFilterTest) {
    proxyModel->setFilter(0, "Alice", 0);
    ASSERT_EQ(proxyModel->rowCount(), 1);
    EXPECT_EQ(proxyModel->data(proxyModel->index(0, 0)).toString(), "Alice");
}

// Test clearFilter function
TEST_F(ProxyModelTest, ClearFilterTest) {
    proxyModel->setFilter(0, "Alice", 0);
    proxyModel->clearFilter(0);
    ASSERT_EQ(proxyModel->rowCount(), 3);
}

// Test clearAllFilters function
TEST_F(ProxyModelTest, ClearAllFiltersTest) {
    proxyModel->setFilter(0, "Alice", 0);
    proxyModel->setFilter(1, "30", 0);
    proxyModel->clearAllFilters();
    ASSERT_EQ(proxyModel->rowCount(), 3);
}

// Test setSortOrder function
TEST_F(ProxyModelTest, SetSortOrderTest) {
    proxyModel->setSortOrder(1, Qt::AscendingOrder);
    EXPECT_EQ(proxyModel->data(proxyModel->index(0, 0)).toString(), "Alice");
    EXPECT_EQ(proxyModel->data(proxyModel->index(1, 0)).toString(), "Bob");
    EXPECT_EQ(proxyModel->data(proxyModel->index(2, 0)).toString(), "Charlie");
}

// Test getSourceModel function
TEST_F(ProxyModelTest, GetSourceModelTest) {
    EXPECT_EQ(proxyModel->getSourceModel(), mockModel);
}

// Test getSelectionData function
TEST_F(ProxyModelTest, GetSelectionDataTest) {
    SelectionModel selectionModel;
    proxyModel->setSelectionModel(&selectionModel);
    selectionModel.select(QModelIndex());
    QStringList data = proxyModel->getSelectionData();
    EXPECT_EQ(data.size(), 0);
}

// Test checkCount function
TEST_F(ProxyModelTest, CheckCountTest) {
    QStringList data;
    data << "Alice" << "Bob";
    EXPECT_TRUE(proxyModel->checkCount(data, 2));
    EXPECT_FALSE(proxyModel->checkCount(data, 3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
