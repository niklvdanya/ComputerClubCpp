#pragma once

#include "models/club_configuration.h"
#include "models/event.h"
#include "services/billing_service.h"
#include "services/client_manager.h"
#include "services/event_manager.h"
#include "services/queue_manager.h"
#include "services/table_manager.h"
#include <memory>
#include <string>
#include <vector>

namespace computer_club {
namespace controllers {

class ComputerClubController {
public:
    explicit ComputerClubController(const models::ClubConfiguration& config);
    
    void processEvents(const std::vector<models::Event>& inputEvents);
    void processEvent(const models::Event& event);
    void closeClub();
    
    std::vector<models::Event> getEvents() const;
    models::ClubConfiguration getConfiguration() const;
    std::vector<std::shared_ptr<models::Table>> getTables() const;
    
private:
    models::ClubConfiguration config_;
    std::unique_ptr<services::EventManager> eventManager_;
    std::unique_ptr<services::ClientManager> clientManager_;
    std::unique_ptr<services::TableManager> tableManager_;
    std::unique_ptr<services::QueueManager> queueManager_;
    std::unique_ptr<services::BillingService> billingService_;
    
    bool isOpenAt(const models::Time& time) const;
    void handleClientArrival(const models::Event& event);
    void handleClientSitting(const models::Event& event);
    void handleClientWaiting(const models::Event& event);
    void handleClientLeaving(const models::Event& event);
    
    void addErrorEvent(const models::Time& time, const std::string& errorMessage);
    void assignTableToNextClient(const models::Time& time, int tableNumber);
};

} // namespace controllers
} // namespace computer_club