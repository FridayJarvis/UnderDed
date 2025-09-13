cmake_minimum_required(VERSION 4.0)
project(UnderDed)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(json)

add_executable(${PROJECT_NAME} src/main.cpp
        src/GameManager.cpp
        include/GameManager.h
        src/Inventory.cpp
        include/Inventory.h
        src/Shop.cpp
        include/Shop.h
        src/InputHandler.cpp
        include/InputHandler.h
        src/Coord.cpp
        include/Coord.h)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PRIVATE include)
