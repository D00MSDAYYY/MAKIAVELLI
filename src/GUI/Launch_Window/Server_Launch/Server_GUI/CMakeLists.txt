cmake_minimum_required(VERSION 3.26.4)

project(Server_GUI)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	server_GUI.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/server_GUI.h
	${CMAKE_CURRENT_SOURCE_DIR}/server_GUI.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Networking
)
