cmake_minimum_required(VERSION 3.2)

project(ARMED_BANDIT
        VERSION 1.0
        DESCRIPTION "Visualizing the K-armed Bandit Problem"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(STATUS "Cmake Build Configuration for ${PROJECT_NAME} @v${PROJECT_VERSION}")

add_executable(${PROJECT_NAME} src/main.cpp
                src/core/game/game.cpp
                src/core/graphics/graphics.cpp
                src/models/agent.cpp
                src/core/env/env.cpp
                src/core/screens/screen.cpp
                src/core/screens/home/homescreen.cpp
                src/core/screens/menu/menu.cpp
                src/core/screens/overlay/overlay.cpp
                src/utils/utils.cpp
                src/utils/time.cpp
                src/utils/texture.cpp
                
                )
                

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/include)

if(WIN32)
    message("Windows")
    target_link_libraries(${PROJECT_NAME} PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/lib/windows/x64/SDL2_ttf.lib
                        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/lib/windows/x64/SDL2_image.lib
                        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/lib/windows/x64/SDL2.lib)

    file(GLOB_RECURSE DLLS ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL2/lib/windows/x64/dlls/*.dll)


    foreach(Dllfile ${DLLS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                         COMMAND "${CMAKE_COMMAND}" -E copy
                         ${Dllfile} ${CMAKE_CURRENT_SOURCE_DIR}/build
                         COMMENT "Copying ${Dllfile}")
    endforeach()
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND "${CMAKE_COMMAND}" -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${CMAKE_CURRENT_SOURCE_DIR}/build/assets
                    COMMENT "Copying assets")