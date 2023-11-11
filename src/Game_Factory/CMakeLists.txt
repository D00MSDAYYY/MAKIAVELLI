cmake_minimum_required(VERSION 3.26.4)

project(Game_Factory)

find_package(Boost REQUIRED COMPONENTS json)

find_package(Qt6 REQUIRED COMPONENTS Core)
set(AUTORCC ON)

# qt_add_resources(RCC ${JSON_FILES})
# qt_add_resources(RCC ${JSON_FILES_QRC})
qt_add_resources(RCC json_files.qrc)

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
PRIVATE
  game_factory.cpp
  ${RCC}
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
   Qt6::Core
   Card_Bank
   Networking
)

