project(Networking)

add_subdirectory(3rdParty)

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
PRIVATE 
  game_server.cpp
  player_client.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/game_network.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/game_server.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/player_client.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PUBLIC 
  Country
  Game
  3rdParty
  GUI
)
