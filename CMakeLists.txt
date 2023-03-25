cmake_minimum_required(VERSION 3.24)
project(csorting C)

set(CMAKE_C_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(csorting ${SDL2_INCLUDE_DIRS})

add_executable(csorting src/csorting.c src/microui.c)
target_link_libraries(csorting ${SDL2_LIBRARIES})