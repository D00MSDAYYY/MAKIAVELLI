cmake_minimum_required(VERSION 3.26.4)

project(Map)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	map_cell.cpp
	map.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/map.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/map_cell.hpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PUBLIC 
	Country
)
