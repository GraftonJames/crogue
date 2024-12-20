cmake_minimum_required(VERSION 3.31)
project("crogue")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} "include")

file(GLOB MY_SOURCES "src/*.c" "include/*.h")
add_executable(${PROJECT_NAME} ${MY_SOURCES})

target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
