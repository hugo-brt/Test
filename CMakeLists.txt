cmake_minimum_required(VERSION 3.10)
project(XianxiaIsaacCodex)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

add_executable(XianxiaIsaacCodex
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Projectile.cpp
    src/Room.cpp)

target_link_libraries(XianxiaIsaacCodex sfml-graphics sfml-window sfml-system)
