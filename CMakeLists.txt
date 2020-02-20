cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(
	RDB
	bplustree_class.h
	btree_lowlevel_functions.h
	constants.h
	file_functions.cpp
	file_functions.h
	ftokenizer.cpp
	ftokenizer.h
	linkedlistfunc.h
	list.h
	main.cpp
	map_class.h
	mmap_class.h
	pair_struct.h
	parser.cpp
	parser.h
	queue.h
	record.cpp
	record.h
	sql.cpp
	sql.h
	stack.h
	state_functions.cpp
	state_functions.h
	stokenizer.cpp
	stokenizer.h
	table.cpp
	table.h
	token.cpp
	token.h
)
