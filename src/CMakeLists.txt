cmake_minimum_required(VERSION 3.26.4)

project(MAKIAVELLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_GENERATOR "Unix Makefiles")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Boost REQUIRED COMPONENTS json)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${NESTED_DIRS})

add_subdirectory(Country)
add_subdirectory(Game_Factory)
add_subdirectory(Map)
add_subdirectory(Card_Bank)
add_subdirectory(Networking)
add_subdirectory(GUI)

qt_add_resources(RCC
	${JSON_FILES_QRC}
)

add_executable(${PROJECT_NAME} 
	main.cpp 
	${RCC}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	# Map
	# Game_Factory
	# Card_Bank
	# Country
	# Networking
	GUI
)
set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE ON
)
