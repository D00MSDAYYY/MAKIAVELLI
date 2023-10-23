cmake_minimum_required(VERSION 3.26.4)

project(Concurrency)

add_library(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME}
PRIVATE 
  concurrency.cpp
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/concurrency.hpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PUBLIC 
  Networking
  GUI
)
