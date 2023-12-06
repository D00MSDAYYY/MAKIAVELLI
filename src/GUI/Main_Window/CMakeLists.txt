cmake_minimum_required(VERSION 3.26)

project(Main_Window)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	main_window.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.h
	${CMAKE_CURRENT_SOURCE_DIR}/main_window.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Launch_Window
)

