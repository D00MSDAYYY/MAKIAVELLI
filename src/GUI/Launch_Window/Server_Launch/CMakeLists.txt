cmake_minimum_required(VERSION 3.26)

project(Server_Launch)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
#qt_standard_project_setup()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

add_subdirectory(Server_Creating)
add_subdirectory(Server)

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
PRIVATE
  server_launch.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/server_launch.h
  ${CMAKE_CURRENT_SOURCE_DIR}/server_launch.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    Qt6::Widgets
    Server_Creating
    Server
    Networking
)

