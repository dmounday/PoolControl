/*
 * WirelessConsumer.h
 *
 *  Created on: Oct 29, 2021
 *      Author: dmounday
 */

#ifndef SRC_WIRELESSCONSUMER_H_
#define SRC_WIRELESSCONSUMER_H_
#include <string>
namespace pentair_control {

class WirelessConsumer {
public:
  WirelessConsumer ();
  virtual ~WirelessConsumer();
  virtual bool Consume(const std::string&)=0;
};

} /* namespace pentair_control */

#endif /* SRC_WIRELESSCONSUMER_H_ */
