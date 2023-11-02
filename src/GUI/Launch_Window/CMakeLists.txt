cmake_minimum_required(VERSION 3.26)

project(Launch_Window)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
#qt_standard_project_setup()
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(Server)
add_subdirectory(Client)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
  launch_window.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/launch_window.h
  ${CMAKE_CURRENT_SOURCE_DIR}/launch_window.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    Qt6::Widgets
    Server
    Client
)

