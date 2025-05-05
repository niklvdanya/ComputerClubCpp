#pragma once

#include <string>

namespace computer_club
{
    namespace models
    {

        class Client
        {
        public:
            explicit Client(const std::string& name);
            explicit Client(std::string&& name) noexcept;

            std::string getName() const noexcept;
            bool isSeated() const noexcept;
            int getTableNumber() const noexcept;
            bool isWaiting() const noexcept;

            void setTable(int tableNumber);
            void clearTable() noexcept;
            void setWaiting(bool waiting) noexcept;

        private:
            std::string name_;
            bool seated_;
            int tableNumber_;
            bool waiting_;
        };

    }  // namespace models
}  // namespace computer_club