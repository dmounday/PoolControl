
message(STATUS CppGPIOLib ${CppGPIOLIB})


set(SRC_FILE_LIST main.cpp
 )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
add_executable( PoolControlRPi ${SRC_FILE_LIST})

target_include_directories( PoolControlRPi PUBLIC
                           
                           ../${HTTPSERVERLIB}
                           ../${CppGPIOINCLUDE} 
                           ../${PLOG_PATH})

target_link_libraries(PoolControlRPi PRIVATE PoolControlLib HTTPServerLib CppGPIOLib -li2c -pthread)

