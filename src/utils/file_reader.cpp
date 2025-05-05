#include "utils/file_reader.h"
#include <fstream>
#include <sstream>
#include "utils/exceptions.h"

namespace computer_club
{
    namespace utils
    {

        FileReader::FileReader(const std::string& filename) : filename_(filename), currentLine_(0)
        {
        }

        models::ClubConfiguration FileReader::readConfiguration()
        {
            std::ifstream file(filename_);
            if (!file.is_open())
            {
                throw FileReadException("Could not open file: " + filename_, 0);
            }

            std::string line;

            if (!std::getline(file, line))
            {
                throw FileReadException("Failed to read table count", ++currentLine_);
            }

            int tableCount = validateAndParseInteger(line, "Invalid table count");

            if (!std::getline(file, line))
            {
                throw FileReadException("Failed to read working hours", ++currentLine_);
            }

            std::istringstream iss(line);
            std::string openTimeStr, closeTimeStr;

            if (!(iss >> openTimeStr >> closeTimeStr))
            {
                throw FileReadException("Invalid working hours format", currentLine_);
            }

            models::Time openTime = validateAndParseTime(openTimeStr);
            models::Time closeTime = validateAndParseTime(closeTimeStr);

            if (closeTime <= openTime)
            {
                throw FileReadException("Close time must be after open time", currentLine_);
            }

            if (!std::getline(file, line))
            {
                throw FileReadException("Failed to read hourly rate", ++currentLine_);
            }

            int hourlyRate = validateAndParseInteger(line, "Invalid hourly rate");

            return models::ClubConfiguration(tableCount, openTime, closeTime, hourlyRate);
        }

        std::vector<models::Event> FileReader::readEvents()
        {
            std::ifstream file(filename_);
            if (!file.is_open())
            {
                throw FileReadException("Could not open file: " + filename_, 0);
            }

            std::string line;

            for (int i = 0; i < 3; ++i)
            {
                if (!std::getline(file, line))
                {
                    throw FileReadException("Failed to skip configuration lines", ++currentLine_);
                }
            }

            std::vector<models::Event> events;
            models::Time lastEventTime;

            while (std::getline(file, line))
            {
                currentLine_++;
                if (line.empty())
                {
                    continue;
                }

                std::istringstream eventStream(line);
                std::string timeStr;
                int eventId;
                std::string clientName;

                if (!(eventStream >> timeStr >> eventId))
                {
                    throw FileReadException("Invalid event format", currentLine_);
                }

                models::Time eventTime = validateAndParseTime(timeStr);

                if (eventTime < lastEventTime)
                {
                    throw FileReadException("Events must be in chronological order", currentLine_);
                }

                lastEventTime = eventTime;

                switch (eventId)
                {
                    case 1:
                    {
                        if (!(eventStream >> clientName))
                        {
                            throw FileReadException(
                                "Missing client name for event 1", currentLine_);
                        }
                        events.emplace_back(
                            eventTime, models::EventType::CLIENT_ARRIVED, clientName);
                        break;
                    }
                    case 2:
                    {
                        int tableNumber;
                        if (!(eventStream >> clientName >> tableNumber))
                        {
                            throw FileReadException("Invalid format for event 2", currentLine_);
                        }
                        events.emplace_back(
                            eventTime, models::EventType::CLIENT_SAT, clientName, tableNumber);
                        break;
                    }
                    case 3:
                    {
                        if (!(eventStream >> clientName))
                        {
                            throw FileReadException(
                                "Missing client name for event 3", currentLine_);
                        }
                        events.emplace_back(
                            eventTime, models::EventType::CLIENT_WAITING, clientName);
                        break;
                    }
                    case 4:
                    {
                        if (!(eventStream >> clientName))
                        {
                            throw FileReadException(
                                "Missing client name for event 4", currentLine_);
                        }
                        events.emplace_back(eventTime, models::EventType::CLIENT_LEFT, clientName);
                        break;
                    }
                    default:
                        throw FileReadException("Unknown event ID", currentLine_);
                }
            }

            return events;
        }

        models::Time FileReader::validateAndParseTime(const std::string& timeStr)
        {
            try
            {
                return models::Time::parse(timeStr);
            }
            catch (const std::exception& e)
            {
                throw FileReadException(e.what(), currentLine_);
            }
        }

        int FileReader::validateAndParseInteger(
            const std::string& intStr, const std::string& errorMessage)
        {
            try
            {
                int value = std::stoi(intStr);
                if (value <= 0)
                {
                    throw FileReadException(errorMessage, currentLine_);
                }
                return value;
            }
            catch (const std::exception&)
            {
                throw FileReadException(errorMessage, currentLine_);
            }
        }

    }  // namespace utils
}  // namespace computer_club