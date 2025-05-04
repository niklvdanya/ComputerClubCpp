#pragma once

#include "models/club_configuration.h"
#include "models/event.h"
#include <string>
#include <vector>

namespace computer_club {
namespace utils {

class FileReader {
public:
    explicit FileReader(const std::string& filename);
    
    models::ClubConfiguration readConfiguration();
    std::vector<models::Event> readEvents();
    
private:
    std::string filename_;
    int currentLine_;
    
    models::Time validateAndParseTime(const std::string& timeStr);
    int validateAndParseInteger(const std::string& intStr, const std::string& errorMessage);
};

} // namespace utils
} // namespace computer_club