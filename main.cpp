#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <sstream>

struct Time {
    int hours;
    int minutes;
    
    Time(int h = 0, int m = 0) : hours(h), minutes(m) {}
    
    static Time parse(const std::string& timeStr) {
        Time time;
        if (timeStr.size() != 5 || timeStr[2] != ':') {
            throw std::runtime_error("Invalid time format");
        }
        
        try {
            time.hours = std::stoi(timeStr.substr(0, 2));
            time.minutes = std::stoi(timeStr.substr(3, 2));
            
            if (time.hours < 0 || time.hours > 23 || time.minutes < 0 || time.minutes > 59) {
                throw std::runtime_error("Invalid time range");
            }
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid time format");
        }
        
        return time;
    }
    
    std::string toString() const {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << hours << ":" 
            << std::setfill('0') << std::setw(2) << minutes;
        return oss.str();
    }
    
    bool operator<(const Time& other) const {
        if (hours != other.hours) {
            return hours < other.hours;
        }
        return minutes < other.minutes;
    }
    
    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes;
    }
    
    bool operator<=(const Time& other) const {
        return *this < other || *this == other;
    }
    
    bool operator>=(const Time& other) const {
        return !(*this < other);
    }
    
    int diffInMinutes(const Time& other) const {
        return (hours - other.hours) * 60 + (minutes - other.minutes);
    }
    
    Time addMinutes(int mins) const {
        Time newTime = *this;
        newTime.minutes += mins;
        while (newTime.minutes >= 60) {
            newTime.minutes -= 60;
            newTime.hours++;
        }
        return newTime;
    }
};

struct Event {
    Time time;
    int id;
    std::string client;
    int table;
    std::string error;
    
    Event(const Time& t, int eventId, const std::string& cl, int tb = 0, const std::string& err = "")
        : time(t), id(eventId), client(cl), table(tb), error(err) {}
    
    std::string toString() const {
        std::ostringstream oss;
        oss << time.toString() << " " << id << " " << client;
        if (table > 0) {
            oss << " " << table;
        } else if (!error.empty()) {
            oss << " " << error;
        }
        return oss.str();
    }
};

class ComputerClub {
private:
    int tableCount;
    Time openTime;
    Time closeTime;
    int hourlyRate;
    
    std::map<std::string, bool> clientsInClub;
    std::map<int, std::string> occupiedTables;
    std::map<std::string, int> clientTables;
    std::queue<std::string> waitingQueue;
    
    std::map<int, Time> tableOccupiedSince;
    std::map<int, int> tableTotalMinutes;
    std::map<int, int> tableRevenue;
    
    std::vector<Event> events;
    
public:
    ComputerClub(int tables, const Time& open, const Time& close, int rate)
        : tableCount(tables), openTime(open), closeTime(close), hourlyRate(rate) {
        
        for (int i = 1; i <= tableCount; ++i) {
            tableTotalMinutes[i] = 0;
            tableRevenue[i] = 0;
        }
    }
    
    bool isOpenAt(const Time& time) const {
        return time >= openTime && time <= closeTime;
    }
    
    void clientArrived(const Time& time, const std::string& clientName) {
        if (!isOpenAt(time)) {
            addErrorEvent(time, "NotOpenYet");
            return;
        }
        
        if (clientsInClub.find(clientName) != clientsInClub.end()) {
            addErrorEvent(time, "YouShallNotPass");
            return;
        }
        
        clientsInClub[clientName] = true;
        events.push_back(Event(time, 1, clientName));
    }
    
    void clientTakesTable(const Time& time, const std::string& clientName, int tableNumber) {
        if (clientsInClub.find(clientName) == clientsInClub.end()) {
            addErrorEvent(time, "ClientUnknown");
            return;
        }
        
        if (occupiedTables.find(tableNumber) != occupiedTables.end()) {
            if (clientTables.find(clientName) == clientTables.end() || 
                clientTables[clientName] != tableNumber) {
                addErrorEvent(time, "PlaceIsBusy");
                return;
            }
        }
        
        if (clientTables.find(clientName) != clientTables.end()) {
            int oldTable = clientTables[clientName];
            if (oldTable == tableNumber) {
                addErrorEvent(time, "PlaceIsBusy");
                return;
            }
            
            finalizeTableUsage(time, oldTable);
            occupiedTables.erase(oldTable);
        }
        
        occupiedTables[tableNumber] = clientName;
        clientTables[clientName] = tableNumber;
        tableOccupiedSince[tableNumber] = time;
        events.push_back(Event(time, 2, clientName, tableNumber));
    }
    
    void clientWaits(const Time& time, const std::string& clientName) {
        if (clientsInClub.find(clientName) == clientsInClub.end()) {
            addErrorEvent(time, "ClientUnknown");
            return;
        }
        
        if (static_cast<int>(occupiedTables.size()) < tableCount) {
            addErrorEvent(time, "ICanWaitNoLonger!");
            return;
        }
        
        if (clientTables.find(clientName) != clientTables.end()) {
            int oldTable = clientTables[clientName];
            finalizeTableUsage(time, oldTable);
            occupiedTables.erase(oldTable);
            clientTables.erase(clientName);
        }
        
        if (static_cast<int>(waitingQueue.size()) >= tableCount) {
            clientLeft(time, clientName);
            return;
        }
        
        waitingQueue.push(clientName);
        events.push_back(Event(time, 3, clientName));
    }
    
    void clientLeft(const Time& time, const std::string& clientName) {
        if (clientsInClub.find(clientName) == clientsInClub.end()) {
            addErrorEvent(time, "ClientUnknown");
            return;
        }
        
        if (clientTables.find(clientName) != clientTables.end()) {
            int tableNumber = clientTables[clientName];
            finalizeTableUsage(time, tableNumber);
            occupiedTables.erase(tableNumber);
            clientTables.erase(clientName);
            
            assignTableToNextClient(time, tableNumber);
        }
        
        clientsInClub.erase(clientName);
        events.push_back(Event(time, 4, clientName));
    }
    
    void addErrorEvent(const Time& time, const std::string& errorMessage) {
        events.push_back(Event(time, 13, errorMessage));
    }
    
    void assignTableToNextClient(const Time& time, int tableNumber) {
        if (waitingQueue.empty()) {
            return;
        }
        
        std::string nextClient = waitingQueue.front();
        waitingQueue.pop();
        
        if (clientsInClub.find(nextClient) != clientsInClub.end()) {
            occupiedTables[tableNumber] = nextClient;
            clientTables[nextClient] = tableNumber;
            tableOccupiedSince[tableNumber] = time;
            events.push_back(Event(time, 12, nextClient, tableNumber));
        }
    }
    
    void closeClub() {
        std::vector<std::string> remainingClients;
        for (const auto& clientPair : clientsInClub) {
            remainingClients.push_back(clientPair.first);
        }
        
        std::sort(remainingClients.begin(), remainingClients.end());
        
        for (const std::string& client : remainingClients) {
            if (clientTables.find(client) != clientTables.end()) {
                int tableNumber = clientTables[client];
                finalizeTableUsage(closeTime, tableNumber);
            }
            events.push_back(Event(closeTime, 11, client));
        }
    }
    
    void finalizeTableUsage(const Time& endTime, int tableNumber) {
        if (tableOccupiedSince.find(tableNumber) != tableOccupiedSince.end()) {
            Time startTime = tableOccupiedSince[tableNumber];
            
            int usageMinutes = startTime.diffInMinutes(endTime);
            if (usageMinutes < 0) {
                usageMinutes = endTime.diffInMinutes(startTime);
            }
            
            tableTotalMinutes[tableNumber] += usageMinutes;
            
            int hoursUsed = (usageMinutes + 59) / 60;
            tableRevenue[tableNumber] += hoursUsed * hourlyRate;
        }
    }
    
    void printResults(std::ostream& out) const {
        out << openTime.toString() << std::endl;
        
        for (const Event& event : events) {
            out << event.toString() << std::endl;
        }
        
        out << closeTime.toString() << std::endl;
        
        for (int i = 1; i <= tableCount; ++i) {
            int revenue = 0;
            int minutes = 0;
            
            auto revIt = tableRevenue.find(i);
            if (revIt != tableRevenue.end()) {
                revenue = revIt->second;
            }
            
            auto minIt = tableTotalMinutes.find(i);
            if (minIt != tableTotalMinutes.end()) {
                minutes = minIt->second;
            }
            
            int hours = minutes / 60;
            int mins = minutes % 60;
            std::ostringstream timeStr;
            timeStr << std::setfill('0') << std::setw(2) << hours << ":" 
                    << std::setfill('0') << std::setw(2) << mins;
            
            out << i << " " << revenue << " " << timeStr.str() << std::endl;
        }
    }
};

bool processInputFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    
    std::string line;
    int lineNumber = 0;
    
    try {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Failed to read table count");
        }
        lineNumber++;
        int tableCount = std::stoi(line);
        if (tableCount <= 0) {
            throw std::runtime_error("Invalid table count");
        }
        
        if (!std::getline(file, line)) {
            throw std::runtime_error("Failed to read working hours");
        }
        lineNumber++;
        
        std::istringstream iss(line);
        std::string openTimeStr, closeTimeStr;
        if (!(iss >> openTimeStr >> closeTimeStr)) {
            throw std::runtime_error("Invalid working hours format");
        }
        
        Time openTime = Time::parse(openTimeStr);
        Time closeTime = Time::parse(closeTimeStr);
        
        if (closeTime <= openTime) {
            throw std::runtime_error("Close time must be after open time");
        }
        
        if (!std::getline(file, line)) {
            throw std::runtime_error("Failed to read hourly rate");
        }
        lineNumber++;
        
        int hourlyRate = std::stoi(line);
        if (hourlyRate <= 0) {
            throw std::runtime_error("Invalid hourly rate");
        }
        
        ComputerClub club(tableCount, openTime, closeTime, hourlyRate);
        
        Time lastEventTime = Time(0, 0);
        
        while (std::getline(file, line)) {
            lineNumber++;
            if (line.empty()) {
                continue;
            }
            
            std::istringstream eventStream(line);
            std::string timeStr;
            int eventId;
            std::string clientName;
            
            if (!(eventStream >> timeStr >> eventId)) {
                throw std::runtime_error("Invalid event format");
            }
            
            Time eventTime = Time::parse(timeStr);
            
            if (eventTime < lastEventTime) {
                throw std::runtime_error("Events must be in chronological order");
            }
            
            lastEventTime = eventTime;
            
            switch (eventId) {
                case 1:
                    if (!(eventStream >> clientName)) {
                        throw std::runtime_error("Missing client name for event 1");
                    }
                    club.clientArrived(eventTime, clientName);
                    break;
                
                case 2: {
                    int tableNumber;
                    if (!(eventStream >> clientName >> tableNumber)) {
                        throw std::runtime_error("Invalid format for event 2");
                    }
                    if (tableNumber <= 0 || tableNumber > tableCount) {
                        throw std::runtime_error("Invalid table number");
                    }
                    club.clientTakesTable(eventTime, clientName, tableNumber);
                    break;
                }
                
                case 3:
                    if (!(eventStream >> clientName)) {
                        throw std::runtime_error("Missing client name for event 3");
                    }
                    club.clientWaits(eventTime, clientName);
                    break;
                
                case 4:
                    if (!(eventStream >> clientName)) {
                        throw std::runtime_error("Missing client name for event 4");
                    }
                    club.clientLeft(eventTime, clientName);
                    break;
                
                default:
                    throw std::runtime_error("Unknown event ID");
            }
        }
        
        club.closeClub();
        
        club.printResults(std::cout);
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Error in line " << lineNumber << ": " << e.what() << std::endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    if (!processInputFile(argv[1])) {
        return 1;
    }
    
    return 0;
}