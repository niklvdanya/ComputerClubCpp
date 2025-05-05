#include <gtest/gtest.h>
#include "services/table_manager.h"
#include "models/time.h"

using namespace computer_club::services;
using namespace computer_club::models;

TEST(TableManagerTest, InitializationAndCounts) {
    TableManager tableManager(5);
    
    EXPECT_EQ(5, tableManager.getTableCount());
    EXPECT_EQ(5, tableManager.getAvailableTableCount());
    
    auto tables = tableManager.getAllTables();
    ASSERT_EQ(5, tables.size());
    
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(i + 1, tables[i]->getNumber());
        EXPECT_FALSE(tables[i]->isOccupied());
    }
}

TEST(TableManagerTest, OccupyAndReleaseTable) {
    TableManager tableManager(3);
    Time startTime(10, 0);
    Time endTime(11, 30);
    
    EXPECT_FALSE(tableManager.isTableOccupied(1));
    EXPECT_EQ(3, tableManager.getAvailableTableCount());
    
    tableManager.occupyTable(1, "Client1", startTime);
    EXPECT_TRUE(tableManager.isTableOccupied(1));
    EXPECT_EQ(2, tableManager.getAvailableTableCount());
    
    auto table = tableManager.getTable(1);
    ASSERT_NE(nullptr, table);
    EXPECT_TRUE(table->isOccupied());
    EXPECT_EQ("Client1", table->getClientName());
    
    tableManager.releaseTable(1, endTime, 10);
    EXPECT_FALSE(tableManager.isTableOccupied(1));
    EXPECT_EQ(3, tableManager.getAvailableTableCount());
    EXPECT_EQ(90, table->getTotalMinutes());
    EXPECT_EQ(20, table->getRevenue());
}

TEST(TableManagerTest, MultipleOccupations) {
    TableManager tableManager(2);
    
    tableManager.occupyTable(1, "Client1", Time(9, 0));
    tableManager.occupyTable(2, "Client2", Time(9, 15));
    
    EXPECT_EQ(0, tableManager.getAvailableTableCount());
    
    tableManager.releaseTable(1, Time(10, 0), 5);
    EXPECT_EQ(1, tableManager.getAvailableTableCount());
    
    tableManager.occupyTable(1, "Client3", Time(10, 15));
    EXPECT_EQ(0, tableManager.getAvailableTableCount());
    
    tableManager.releaseTable(1, Time(11, 0), 5);
    tableManager.releaseTable(2, Time(11, 0), 5);
    EXPECT_EQ(2, tableManager.getAvailableTableCount());
}