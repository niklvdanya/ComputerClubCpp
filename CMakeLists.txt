cmake_minimum_required(VERSION 3.10)
project(computer_club)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES 
    "src/*.cpp"
    "src/models/*.cpp"
    "src/services/*.cpp"
    "src/controllers/*.cpp"
    "src/utils/*.cpp"
    "src/views/*.cpp"
)

add_executable(computer_club ${SOURCES})