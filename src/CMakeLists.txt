cmake_minimum_required(VERSION 3.26.4)

project(MAKIAVELLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Country)
add_subdirectory(Game_Factory)
add_subdirectory(Map)
add_subdirectory(Card_Bank)
add_subdirectory(Networking)
add_subdirectory(GUI)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Map
    Game_Factory
    Card_Bank
    Country
    Networking
    GUI
  )
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     MACOSX_BUNDLE ON
# )
