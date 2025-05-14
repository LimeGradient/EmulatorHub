cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(EmulatorHub VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include/)

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.2.0")
CPMAddPackage("gh:gabime/spdlog@1.15.3")
CPMAddPackage("gh:jeremy-rifkin/cpptrace#v0.8.3")
CPMAddPackage("gh:nicbarker/clay#v0.13")

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt
    spdlog
    cpptrace
    clay
)