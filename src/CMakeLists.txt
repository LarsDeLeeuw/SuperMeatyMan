cmake_minimum_required(VERSION 3.16)
project(SuperMeatyMan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O2 -g -Wall -Werror")
# find libraries: additional modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# find SFML library:
find_package(SFML COMPONENTS system graphics window REQUIRED)


set(HEADER_FILES
        "include/Game.hpp"
        "include/EntityView.hpp"
        "include/PlayerView.hpp"
        "include/WallView.hpp"
        "include/GoalView.hpp"
        "include/BGTileView.hpp"
        "include/ConcreteEntityFactory.hpp"
        "include/StateStack.hpp"
        "include/State.hpp"
        "include/DeadState.hpp"
        "include/GameState.hpp"
        "include/MenuState.hpp"
        "include/Window.hpp"
        )

set(SOURCE_FILES
        "Game.cpp"
        "EntityView.cpp"
        "PlayerView.cpp"
        "WallView.cpp"
        "GoalView.cpp"
        "BGTileView.cpp"
        "ConcreteEntityFactory.cpp"
        "StateStack.cpp"
        "State.cpp"
        "DeadState.cpp"
        "GameState.cpp"
        "MenuState.cpp"
        "Window.cpp"
        )

add_executable(SuperMeatyMan main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(SuperMeatyMan
        logic_lib
        ${SFML_LIBRARIES}
        )

add_subdirectory(logic)
#add_subdirectory(Google_tests)

