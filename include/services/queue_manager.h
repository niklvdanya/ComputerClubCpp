#pragma once

#include <queue>
#include <string>

namespace computer_club {
namespace services {

class QueueManager {
public:
    QueueManager();
    
    void addToQueue(const std::string& clientName);
    std::string getNextInQueue();
    bool isQueueEmpty() const;
    int getQueueSize() const;
    
private:
    std::queue<std::string> waitingQueue_;
};

} // namespace services
} // namespace computer_club
