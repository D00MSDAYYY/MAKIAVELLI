cmake_minimum_required(VERSION 3.26)

project(Server_Launch)

add_subdirectory(Server_Creating)
add_subdirectory(Server_GUI)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	server_launch.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/server_launch.h
	${CMAKE_CURRENT_SOURCE_DIR}/server_launch.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Server_Creating
)

