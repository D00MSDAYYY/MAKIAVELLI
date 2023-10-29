cmake_minimum_required(VERSION 3.26.4)


project(Networking)

add_subdirectory(3rdParty)

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
PRIVATE 
  game_server.cpp
  player_client.cpp
  text_message.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/game_network.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/game_server.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/player_client.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/text_message.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PUBLIC 
  Country
  Game_Factory
  3rdParty
  GUI
)
