cmake_minimum_required(VERSION 3.18)
project(HTTPServerLib LANGUAGES CXX)

add_library( HTTPServerLib HTTPServerLib.cpp)
target_include_directories( HTTPServerLib PUBLIC ${PLOG_PATH} )