# Testing library
include ( FetchContent )
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.6)
FetchContent_MakeAvailable(catch)
# Adds Catch2::Catch2


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

###set(CATCH2_INCLUDE_DIR ../../Catch2/src) 
###add_library(Catch INTERFACE)
###target_include_directories(Catch INTERFACE ${CATCH2_INCLUDE_DIR})
                       
add_executable( SensorTest SensorTests.cpp)
target_link_libraries(SensorTest PRIVATE
 PoolControlLib
 -pthread
 Catch2::Catch2)


#target_include_directories( SensorTest PUBLIC
#	                         ../src
#                           ../${PLOG_PATH})

