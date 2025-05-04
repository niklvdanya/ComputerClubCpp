#pragma once

#include "models/time.h"
#include <string>

namespace computer_club {
namespace models {

class Table {
public:
    explicit Table(int number);
    
    int getNumber() const;
    bool isOccupied() const;
    std::string getClientName() const;
    Time getOccupiedSince() const;
    int getTotalMinutes() const;
    int getRevenue() const;
    
    void occupy(const std::string& clientName, const Time& time);
    void release(const Time& time, int hourlyRate);
    
private:
    int number_;
    bool occupied_;
    std::string clientName_;
    Time occupiedSince_;
    int totalMinutes_;
    int revenue_;
};

} // namespace models
} // namespace computer_club
