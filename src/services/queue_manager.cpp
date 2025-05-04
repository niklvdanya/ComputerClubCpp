#include "services/queue_manager.h"

namespace computer_club {
namespace services {

QueueManager::QueueManager() {}

void QueueManager::addToQueue(const std::string& clientName) {
    waitingQueue_.push(clientName);
}

std::string QueueManager::getNextInQueue() {
    if (waitingQueue_.empty()) {
        return "";
    }
    
    std::string next = waitingQueue_.front();
    waitingQueue_.pop();
    return next;
}

bool QueueManager::isQueueEmpty() const {
    return waitingQueue_.empty();
}

int QueueManager::getQueueSize() const {
    return static_cast<int>(waitingQueue_.size());
}

} // namespace services
} // namespace computer_club