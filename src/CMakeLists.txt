cmake_minimum_required(VERSION 3.26.4)

project(MAKIAVELLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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


add_executable(${PROJECT_NAME} 
	main.cpp 
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
	Map
	Game_Factory
	Card_Bank
	Country
	Networking
	GUI
)
set_target_properties(${PROJECT_NAME} PROPERTIES
	MACOSX_BUNDLE ON
)

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND ${SOURCE_FILE} 3rdParty PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()

add_custom_target(
        clangformat
        COMMAND /usr/bin/clang-format
        -style=LLVM
        -i
        ${ALL_SOURCE_FILES}
)
