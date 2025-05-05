#pragma once

#include <ostream>
#include "controllers/computer_club_controller.h"

namespace computer_club
{
    namespace views
    {

        class OutputFormatter
        {
        public:
            explicit OutputFormatter(const controllers::IComputerClubController& controller);

            void printResults(std::ostream& out) const;

        private:
            const controllers::IComputerClubController& controller_;
        };

    }  // namespace views
}  // namespace computer_club
