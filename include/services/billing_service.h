#pragma once

#include "models/table.h"
#include "models/time.h"
#include <string>

namespace computer_club {
namespace services {

class BillingService {
public:
    explicit BillingService(int hourlyRate);
    
    int calculateCharge(int minutes) const;
    std::string formatOccupationTime(int minutes) const;
    
private:
    int hourlyRate_;
};

} // namespace services
} // namespace computer_club
