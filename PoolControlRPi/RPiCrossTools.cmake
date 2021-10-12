set(CMAKE_SYSTEM_NAME               Linux)
set(CMAKE_SYSTEM_PROCESSOR          RPi-arm)

set(RPi_TOOLCHAIN_PATH /opt/cross-pi-gcc-10.2.0-2/bin/)
set(CMAKE_EXECUTABLE_SUFFIX "")

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

set(CMAKE_AR                        ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER              ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER                ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER              ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER                    ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY                   ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-objcopy${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_RANLIB                    ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-ranlib${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_SIZE                      ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-size${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")
set(CMAKE_STRIP                     ${RPi_TOOLCHAIN_PATH}arm-linux-gnueabihf-strip${CMAKE_EXECUTABLE_SUFFIX} CACHE INTERNAL "")

#set(CMAKE_C_FLAGS                   "-Wno-psabi --specs=nosys.specs -fdata-sections -ffunction-sections -Wl,--gc-sections" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS                 "${CMAKE_C_FLAGS} -fno-exceptions" CACHE INTERNAL "")

#set(CMAKE_C_FLAGS_DEBUG             "-Os -g" CACHE INTERNAL "")
#set(CMAKE_C_FLAGS_RELEASE           "-Os -DNDEBUG" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
#set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)