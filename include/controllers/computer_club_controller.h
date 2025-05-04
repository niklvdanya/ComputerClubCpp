#pragma once

#include "controllers/i_computer_club_controller.h"
#include "models/club_configuration.h"
#include "services/billing_service.h"
#include "services/client_manager.h"
#include "services/event_manager.h"
#include "services/queue_manager.h"
#include "services/table_manager.h"
#include <memory>

namespace computer_club {
namespace controllers {

class ComputerClubController : public IComputerClubController {
public:
    explicit ComputerClubController(const models::ClubConfiguration& config);
    ~ComputerClubController() override = default;

    ComputerClubController(const ComputerClubController&) = delete;
    ComputerClubController& operator=(const ComputerClubController&) = delete;
    ComputerClubController(ComputerClubController&&) = default;
    ComputerClubController& operator=(ComputerClubController&&) = default;
    
    void processEvents(const std::vector<models::Event>& inputEvents) override;
    void processEvent(const models::Event& event) override;
    void closeClub() override;
    
    std::vector<models::Event> getEvents() const override;
    models::ClubConfiguration getConfiguration() const override;
    std::vector<std::shared_ptr<models::Table>> getTables() const override;
    
private:
    models::ClubConfiguration config_;
    std::unique_ptr<services::EventManager> eventManager_;
    std::unique_ptr<services::ClientManager> clientManager_;
    std::unique_ptr<services::TableManager> tableManager_;
    std::unique_ptr<services::QueueManager> queueManager_;
    std::unique_ptr<services::BillingService> billingService_;
    
    bool isOpenAt(const models::Time& time) const noexcept;
    void handleClientArrival(const models::Event& event);
    void handleClientSitting(const models::Event& event);
    void handleClientWaiting(const models::Event& event);
    void handleClientLeaving(const models::Event& event);
    
    void addErrorEvent(const models::Time& time, const std::string& errorMessage);
    void assignTableToNextClient(const models::Time& time, int tableNumber);
};

} // namespace controllers
} // namespace computer_club