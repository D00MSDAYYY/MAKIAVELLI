cmake_minimum_required(VERSION 3.26)

project(Game_Window)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} )

target_sources(${PROJECT_NAME}
PRIVATE
  game_window.cpp
PUBLIC
  game_window.h
  game_window.ui
)


target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    Qt6::Widgets

)

