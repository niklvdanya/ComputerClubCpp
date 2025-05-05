cmake_minimum_required(VERSION 3.10)
project(computer_club)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(include)

set(LIB_SOURCES
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

add_library(computer_club_lib ${LIB_SOURCES})

set(SOURCES
    src/main.cpp
)

add_executable(computer_club ${SOURCES})
target_link_libraries(computer_club computer_club_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(computer_club_tests 
    tests/test_main.cpp
    tests/models/time_test.cpp
    tests/services/queue_manager_test.cpp
    tests/services/table_manager_test.cpp
    tests/controllers/computer_club_controller_test.cpp
    tests/views/output_formatter_test.cpp
)
target_link_libraries(computer_club_tests 
    GTest::gtest 
    GTest::gmock
    computer_club_lib
)
target_include_directories(computer_club_tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)
gtest_discover_tests(computer_club_tests)