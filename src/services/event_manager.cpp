#include "services/event_manager.h"

namespace computer_club
{
    namespace services
    {

        void EventManager::addEvent(const models::Event& event)
        {
            events_.push_back(event);
        }

        const std::vector<models::Event>& EventManager::getEvents() const noexcept
        {
            return events_;
        }

    }  // namespace services
}  // namespace computer_club