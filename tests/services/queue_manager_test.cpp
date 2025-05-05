#include "services/queue_manager.h"
#include <gtest/gtest.h>

using namespace computer_club::services;

TEST(QueueManagerTest, BasicOperations)
{
    QueueManager queueManager;

    EXPECT_TRUE(queueManager.isQueueEmpty());
    EXPECT_EQ(0, queueManager.getQueueSize());

    queueManager.addToQueue("Client1");
    EXPECT_FALSE(queueManager.isQueueEmpty());
    EXPECT_EQ(1, queueManager.getQueueSize());

    queueManager.addToQueue("Client2");
    EXPECT_EQ(2, queueManager.getQueueSize());

    EXPECT_EQ("Client1", queueManager.getNextInQueue());
    EXPECT_EQ(1, queueManager.getQueueSize());

    EXPECT_EQ("Client2", queueManager.getNextInQueue());
    EXPECT_TRUE(queueManager.isQueueEmpty());

    EXPECT_EQ("", queueManager.getNextInQueue());
}