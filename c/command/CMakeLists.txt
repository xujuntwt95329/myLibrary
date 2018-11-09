cmake_minimum_required (VERSION 2.8)

project (command C)

include_directories (inc)

SET(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/command_test.c
    ${CMAKE_CURRENT_LIST_DIR}/src/command.c
    )

add_executable(${PROJECT_NAME} ${SOURCES})
