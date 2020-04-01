cmake_minimum_required(VERSION 3.17.0)

project(snake)
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${SRC_DIR})
set(SOURCES "${SRC_DIR}/main.cpp" "${SRC_DIR}/controller.cpp" "${SRC_DIR}/ui.cpp" "${SRC_DIR}/player.cpp" "${SRC_DIR}/field.cpp")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(snake ${CURSES_LIBRARIES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
