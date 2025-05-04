#include "controllers/computer_club_factory.h"
#include "controllers/computer_club_controller.h"

namespace computer_club {
namespace controllers {

std::unique_ptr<IComputerClubController> ComputerClubControllerFactory::create(
        const models::ClubConfiguration& config) {
    return std::make_unique<ComputerClubController>(config);
}

} // namespace controllers
} // namespace computer_club