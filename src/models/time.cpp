#include "models/time.h"
#include <iomanip>
#include <sstream>

namespace computer_club {
namespace models {

Time::Time() : hours_(0), minutes_(0) {}

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {}

Time Time::parse(const std::string& timeStr) {
    Time time;
    if (timeStr.size() != 5 || timeStr[2] != ':') {
        throw std::runtime_error("Invalid time format");
    }
    
    try {
        time.hours_ = std::stoi(timeStr.substr(0, 2));
        time.minutes_ = std::stoi(timeStr.substr(3, 2));
        
        if (time.hours_ < 0 || time.hours_ > 23 || time.minutes_ < 0 || time.minutes_ > 59) {
            throw std::runtime_error("Invalid time range");
        }
    } catch (const std::exception&) {
        throw std::runtime_error("Invalid time format");
    }
    
    return time;
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours_ << ":" 
        << std::setfill('0') << std::setw(2) << minutes_;
    return oss.str();
}

bool Time::operator<(const Time& other) const {
    if (hours_ != other.hours_) {
        return hours_ < other.hours_;
    }
    return minutes_ < other.minutes_;
}

bool Time::operator==(const Time& other) const {
    return hours_ == other.hours_ && minutes_ == other.minutes_;
}

bool Time::operator<=(const Time& other) const {
    return *this < other || *this == other;
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

int Time::diffInMinutes(const Time& other) const {
    return (hours_ - other.hours_) * 60 + (minutes_ - other.minutes_);
}

Time Time::addMinutes(int mins) const {
    Time newTime = *this;
    newTime.minutes_ += mins;
    
    while (newTime.minutes_ >= 60) {
        newTime.minutes_ -= 60;
        newTime.hours_++;
    }
    
    while (newTime.minutes_ < 0) {
        newTime.minutes_ += 60;
        newTime.hours_--;
    }
    
    return newTime;
}

} // namespace models
} // namespace computer_club