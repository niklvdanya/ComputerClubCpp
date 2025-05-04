#pragma once

#include "controllers/computer_club_controller.h"
#include <ostream>

namespace computer_club {
namespace views {

class OutputFormatter {
public:
    explicit OutputFormatter(const controllers::ComputerClubController& controller);
    
    void printResults(std::ostream& out) const;
    
private:
    const controllers::ComputerClubController& controller_;
};

} // namespace views
} // namespace computer_club
