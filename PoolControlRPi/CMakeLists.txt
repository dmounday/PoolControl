cmake_minimum_required(VERSION 3.18)
# 
# Set Tool chain variables
set(CMAKE_TOOLCHAIN_FILE RPiCrossTools.cmake)

project(poolsmartz VERSION 1.1.0
        DESCRIPTION "PoolController on RPi"
  LANGUAGES CXX)
 
include(CMakePrintHelpers)
include(ExternalProject)
cmake_print_variables(CMAKE_PROJECT_NAME PROJECT_NAME CMAKE_INSTALL_PREFIX
                      CMAKE_SYSTEM_PREFIX_PATH
                      CMAKE_BINARY_DIR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(HTTPSERVERLIB ../HTTPServerLib)
set(CppGPIOINCLUDE ../CppGPIO/include)
set(PLOG_PATH ../plog/include)



add_subdirectory(../CppGPIO CppGPIOLib)
add_subdirectory(../HTTPServerLib HTTPServerLib)
add_subdirectory(src)
add_subdirectory(main)







