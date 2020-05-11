cmake_minimum_required(VERSION 3.12)
project(project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules")

find_package(SFML 2.4.2 COMPONENTS graphics audio window system REQUIRED)

add_executable(project main.cpp player.cpp player.h map.h view.h mission.h entity.cpp entity.h map.cpp view.cpp enemy.cpp enemy.h menu.cpp menu.h Game.cpp Game.h HardEnemy.cpp HardEnemy.h)

target_link_libraries(project sfml-graphics sfml-audio sfml-window sfml-system)