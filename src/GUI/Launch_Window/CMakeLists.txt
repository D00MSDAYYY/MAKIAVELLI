cmake_minimum_required(VERSION 3.26)

project(Launch_Window)

add_subdirectory(Server_Launch)
add_subdirectory(Client_Launch)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	launch_window.cpp
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/launch_window.h
	${CMAKE_CURRENT_SOURCE_DIR}/launch_window.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Server_Launch
	Client_Launch
)

