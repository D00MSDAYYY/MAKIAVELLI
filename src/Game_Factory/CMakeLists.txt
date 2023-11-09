cmake_minimum_required(VERSION 3.26.4)

project(Game_Factory)

add_library(${PROJECT_NAME} "")

find_package(Boost REQUIRED COMPONENTS json)
find_package(Qt6 REQUIRED COMPONENTS Core)

# set(AUTORCC ON)

qt_add_resources(${PROJECT_NAME} "json_files"
  PREFIX "/json_files"
  FILES ${JSON_FILES} 
  
)

target_sources(${PROJECT_NAME}
PRIVATE
  game_factory.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/game_factory.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(${PROJECT_NAME} 
PUBLIC 
   Boost::json
   Card_Bank
   Networking
)

