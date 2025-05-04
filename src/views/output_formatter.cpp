#include "views/output_formatter.h"

namespace computer_club {
namespace views {

OutputFormatter::OutputFormatter(const controllers::IComputerClubController& controller)
    : controller_(controller) {}
    
void OutputFormatter::printResults(std::ostream& out) const {
    const auto& config = controller_.getConfiguration();
    const auto& events = controller_.getEvents();
    const auto& tables = controller_.getTables();
    
    out << config.getOpenTime().toString() << std::endl;
    
    for (const auto& event : events) {
        out << event.toString() << std::endl;
    }
    
    out << config.getCloseTime().toString() << std::endl;
    
    for (const auto& table : tables) {
        services::BillingService billingService(config.getHourlyRate());
        
        out << table->getNumber() << " " 
            << table->getRevenue() << " " 
            << billingService.formatOccupationTime(table->getTotalMinutes()) << std::endl;
    }
}

} // namespace views
} // namespace computer_club