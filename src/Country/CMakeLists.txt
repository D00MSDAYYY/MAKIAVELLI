cmake_minimum_required(VERSION 3.26.4)

project(Country)

add_library(${PROJECT_NAME} )

target_sources(${PROJECT_NAME}
PRIVATE
	activity_points.cpp
	cards_holder.cpp 
	country.cpp 
	resources.cpp 
	points.cpp 
	locations.cpp
PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/activity_points.hpp
	${CMAKE_CURRENT_LIST_DIR}/cards_holder.hpp 
	${CMAKE_CURRENT_LIST_DIR}/country.hpp 
	${CMAKE_CURRENT_LIST_DIR}/resources.hpp 
	${CMAKE_CURRENT_LIST_DIR}/points.hpp 
	${CMAKE_CURRENT_LIST_DIR}/locations.hpp 
)


target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} 
PUBLIC 
	Boost::json
	Map
	Networking
	Card_Bank
)