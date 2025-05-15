cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(EmulatorHub VERSION 0.1.0 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

include(cmake/CPM.cmake)
CPMAddPackage("gh:fmtlib/fmt#11.2.0")
CPMAddPackage("gh:gabime/spdlog@1.15.3")
CPMAddPackage("gh:jeremy-rifkin/cpptrace#v0.8.3")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt
    spdlog
    cpptrace::cpptrace

    ${wxWidgets_LIBRARIES}
)