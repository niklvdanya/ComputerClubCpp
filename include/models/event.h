#pragma once

#include "models/time.h"
#include <string>

namespace computer_club {
namespace models {

enum class EventType {
    CLIENT_ARRIVED = 1,
    CLIENT_SAT = 2,
    CLIENT_WAITING = 3,
    CLIENT_LEFT = 4,
    CLIENT_LEFT_END = 11,
    CLIENT_SAT_FROM_QUEUE = 12,
    ERROR = 13
};

class Event {
public:
    Event(const Time& time, EventType type, const std::string& clientName, int tableNumber = 0, const std::string& error = "");
    Event(const Time& time, EventType type, std::string&& clientName, int tableNumber = 0, std::string&& error = "") noexcept;
    
    Time getTime() const noexcept;
    EventType getType() const noexcept;
    std::string getClientName() const noexcept;
    int getTableNumber() const noexcept;
    std::string getError() const noexcept;
    
    std::string toString() const;
    int getEventIdFromType() const noexcept;
    
private:
    Time time_;
    EventType type_;
    std::string clientName_;
    int tableNumber_;
    std::string error_;
};

} // namespace models
} // namespace computer_club