#include "utils/exceptions.h"
#include <sstream>

namespace computer_club
{
    namespace utils
    {

        ClubException::ClubException(const std::string& message) : std::runtime_error(message) {}

        InvalidTimeFormatException::InvalidTimeFormatException()
            : ClubException("Invalid time format")
        {
        }

        InvalidConfigurationException::InvalidConfigurationException(const std::string& message)
            : ClubException(message)
        {
        }

        ClientException::ClientException(const std::string& message) : ClubException(message) {}

        InvalidEventException::InvalidEventException(const std::string& message)
            : ClubException(message)
        {
        }

        FileReadException::FileReadException(const std::string& message, int lineNumber)
            : ClubException(message), lineNumber_(lineNumber)
        {
        }

        int FileReadException::getLineNumber() const
        {
            return lineNumber_;
        }

    }  // namespace utils
}  // namespace computer_club