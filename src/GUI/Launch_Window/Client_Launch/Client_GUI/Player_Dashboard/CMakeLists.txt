cmake_minimum_required(VERSION 3.26)

project(Player_Dashboard)

find_package(Qt6 REQUIRED COMPONENTS SvgWidgets)

add_library(${PROJECT_NAME})

qt_add_resources(RCC 
	pd_images.qrc
)

target_sources(${PROJECT_NAME}
PRIVATE
	player_dashboard.cpp
	${RCC}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/player_dashboard.h
	${CMAKE_CURRENT_SOURCE_DIR}/player_dashboard.ui
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Qt6::SvgWidgets
)

