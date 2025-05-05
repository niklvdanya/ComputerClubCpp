#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "controllers/computer_club_controller.h"
#include "models/club_configuration.h"
#include "models/event.h"

using namespace computer_club::controllers;
using namespace computer_club::models;

class ComputerClubControllerTest : public ::testing::Test {
protected:
    ComputerClubControllerTest() 
        : config(3, Time(9, 0), Time(19, 0), 10),
          controller(std::make_unique<ComputerClubController>(config)) {
    }

    ClubConfiguration config;
    std::unique_ptr<ComputerClubController> controller;
};

TEST_F(ComputerClubControllerTest, ClientArrival) {
    Event clientArrival(Time(10, 0), EventType::CLIENT_ARRIVED, "Client1");
    controller->processEvent(clientArrival);
    
    auto events = controller->getEvents();
    ASSERT_EQ(1, events.size());
    EXPECT_EQ("Client1", events[0].getClientName());
    EXPECT_EQ(EventType::CLIENT_ARRIVED, events[0].getType());
}

TEST_F(ComputerClubControllerTest, ClientArrivalBeforeOpening) {
    Event clientArrival(Time(8, 0), EventType::CLIENT_ARRIVED, "Client1");
    controller->processEvent(clientArrival);
    
    auto events = controller->getEvents();
    ASSERT_EQ(1, events.size());
    EXPECT_EQ(EventType::ERROR, events[0].getType());
    EXPECT_EQ("NotOpenYet", events[0].getClientName());
}

TEST_F(ComputerClubControllerTest, ClientSitting) {
    Event clientArrival(Time(10, 0), EventType::CLIENT_ARRIVED, "Client1");
    controller->processEvent(clientArrival);
    
    Event clientSitting(Time(10, 5), EventType::CLIENT_SAT, "Client1", 1);
    controller->processEvent(clientSitting);
    
    auto events = controller->getEvents();
    ASSERT_EQ(2, events.size());
    EXPECT_EQ(EventType::CLIENT_ARRIVED, events[0].getType());
    EXPECT_EQ(EventType::CLIENT_SAT, events[1].getType());
    EXPECT_EQ(1, events[1].getTableNumber());
}

TEST_F(ComputerClubControllerTest, ClientLeaving) {
    Event clientArrival(Time(10, 0), EventType::CLIENT_ARRIVED, "Client1");
    controller->processEvent(clientArrival);
    
    Event clientSitting(Time(10, 5), EventType::CLIENT_SAT, "Client1", 1);
    controller->processEvent(clientSitting);
    
    Event clientLeaving(Time(11, 0), EventType::CLIENT_LEFT, "Client1");
    controller->processEvent(clientLeaving);
    
    auto events = controller->getEvents();
    ASSERT_EQ(3, events.size());
    EXPECT_EQ(EventType::CLIENT_LEFT, events[2].getType());
    
    auto tables = controller->getTables();
    ASSERT_EQ(3, tables.size());
    EXPECT_FALSE(tables[0]->isOccupied());
    
    EXPECT_EQ(10, tables[0]->getRevenue());
}

TEST_F(ComputerClubControllerTest, CloseClub) {
    Event clientArrival(Time(10, 0), EventType::CLIENT_ARRIVED, "Client1");
    controller->processEvent(clientArrival);
    
    Event clientSitting(Time(10, 5), EventType::CLIENT_SAT, "Client1", 1);
    controller->processEvent(clientSitting);
    
    controller->closeClub();
    
    auto events = controller->getEvents();
    ASSERT_GT(events.size(), 2);
    
    EXPECT_EQ(EventType::CLIENT_LEFT_END, events.back().getType());
    EXPECT_EQ("Client1", events.back().getClientName());
    
    auto tables = controller->getTables();
    for (const auto& table : tables) {
        EXPECT_FALSE(table->isOccupied());
    }
}