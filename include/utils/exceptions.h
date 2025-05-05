#pragma once

#include <stdexcept>
#include <string>

namespace computer_club
{
    namespace utils
    {

        class ClubException : public std::runtime_error
        {
        public:
            explicit ClubException(const std::string& message);
        };

        class InvalidTimeFormatException : public ClubException
        {
        public:
            InvalidTimeFormatException();
        };

        class InvalidConfigurationException : public ClubException
        {
        public:
            explicit InvalidConfigurationException(const std::string& message);
        };

        class ClientException : public ClubException
        {
        public:
            explicit ClientException(const std::string& message);
        };

        class InvalidEventException : public ClubException
        {
        public:
            explicit InvalidEventException(const std::string& message);
        };

        class FileReadException : public ClubException
        {
        public:
            explicit FileReadException(const std::string& message, int lineNumber = 0);

            int getLineNumber() const;

        private:
            int lineNumber_;
        };

    }  // namespace utils
}  // namespace computer_club
