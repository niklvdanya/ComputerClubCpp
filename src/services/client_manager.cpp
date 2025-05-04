#include "services/client_manager.h"
#include <algorithm>

namespace computer_club {
namespace services {

ClientManager::ClientManager() {}

bool ClientManager::hasClient(const std::string& clientName) const {
    return clients_.find(clientName) != clients_.end();
}

std::shared_ptr<models::Client> ClientManager::getClient(const std::string& clientName) {
    auto it = clients_.find(clientName);
    if (it != clients_.end()) {
        return it->second;
    }
    return nullptr;
}

void ClientManager::addClient(const std::string& clientName) {
    if (!hasClient(clientName)) {
        clients_[clientName] = std::make_shared<models::Client>(clientName);
    }
}

void ClientManager::removeClient(const std::string& clientName) {
    clients_.erase(clientName);
}

std::vector<std::string> ClientManager::getClientNames() const {
    std::vector<std::string> names;
    for (const auto& pair : clients_) {
        names.push_back(pair.first);
    }
    std::sort(names.begin(), names.end());
    return names;
}

} // namespace services
} // namespace computer_club