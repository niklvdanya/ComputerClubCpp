#pragma once

#include <memory>
#include <vector>
#include "models/club_configuration.h"
#include "models/event.h"
#include "models/table.h"

namespace computer_club
{
    namespace controllers
    {

        class IComputerClubController
        {
        public:
            virtual ~IComputerClubController() = default;

            virtual void processEvents(const std::vector<models::Event>& inputEvents) = 0;
            virtual void processEvent(const models::Event& event) = 0;
            virtual void closeClub() = 0;

            virtual std::vector<models::Event> getEvents() const noexcept = 0;
            virtual models::ClubConfiguration getConfiguration() const noexcept = 0;
            virtual std::vector<std::shared_ptr<models::Table>> getTables() const = 0;
        };

    }  // namespace controllers
}  // namespace computer_club