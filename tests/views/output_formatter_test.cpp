#include "views/output_formatter.h"
#include <gtest/gtest.h>
#include <sstream>
#include "controllers/computer_club_controller.h"
#include "models/club_configuration.h"

using namespace computer_club::views;
using namespace computer_club::controllers;
using namespace computer_club::models;

class OutputFormatterTest : public ::testing::Test
{
protected:
    OutputFormatterTest()
        : config(2, Time(9, 0), Time(19, 0), 10),
          controller(std::make_unique<ComputerClubController>(config))
    {
        Event clientArrival(Time(10, 0), EventType::CLIENT_ARRIVED, "Client1");
        controller->processEvent(clientArrival);

        Event clientSitting(Time(10, 5), EventType::CLIENT_SAT, "Client1", 1);
        controller->processEvent(clientSitting);

        Event clientLeaving(Time(11, 0), EventType::CLIENT_LEFT, "Client1");
        controller->processEvent(clientLeaving);
    }

    ClubConfiguration config;
    std::unique_ptr<ComputerClubController> controller;
};

TEST_F(OutputFormatterTest, PrintResults)
{
    std::ostringstream oss;
    OutputFormatter formatter(*controller);
    formatter.printResults(oss);

    std::string output = oss.str();
    EXPECT_NE(std::string::npos, output.find("09:00"));
    EXPECT_NE(std::string::npos, output.find("10:00 1 Client1"));
    EXPECT_NE(std::string::npos, output.find("10:05 2 Client1 1"));
    EXPECT_NE(std::string::npos, output.find("11:00 4 Client1"));
    EXPECT_NE(std::string::npos, output.find("19:00"));
    EXPECT_NE(std::string::npos, output.find("1 10"));
    EXPECT_NE(std::string::npos, output.find("2 0"));
}

TEST_F(OutputFormatterTest, PrintResultsAfterCloseClub)
{
    controller->closeClub();

    std::ostringstream oss;
    OutputFormatter formatter(*controller);
    formatter.printResults(oss);

    std::string output = oss.str();

    EXPECT_NE(std::string::npos, output.find("19:00"));
    EXPECT_NE(std::string::npos, output.find("Client1"));
    EXPECT_NE(std::string::npos, output.find("11"));
}