cmake_minimum_required(VERSION 3.26)

project(Client)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
# qt_standard_project_setup()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

add_subdirectory(Client_Connector)
add_subdirectory(Client_Waiting)

add_library(${PROJECT_NAME} )

target_sources(${PROJECT_NAME}
PRIVATE
  client.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/client.h
  ${CMAKE_CURRENT_SOURCE_DIR}/client.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    Qt6::Widgets
    Client_Connector
    Client_Waiting
)
