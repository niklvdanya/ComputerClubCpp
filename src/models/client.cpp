#include "models/client.h"

namespace computer_club {
namespace models {

Client::Client(const std::string& name) 
    : name_(name), seated_(false), tableNumber_(0), waiting_(false) {}

std::string Client::getName() const {
    return name_;
}

bool Client::isSeated() const {
    return seated_;
}

int Client::getTableNumber() const {
    return tableNumber_;
}

bool Client::isWaiting() const {
    return waiting_;
}

void Client::setTable(int tableNumber) {
    tableNumber_ = tableNumber;
    seated_ = true;
    waiting_ = false;
}

void Client::clearTable() {
    tableNumber_ = 0;
    seated_ = false;
}

void Client::setWaiting(bool waiting) {
    waiting_ = waiting;
    if (waiting) {
        clearTable();
    }
}

} // namespace models
} // namespace computer_club