/*
 * WirelessHandler.h
 *
 *  Created on: Jul 26, 2020
 *      Author: dmounday
 */

#ifndef SRC_WIRELESSHANDLER_H_
#define SRC_WIRELESSHANDLER_H_
#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include "plog/Log.h"
#include "SerialPort.h"

namespace pentair_control {
namespace pt = boost::property_tree;
//
// Handles one or more WirelessRT that report on the same serial port.
//
class WirelessConsumer;

class WirelessHandler: public SerialPort {
  std::vector<WirelessConsumer*> consumers;
	void on_receive_(const std::string& data)override;
public:
  WirelessHandler(boost::asio::io_context& ioc, const pt::ptree& node);
  void RegisterConsumer(WirelessConsumer*);

};

} /* namespace WirelessSerialSensors */

#endif /* SRC_WIRELESSHANDLER_H_ */
