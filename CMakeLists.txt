cmake_minimum_required(VERSION 2.8.9)
project (clibraries C)
set(CMAKE_BUILD_TYPE Release)

# remove this to prevent log
add_definitions(-DAPP_DEBUG)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_library(clibraries SHARED ${SOURCES})

#install(TARGETS clibraries DESTINATION ${PROJECT_SOURCE_DIR}/build)
