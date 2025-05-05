#include "models/client.h"

namespace computer_club {
namespace models {

Client::Client(const std::string& name) 
    : name_(name), seated_(false), tableNumber_(0), waiting_(false) {}

Client::Client(std::string&& name) noexcept
    : name_(std::move(name)), seated_(false), tableNumber_(0), waiting_(false) {}

std::string Client::getName() const noexcept {
    return name_;
}

bool Client::isSeated() const noexcept {
    return seated_;
}

int Client::getTableNumber() const noexcept {
    return tableNumber_;
}

bool Client::isWaiting() const noexcept {
    return waiting_;
}

void Client::setTable(int tableNumber) {
    tableNumber_ = tableNumber;
    seated_ = true;
    waiting_ = false;
}

void Client::clearTable() noexcept {
    tableNumber_ = 0;
    seated_ = false;
}

void Client::setWaiting(bool waiting) noexcept {
    waiting_ = waiting;
    if (waiting) {
        clearTable();
    }
}

} // namespace models
} // namespace computer_club