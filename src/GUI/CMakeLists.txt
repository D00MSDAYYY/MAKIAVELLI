cmake_minimum_required(VERSION 3.26.4)

project(GUI)

add_subdirectory(Main_Window)
add_subdirectory(Game_Window)
add_subdirectory(Launch_Window)


find_package(Qt6 REQUIRED COMPONENTS Widgets)
#qt_standard_project_setup()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} )

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    Qt6::Widgets
    Main_Window
    Launch_Window
    Game_Window
)