#include "controllers/computer_club_controller.h"

namespace computer_club
{
    namespace controllers
    {

        ComputerClubController::ComputerClubController(const models::ClubConfiguration& config)
            : config_(config)
        {
            eventManager_ = std::make_unique<services::EventManager>();
            clientManager_ = std::make_unique<services::ClientManager>();
            tableManager_ = std::make_unique<services::TableManager>(config.getTableCount());
            queueManager_ = std::make_unique<services::QueueManager>();
            billingService_ = std::make_unique<services::BillingService>(config.getHourlyRate());
        }

        void ComputerClubController::processEvents(const std::vector<models::Event>& inputEvents)
        {
            for (const auto& event : inputEvents)
            {
                processEvent(event);
            }
        }

        void ComputerClubController::processEvent(const models::Event& event)
        {
            switch (event.getType())
            {
                case models::EventType::CLIENT_ARRIVED:
                    handleClientArrival(event);
                    break;
                case models::EventType::CLIENT_SAT:
                    handleClientSitting(event);
                    break;
                case models::EventType::CLIENT_WAITING:
                    handleClientWaiting(event);
                    break;
                case models::EventType::CLIENT_LEFT:
                    handleClientLeaving(event);
                    break;
                default:
                    eventManager_->addEvent(event);
                    break;
            }
        }

        void ComputerClubController::closeClub()
        {
            std::vector<std::string> remainingClients = clientManager_->getClientNames();

            for (const std::string& clientName : remainingClients)
            {
                auto client = clientManager_->getClient(clientName);
                if (client && client->isSeated())
                {
                    int tableNumber = client->getTableNumber();
                    tableManager_->releaseTable(
                        tableNumber, config_.getCloseTime(), config_.getHourlyRate());
                }

                eventManager_->addEvent(models::Event(
                    config_.getCloseTime(), models::EventType::CLIENT_LEFT_END, clientName));
            }
        }

        std::vector<models::Event> ComputerClubController::getEvents() const noexcept
        {
            return eventManager_->getEvents();
        }

        models::ClubConfiguration ComputerClubController::getConfiguration() const noexcept
        {
            return config_;
        }

        std::vector<std::shared_ptr<models::Table>> ComputerClubController::getTables() const
        {
            return tableManager_->getAllTables();
        }

        bool ComputerClubController::isOpenAt(const models::Time& time) const noexcept
        {
            return time >= config_.getOpenTime() && time <= config_.getCloseTime();
        }

        void ComputerClubController::handleClientArrival(const models::Event& event)
        {
            const auto& time = event.getTime();
            const auto& clientName = event.getClientName();

            if (!isOpenAt(time))
            {
                addErrorEvent(time, "NotOpenYet");
                return;
            }

            if (clientManager_->hasClient(clientName))
            {
                addErrorEvent(time, "YouShallNotPass");
                return;
            }

            clientManager_->addClient(clientName);
            eventManager_->addEvent(event);
        }

        void ComputerClubController::handleClientSitting(const models::Event& event)
        {
            const auto& time = event.getTime();
            const auto& clientName = event.getClientName();
            int tableNumber = event.getTableNumber();

            if (!clientManager_->hasClient(clientName))
            {
                addErrorEvent(time, "ClientUnknown");
                return;
            }

            auto client = clientManager_->getClient(clientName);

            if (tableManager_->isTableOccupied(tableNumber))
            {
                if (client->isSeated() && client->getTableNumber() == tableNumber)
                {
                    addErrorEvent(time, "PlaceIsBusy");
                    return;
                }

                if (client->isSeated() && client->getTableNumber() != tableNumber)
                {
                    int oldTable = client->getTableNumber();
                    tableManager_->releaseTable(oldTable, time, config_.getHourlyRate());
                }
            }

            if (client->isSeated())
            {
                int oldTable = client->getTableNumber();
                if (oldTable == tableNumber)
                {
                    addErrorEvent(time, "PlaceIsBusy");
                    return;
                }

                tableManager_->releaseTable(oldTable, time, config_.getHourlyRate());
            }

            tableManager_->occupyTable(tableNumber, clientName, time);
            client->setTable(tableNumber);
            eventManager_->addEvent(event);
        }

        void ComputerClubController::handleClientWaiting(const models::Event& event)
        {
            const auto& time = event.getTime();
            const auto& clientName = event.getClientName();

            if (!clientManager_->hasClient(clientName))
            {
                addErrorEvent(time, "ClientUnknown");
                return;
            }

            if (tableManager_->getAvailableTableCount() > 0)
            {
                addErrorEvent(time, "ICanWaitNoLonger!");
                return;
            }

            auto client = clientManager_->getClient(clientName);

            if (client->isSeated())
            {
                int oldTable = client->getTableNumber();
                tableManager_->releaseTable(oldTable, time, config_.getHourlyRate());
                client->clearTable();
            }

            if (queueManager_->getQueueSize() >= tableManager_->getTableCount())
            {
                clientManager_->removeClient(clientName);
                eventManager_->addEvent(
                    models::Event(time, models::EventType::CLIENT_LEFT_END, clientName));
                return;
            }

            queueManager_->addToQueue(clientName);
            client->setWaiting(true);
            eventManager_->addEvent(event);
        }

        void ComputerClubController::handleClientLeaving(const models::Event& event)
        {
            const auto& time = event.getTime();
            const auto& clientName = event.getClientName();

            if (!clientManager_->hasClient(clientName))
            {
                addErrorEvent(time, "ClientUnknown");
                return;
            }

            auto client = clientManager_->getClient(clientName);

            if (client->isSeated())
            {
                int tableNumber = client->getTableNumber();
                tableManager_->releaseTable(tableNumber, time, config_.getHourlyRate());
                assignTableToNextClient(time, tableNumber);
            }

            clientManager_->removeClient(clientName);
            eventManager_->addEvent(event);
        }

        void ComputerClubController::addErrorEvent(
            const models::Time& time, const std::string& errorMessage)
        {
            eventManager_->addEvent(models::Event(time, models::EventType::ERROR, errorMessage));
        }

        void ComputerClubController::assignTableToNextClient(
            const models::Time& time, int tableNumber)
        {
            if (queueManager_->isQueueEmpty())
            {
                return;
            }

            std::string nextClientName = queueManager_->getNextInQueue();

            if (clientManager_->hasClient(nextClientName))
            {
                auto nextClient = clientManager_->getClient(nextClientName);
                tableManager_->occupyTable(tableNumber, nextClientName, time);
                nextClient->setTable(tableNumber);
                nextClient->setWaiting(false);

                eventManager_->addEvent(models::Event(
                    time, models::EventType::CLIENT_SAT_FROM_QUEUE, nextClientName, tableNumber));
            }
        }

    }  // namespace controllers
}  // namespace computer_club