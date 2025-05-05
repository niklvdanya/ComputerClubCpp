#pragma once

#include <memory>
#include "controllers/i_computer_club_controller.h"
#include "models/club_configuration.h"

namespace computer_club
{
    namespace controllers
    {

        class ComputerClubControllerFactory
        {
        public:
            ComputerClubControllerFactory() = delete;

            static std::unique_ptr<IComputerClubController> create(
                const models::ClubConfiguration& config);
        };

    }  // namespace controllers
}  // namespace computer_club