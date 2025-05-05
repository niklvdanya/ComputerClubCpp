#pragma once

#include "models/event.h"
#include <vector>

namespace computer_club {
namespace services {

class EventManager {
public:
    EventManager() = default;
    
    void addEvent(const models::Event& event);
    const std::vector<models::Event>& getEvents() const noexcept;
    
private:
    std::vector<models::Event> events_;
};

} // namespace services
} // namespace computer_club