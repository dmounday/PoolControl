# Pool Controller App for Raspberry Pi 3 B+

Application to control the power to the simple pool equipment. 
The relays and sensors are a custom installation created for a 
small pool.

Features:
* Dependency control of equipment (i.e. Main Pump must be on if IC40 is on).
* Support for any number of temperature sensors.
* Freeze guard - turn of Main pump if AirTemp temperature drops below set value.
* Options for local push-button switch control of equipment.
* Web interface for equipment control and scheduling


Requires C++17.

This application depends on the library code within this repository:
* HTTPServerLib
* plog (Header only logging)
* CppGPIO (adapted to use boost/asio for timers)

and the following:

* Boost version 1.71 or later.
* arm-i2c library


To Build:
1. Edit the RPiCrossTools.cmake to reflect your toolchain.
2. $ cmake -S . -B build
   $ cd build; make -j8

   Executable is build/main/PoolControlRPi

   Example configuration and scheduling files are:
      poolconfig.json
      schedule.json
      poolsmartz.service 
3.  
   Run as
   $PoolControlRPi poolconfig.json schedule.json info [console]

   or install as a service.

Notes:
The CppGPIO library is a static library linked with the application. This may
conflict with usage of GPIO by other applications. This should be implemented
as a shared library.
   

   
   