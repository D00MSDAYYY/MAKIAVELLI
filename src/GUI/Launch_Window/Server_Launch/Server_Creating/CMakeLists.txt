cmake_minimum_required(VERSION 3.26.4)

project(Server_Creating)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	server_creating.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/server_creating.h
	${CMAKE_CURRENT_SOURCE_DIR}/server_creating.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Server_GUI
)
