#pragma once

#include <string>
#include "models/time.h"

namespace computer_club
{
    namespace models
    {

        class Table
        {
        public:
            explicit Table(int number) noexcept;

            int getNumber() const noexcept;
            bool isOccupied() const noexcept;
            std::string getClientName() const noexcept;
            Time getOccupiedSince() const noexcept;
            int getTotalMinutes() const noexcept;
            int getRevenue() const noexcept;

            void occupy(const std::string& clientName, const Time& time);
            void occupy(std::string&& clientName, const Time& time) noexcept;
            void release(const Time& time, int hourlyRate) noexcept;

        private:
            int number_;
            bool occupied_;
            std::string clientName_;
            Time occupiedSince_;
            int totalMinutes_;
            int revenue_;
        };

    }  // namespace models
}  // namespace computer_club