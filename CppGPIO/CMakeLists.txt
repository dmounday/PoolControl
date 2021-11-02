cmake_minimum_required(VERSION 3.18)
project(CppGPIO LANGUAGES CXX)
set(SRC_FILE_LIST src/output.cpp
src/i2c.cpp
src/make_unique.hpp
src/tools.hpp
src/buttons.cpp
src/gpio.cpp
src/tools.cpp
)

add_library( CppGPIOLib ${SRC_FILE_LIST})
target_include_directories( CppGPIOLib PUBLIC include )

