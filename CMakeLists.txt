cmake_minimum_required(VERSION 3.10)
project(computer_club)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES

    src/main.cpp
    
    src/controllers/computer_club_controller.cpp
    src/controllers/computer_club_factory.cpp

    src/models/client.cpp
    src/models/club_configuration.cpp
    src/models/event.cpp
    src/models/table.cpp
    src/models/time.cpp
    
    src/services/billing_service.cpp
    src/services/client_manager.cpp
    src/services/event_manager.cpp
    src/services/queue_manager.cpp
    src/services/table_manager.cpp
    
    src/utils/exceptions.cpp
    src/utils/file_reader.cpp
    
    src/views/output_formatter.cpp
)

add_executable(computer_club ${SOURCES})

