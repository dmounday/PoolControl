
message(STATUS CppGPIOLib ${CppGPIOLIB})


set(SRC_FILE_LIST main.cpp
 )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
add_executable( poolsmartz ${SRC_FILE_LIST})

target_include_directories( poolsmartz PUBLIC      
                           ../${HTTPSERVERLIB}
                           ../${CppGPIOINCLUDE} 
                           ../${PLOG_PATH})

target_link_libraries(poolsmartz PRIVATE PoolControlLib HTTPServerLib CppGPIOLib -li2c -pthread)

install( FILES ../poolconfig.json ../schedule.json
  DESTINATION "/etc/poolsmartz" )
install( FILES ../poolsmartz.service DESTINATION "/etc/systemd/system")

install(TARGETS ${PROJECT_NAME}
  EXPORT "${PROJECT_NAME}Targets"
  RUNTIME DESTINATION "/bin/"
  )

set(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "don@mounday.com")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "armhf")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Pool Equipment controller")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
    "${CMAKE_CURRENT_SOURCE_DIR}/../postinst;${CMAKE_CURRENT_SOURCE_DIR}/../prerm")

include(CPack)
