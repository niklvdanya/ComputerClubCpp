#pragma once

#include <string>

namespace computer_club {
namespace models {

class Client {
public:
    explicit Client(const std::string& name);
    
    std::string getName() const;
    bool isSeated() const;
    int getTableNumber() const;
    bool isWaiting() const;
    
    void setTable(int tableNumber);
    void clearTable();
    void setWaiting(bool waiting);
    
private:
    std::string name_;
    bool seated_;
    int tableNumber_;
    bool waiting_;
};

} // namespace models
} // namespace computer_club