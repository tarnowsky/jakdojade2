cmake_minimum_required(VERSION 3.25)
project(jakdojade2)

set(CMAKE_CXX_STANDARD 17)

add_executable(jakdojade2 main.cpp list.h tstring.h Process.cpp Process.h tstring.cpp Town.cpp Town.h HashMap.cpp HashMap.h)
add_executable(HashMap_Test main.cpp tstring.h tstring.cpp HashMap.cpp HashMap.h)