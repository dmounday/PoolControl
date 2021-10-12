
set(SRC_FILE_LIST HTTPServerLib.cpp)

add_library( HTTPServerLib ${SRC_FILE_LIST})
target_include_directories( HTTPServerLib PUBLIC ${CMAKE_CURRENT_DIRECTORY} ${PLOG_PATH} )