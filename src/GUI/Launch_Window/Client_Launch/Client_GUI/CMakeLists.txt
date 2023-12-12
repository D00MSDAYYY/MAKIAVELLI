cmake_minimum_required(VERSION 3.26)

project(Client_GUI)

add_subdirectory(Player_Dashboard)

add_library(${PROJECT_NAME})

qt_add_resources(RCC 
	cg_images.qrc
)

target_sources(${PROJECT_NAME}
PRIVATE
	client_gui.cpp
	${RCC}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/client_gui.h
	${CMAKE_CURRENT_SOURCE_DIR}/client_gui.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::Widgets
	Networking
	Player_Dashboard
)

