cmake_minimum_required(VERSION 2.8)

set(SOURCE
	main.cpp
)

add_executable(main ${SOURCE})

target_link_libraries(main ${Boost_LIBRARIES})