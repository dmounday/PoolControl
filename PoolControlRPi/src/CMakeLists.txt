
message(STATUS CppGPIOLib ${CppGPIOLIB})


set(SRC_FILE_LIST ./IC40.cpp
./EquipmentCommands.cpp
./EquipmentBase.cpp
./LogicLevelShifter.cpp
./JsonHandler.cpp
./MomentarySwitch.cpp
./ConfigGlobal.cpp
./WirelessHandler.cpp
./WirelessConsumer.cpp
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
./SensorBase.cpp
)

add_library( PoolControlLib ${SRC_FILE_LIST})

target_include_directories( PoolControlLib PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ../${HTTPSERVERLIB}
                           ../${CppGPIOINCLUDE} 
                           ../${PLOG_PATH})
target_link_libraries(PoolControlLib HTTPServerLib CppGPIOLib ${ARMLIBS})

