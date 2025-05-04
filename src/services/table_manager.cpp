#include "services/table_manager.h"
#include "utils/exceptions.h"

namespace computer_club {
namespace services {

TableManager::TableManager(int tableCount) : tableCount_(tableCount) {
    for (int i = 1; i <= tableCount; ++i) {
        tables_[i] = std::make_shared<models::Table>(i);
    }
}

int TableManager::getTableCount() const {
    return tableCount_;
}

bool TableManager::isTableOccupied(int tableNumber) const {
    auto it = tables_.find(tableNumber);
    if (it != tables_.end()) {
        return it->second->isOccupied();
    }
    return false;
}

std::shared_ptr<models::Table> TableManager::getTable(int tableNumber) {
    auto it = tables_.find(tableNumber);
    if (it != tables_.end()) {
        return it->second;
    }
    return nullptr;
}

void TableManager::occupyTable(int tableNumber, const std::string& clientName, const models::Time& time) {
    auto table = getTable(tableNumber);
    if (table) {
        table->occupy(clientName, time);
    }
}

void TableManager::releaseTable(int tableNumber, const models::Time& time, int hourlyRate) {
    auto table = getTable(tableNumber);
    if (table) {
        table->release(time, hourlyRate);
    }
}

int TableManager::getAvailableTableCount() const {
    int count = 0;
    for (const auto& pair : tables_) {
        if (!pair.second->isOccupied()) {
            ++count;
        }
    }
    return count;
}

std::vector<std::shared_ptr<models::Table>> TableManager::getAllTables() const {
    std::vector<std::shared_ptr<models::Table>> result;
    for (const auto& pair : tables_) {
        result.push_back(pair.second);
    }
    return result;
}

} // namespace services
} // namespace computer_club