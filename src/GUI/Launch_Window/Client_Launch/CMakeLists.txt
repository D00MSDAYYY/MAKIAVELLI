cmake_minimum_required(VERSION 3.26)

project(Client_Launch)

add_subdirectory(Client_GUI)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	client_launch.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/client_launch.h
	${CMAKE_CURRENT_SOURCE_DIR}/client_launch.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Client_GUI
)

