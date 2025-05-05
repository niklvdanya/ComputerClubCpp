#include <gtest/gtest.h>
#include "models/time.h"

using namespace computer_club::models;

TEST(TimeTest, BasicOperations) {
    Time time1;
    EXPECT_EQ("00:00", time1.toString());
    
    Time time2(12, 30);
    EXPECT_EQ("12:30", time2.toString());
    
    Time time3 = Time::parse("14:45");
    EXPECT_EQ("14:45", time3.toString());
    
    EXPECT_TRUE(time1 < time2);
    EXPECT_TRUE(time2 < time3);
    EXPECT_FALSE(time3 < time2);
    
    EXPECT_EQ(135, time3.diffInMinutes(time2));
    
    Time time4 = time2.addMinutes(45);
    EXPECT_EQ("13:15", time4.toString());
}

TEST(TimeTest, InvalidInput) {
    EXPECT_THROW(Time::parse("14:"), std::runtime_error);
    EXPECT_THROW(Time::parse("24:00"), std::runtime_error);
    EXPECT_THROW(Time::parse("12:60"), std::runtime_error);
}