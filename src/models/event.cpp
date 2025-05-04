#include "models/event.h"
#include <sstream>

namespace computer_club {
namespace models {

Event::Event(const Time& time, EventType type, const std::string& clientName, int tableNumber, const std::string& error)
    : time_(time), type_(type), clientName_(clientName), tableNumber_(tableNumber), error_(error) {}

Time Event::getTime() const {
    return time_;
}

EventType Event::getType() const {
    return type_;
}

std::string Event::getClientName() const {
    return clientName_;
}

int Event::getTableNumber() const {
    return tableNumber_;
}

std::string Event::getError() const {
    return error_;
}

int Event::getEventIdFromType() const {
    return static_cast<int>(type_);
}

std::string Event::toString() const {
    std::ostringstream oss;
    oss << time_.toString() << " " << getEventIdFromType() << " " << clientName_;
    
    if (tableNumber_ > 0) {
        oss << " " << tableNumber_;
    } else if (!error_.empty()) {
        oss << " " << error_;
    }
    
    return oss.str();
}

} // namespace models
} // namespace computer_club