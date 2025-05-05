#pragma once

#include <map>
#include <memory>
#include <vector>
#include "models/table.h"

namespace computer_club
{
    namespace services
    {

        class TableManager
        {
        public:
            explicit TableManager(int tableCount);

            int getTableCount() const noexcept;
            bool isTableOccupied(int tableNumber) const noexcept;
            std::shared_ptr<models::Table> getTable(int tableNumber);

            void occupyTable(
                int tableNumber, const std::string& clientName, const models::Time& time);
            void releaseTable(int tableNumber, const models::Time& time, int hourlyRate) noexcept;

            int getAvailableTableCount() const noexcept;
            std::vector<std::shared_ptr<models::Table>> getAllTables() const;

        private:
            int tableCount_;
            std::map<int, std::shared_ptr<models::Table>> tables_;
        };

    }  // namespace services
}  // namespace computer_club