
message(STATUS CppGPIOLib ${CppGPIOLIB})


set(SRC_FILE_LIST ./IC40.cpp
./EquipmentCommands.cpp
./EquipmentBase.cpp
./LogicLevelShifter.cpp
./JsonHandler.cpp
./MomentarySwitch.cpp
./ConfigGlobal.cpp
./WirelessHandler.cpp
./SerialPort.cpp
./SensorDope.cpp
./SI7021.cpp
./RemoteAccess.cpp
./DS18B20.cpp
./GblDataImpl.cpp
./EquipSched.cpp
./WirelessSensors.cpp
./GblData.cpp
./EquipmentStatus.cpp
./MainPumpSchedule.cpp
./RelaySwitcher.cpp
./HeatPumpSchedule.cpp
./ConfigScheduling.cpp
./RTSensor.cpp
./SensorModule.cpp
./main.cpp )

set(HDR_FILE_LIST ./WirelessHandler.h
./SI7021.h
./ConfigGlobal.h
./ConfigScheduling.h
./MainPumpSchedule.h
./RelaySwitcher.h
./HeatPumpSchedule.h
./GblDataImpl.h
./EquipmentCommands.h
./LogicLevelShifter.h
./WirelessSensors.h
./RemoteAccess.h
./IC40.h
./SensorModule.h
./EquipmentBase.h
./MomentarySwitch.h
./SerialPort.h
./DS18B20.h
./SensorDope.h
./JsonHandler.h
./EquipSched.h
./RTSensor.h
./EquipmentStatus.h
./GblData.h )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_executable( PoolControlRPi ${SRC_FILE_LIST})
target_link_libraries(PoolControlRPi -pthread )
target_include_directories( PoolControlRPi PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ../${HTTPSERVERLIB}
                           ../${CppGPIOINCLUDE} 
                           ../${PLOG_PATH})
target_link_libraries(PoolControlRPi HTTPServerLib CppGPIOLib ${ARMLIBS})

