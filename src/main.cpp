#include "controllers/computer_club_controller.h"
#include "utils/file_reader.h"
#include "views/output_formatter.h"
#include "utils/exceptions.h"
#include <iostream>

using namespace computer_club;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    
    try {
        utils::FileReader fileReader(argv[1]);
        
        models::ClubConfiguration config = fileReader.readConfiguration();
        std::vector<models::Event> inputEvents = fileReader.readEvents();
        
        controllers::ComputerClubController controller(config);
        controller.processEvents(inputEvents);
        controller.closeClub();
        
        views::OutputFormatter formatter(controller);
        formatter.printResults(std::cout);
        
        return 0;
    } catch (const utils::FileReadException& e) {
        std::cerr << "Error in line " << e.getLineNumber() << ": " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}