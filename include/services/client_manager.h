#pragma once

#include "models/client.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace computer_club {
namespace services {

class ClientManager {
public:
    ClientManager() = default;
    
    bool hasClient(const std::string& clientName) const noexcept;
    std::shared_ptr<models::Client> getClient(const std::string& clientName);
    void addClient(const std::string& clientName);
    void removeClient(const std::string& clientName) noexcept;
    
    std::vector<std::string> getClientNames() const;
    
private:
    std::map<std::string, std::shared_ptr<models::Client>> clients_;
};

} // namespace services
} // namespace computer_club