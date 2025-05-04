#pragma once

#include <string>
#include <stdexcept>

namespace computer_club {
namespace models {

class Time {
public:
    Time();
    Time(int hours, int minutes);
    
    static Time parse(const std::string& timeStr);
    
    std::string toString() const;
    
    bool operator<(const Time& other) const noexcept;
    bool operator==(const Time& other) const noexcept;
    bool operator<=(const Time& other) const noexcept;
    bool operator>=(const Time& other) const noexcept;
    
    int diffInMinutes(const Time& other) const;
    Time addMinutes(int mins) const;
    
private:
    int hours_;
    int minutes_;
};

} // namespace models
} // namespace computer_club
