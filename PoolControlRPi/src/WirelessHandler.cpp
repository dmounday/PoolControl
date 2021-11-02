/*
 * WirelessHandler.cpp
 *
 *  Created on: Jul 26, 2020
 *      Author: dmounday
 */

#include "WirelessHandler.h"
#include "WirelessSensors.h"
//#define DEBUG
#ifdef DEBUG
#define DBG_LOG(x) x
#else
#define DBG_LOG(x)
#endif
namespace pentair_control {
/**
 * "WirelessHandler":
  {
  "_comment3": "Interface to MightyHat UPS and wireless R/T",
   "SerialPort": "/dev/ttyAMA0",
   "BaudRate": 115200,
   "Destination": "Wireless"
  },
 * @param io
 * @param node
 */
WirelessHandler::WirelessHandler(boost::asio::io_context& io, const pt::ptree& node):
	SerialPort(io)
{
  PLOG(plog::debug)<< "Start serial.";
	if ( !start(node.get<std::string>("SerialPort"), node.get<int>("BaudRate"))) {
		PLOG(plog::error)<< "Unable to start serial port";
	}
}
void WirelessHandler::RegisterConsumer( WirelessConsumer* c){
  consumers.push_back(c);
}
void
WirelessHandler::on_receive_(const std::string& data){
  DBG_LOG(PLOG(plog::debug)<< data);
  for (auto c: consumers){
    if ( c->Consume(data))
      return;
  }
	//return UpdateSensors(data);
}

} /* namespace WirelessSerialSensors */
