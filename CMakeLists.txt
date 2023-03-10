cmake_minimum_required(VERSION 3.2)

project(ARMED_BANDIT
        VERSION 1.0
        DESCRIPTION "Visualizing the K-armed Bandit Problem"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Cmake Build Configuration for ${PROJECT_NAME} @v${PROJECT_VERSION}")

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/include)
