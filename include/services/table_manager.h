#pragma once

#include "models/table.h"
#include <map>
#include <memory>
#include <vector>

namespace computer_club {
namespace services {

class TableManager {
public:
    explicit TableManager(int tableCount);
    
    int getTableCount() const;
    bool isTableOccupied(int tableNumber) const;
    std::shared_ptr<models::Table> getTable(int tableNumber);
    
    void occupyTable(int tableNumber, const std::string& clientName, const models::Time& time);
    void releaseTable(int tableNumber, const models::Time& time, int hourlyRate);
    
    int getAvailableTableCount() const;
    std::vector<std::shared_ptr<models::Table>> getAllTables() const;
    
private:
    int tableCount_;
    std::map<int, std::shared_ptr<models::Table>> tables_;
};

} // namespace services
} // namespace computer_club
