#include "models/club_configuration.h"

namespace computer_club {
namespace models {

ClubConfiguration::ClubConfiguration(int tableCount, const Time& openTime, const Time& closeTime, int hourlyRate)
    : tableCount_(tableCount), openTime_(openTime), closeTime_(closeTime), hourlyRate_(hourlyRate) {}

int ClubConfiguration::getTableCount() const {
    return tableCount_;
}

Time ClubConfiguration::getOpenTime() const {
    return openTime_;
}

Time ClubConfiguration::getCloseTime() const {
    return closeTime_;
}

int ClubConfiguration::getHourlyRate() const {
    return hourlyRate_;
}

} // namespace models
} // namespace computer_club