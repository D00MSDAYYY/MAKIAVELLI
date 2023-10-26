cmake_minimum_required(VERSION 3.26.4)

project(MAKIAVELLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Country)
add_subdirectory(Game)
add_subdirectory(Map)
add_subdirectory(Card_Bank)
add_subdirectory(Networking)
add_subdirectory(GUI)
add_subdirectory(Concurrency)


# find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
# if(CMAKE_CXX_CPPCHECK)
# 	list(
#         APPEND CMAKE_CXX_CPPCHECK 
#             "--enable=warning"
#             "--inconclusive"
#             "--force" 
#             "--inline-suppr"
#             "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
#     )
# endif()


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Map
    Game
    Card_Bank
    Country
    Networking
    GUI
  )
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE ON
)
