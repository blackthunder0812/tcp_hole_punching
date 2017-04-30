cmake_minimum_required(VERSION 2.8)

set(CLIENT_SOURCE
	client/main.cpp
)

# client code
add_executable(client ${CLIENT_SOURCE})
target_link_libraries(client ${Boost_LIBRARIES})

set(SERVER_SOURCE
	server/main.cpp
)

# server code
add_executable(server ${SERVER_SOURCE})
target_link_libraries(server ${Boost_LIBRARIES})
