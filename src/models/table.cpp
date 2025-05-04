#include "models/table.h"

namespace computer_club {
namespace models {

Table::Table(int number)
    : number_(number), occupied_(false), clientName_(""), totalMinutes_(0), revenue_(0) {}

int Table::getNumber() const {
    return number_;
}

bool Table::isOccupied() const {
    return occupied_;
}

std::string Table::getClientName() const {
    return clientName_;
}

Time Table::getOccupiedSince() const {
    return occupiedSince_;
}

int Table::getTotalMinutes() const {
    return totalMinutes_;
}

int Table::getRevenue() const {
    return revenue_;
}

void Table::occupy(const std::string& clientName, const Time& time) {
    clientName_ = clientName;
    occupiedSince_ = time;
    occupied_ = true;
}

void Table::release(const Time& time, int hourlyRate) {
    if (occupied_) {
        int usageMinutes = occupiedSince_.diffInMinutes(time);
        if (usageMinutes < 0) {
            usageMinutes = time.diffInMinutes(occupiedSince_);
        }
        
        totalMinutes_ += usageMinutes;
        
        int hoursUsed = (usageMinutes + 59) / 60;
        revenue_ += hoursUsed * hourlyRate;
        
        occupied_ = false;
        clientName_ = "";
    }
}

} // namespace models
} // namespace computer_club