cmake_minimum_required(VERSION 3.26.4)

project(3rdParty)

find_package(Boost COMPONENTS asio)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/net_client.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net_common.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net_connection.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net_message.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net_server.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/net_tsqueue.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/olc_net.hpp
)

target_include_directories(${PROJECT_NAME}
INTERFACE
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME} 
INTERFACE
	Boost::headers
)
