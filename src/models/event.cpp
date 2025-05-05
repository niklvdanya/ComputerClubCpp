#include "models/event.h"
#include <sstream>

namespace computer_club
{
    namespace models
    {

        Event::Event(
            const Time& time,
            EventType type,
            const std::string& clientName,
            int tableNumber,
            const std::string& error)
            : time_(time),
              type_(type),
              clientName_(clientName),
              tableNumber_(tableNumber),
              error_(error)
        {
        }

        Event::Event(
            const Time& time,
            EventType type,
            std::string&& clientName,
            int tableNumber,
            std::string&& error) noexcept
            : time_(time),
              type_(type),
              clientName_(std::move(clientName)),
              tableNumber_(tableNumber),
              error_(std::move(error))
        {
        }

        Time Event::getTime() const noexcept
        {
            return time_;
        }

        EventType Event::getType() const noexcept
        {
            return type_;
        }

        std::string Event::getClientName() const noexcept
        {
            return clientName_;
        }

        int Event::getTableNumber() const noexcept
        {
            return tableNumber_;
        }

        std::string Event::getError() const noexcept
        {
            return error_;
        }

        int Event::getEventIdFromType() const noexcept
        {
            return static_cast<int>(type_);
        }

        std::string Event::toString() const
        {
            std::ostringstream oss;
            oss << time_.toString() << " " << getEventIdFromType() << " " << clientName_;

            if (tableNumber_ > 0)
            {
                oss << " " << tableNumber_;
            }
            else if (!error_.empty())
            {
                oss << " " << error_;
            }

            return oss.str();
        }

    }  // namespace models
}  // namespace computer_club