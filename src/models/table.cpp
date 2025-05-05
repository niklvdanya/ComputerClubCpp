#include "models/table.h"

namespace computer_club
{
    namespace models
    {

        Table::Table(int number) noexcept
            : number_(number), occupied_(false), clientName_(""), totalMinutes_(0), revenue_(0)
        {
        }

        int Table::getNumber() const noexcept
        {
            return number_;
        }

        bool Table::isOccupied() const noexcept
        {
            return occupied_;
        }

        std::string Table::getClientName() const noexcept
        {
            return clientName_;
        }

        Time Table::getOccupiedSince() const noexcept
        {
            return occupiedSince_;
        }

        int Table::getTotalMinutes() const noexcept
        {
            return totalMinutes_;
        }

        int Table::getRevenue() const noexcept
        {
            return revenue_;
        }

        void Table::occupy(const std::string& clientName, const Time& time)
        {
            clientName_ = clientName;
            occupiedSince_ = time;
            occupied_ = true;
        }

        void Table::occupy(std::string&& clientName, const Time& time) noexcept
        {
            clientName_ = std::move(clientName);
            occupiedSince_ = time;
            occupied_ = true;
        }

        void Table::release(const Time& time, int hourlyRate) noexcept
        {
            if (occupied_)
            {
                int usageMinutes = occupiedSince_.diffInMinutes(time);
                if (usageMinutes < 0)
                {
                    usageMinutes = time.diffInMinutes(occupiedSince_);
                }

                totalMinutes_ += usageMinutes;

                int hoursUsed = (usageMinutes + 59) / 60;
                revenue_ += hoursUsed * hourlyRate;

                occupied_ = false;
                clientName_ = "";
            }
        }

    }  // namespace models
}  // namespace computer_club