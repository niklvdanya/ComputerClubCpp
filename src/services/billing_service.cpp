#include "services/billing_service.h"
#include <iomanip>
#include <sstream>

namespace computer_club {
namespace services {

BillingService::BillingService(int hourlyRate) : hourlyRate_(hourlyRate) {}

int BillingService::calculateCharge(int minutes) const {
    int hoursUsed = (minutes + 59) / 60;
    return hoursUsed * hourlyRate_;
}

std::string BillingService::formatOccupationTime(int minutes) const {
    int hours = minutes / 60;
    int mins = minutes % 60;
    
    std::ostringstream timeStr;
    timeStr << std::setfill('0') << std::setw(2) << hours << ":" 
            << std::setfill('0') << std::setw(2) << mins;
    
    return timeStr.str();
}

} // namespace services
} // namespace computer_club