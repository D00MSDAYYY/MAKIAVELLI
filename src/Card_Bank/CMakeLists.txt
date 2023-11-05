cmake_minimum_required(VERSION 3.26.4)

project(Card_Bank)

add_library(${PROJECT_NAME} )

find_package(Boost REQUIRED COMPONENTS json)

target_sources(${PROJECT_NAME} 
PRIVATE
  card.cpp
  card_bank.cpp

PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/card.hpp
  ${CMAKE_CURRENT_LIST_DIR}/card_bank.hpp
)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PUBLIC 
    Boost::json
    Country
)