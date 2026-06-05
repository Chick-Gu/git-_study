cmake_minimum_required(VERSION 3.10)

project(TodoManager)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(todo_manager main.cpp todo.cpp)

install(TARGETS todo_manager DESTINATION bin)