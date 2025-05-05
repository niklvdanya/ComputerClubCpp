#pragma once

#include <vector>
#include "models/event.h"

namespace computer_club
{
    namespace services
    {

        class EventManager
        {
        public:
            EventManager() = default;

            void addEvent(const models::Event& event);
            const std::vector<models::Event>& getEvents() const noexcept;

        private:
            std::vector<models::Event> events_;
        };

    }  // namespace services
}  // namespace computer_club