#pragma once

#include <string>
#include "models/table.h"
#include "models/time.h"

namespace computer_club
{
    namespace services
    {

        class BillingService
        {
        public:
            explicit BillingService(int hourlyRate) noexcept;

            int calculateCharge(int minutes) const noexcept;
            std::string formatOccupationTime(int minutes) const;

        private:
            int hourlyRate_;
        };

    }  // namespace services
}  // namespace computer_club