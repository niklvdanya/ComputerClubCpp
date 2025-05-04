#pragma once

#include "models/time.h"

namespace computer_club {
namespace models {

class ClubConfiguration {
public:
    ClubConfiguration(int tableCount, const Time& openTime, const Time& closeTime, int hourlyRate);
    
    int getTableCount() const;
    Time getOpenTime() const;
    Time getCloseTime() const;
    int getHourlyRate() const;
    
private:
    int tableCount_;
    Time openTime_;
    Time closeTime_;
    int hourlyRate_;
};

} // namespace models
} // namespace computer_club
