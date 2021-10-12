/*
 * LogicLevelShifter.h
 *
 *  Created on: Feb 8, 2021
 *      Author: dmounday
 */

#ifndef SRC_LOGICLEVELSHIFTER_H_
#define SRC_LOGICLEVELSHIFTER_H_
#include "plog/Log.h"

#include <boost/property_tree/ptree.hpp>
#include <cppgpio/output.hpp>

namespace pentair_control {
namespace pt = boost::property_tree;
class LogicLevelShifter : public GPIO::DigitalOut {
public:
  LogicLevelShifter (const pt::ptree& node);
  LogicLevelShifter(unsigned int gpio);
  virtual ~LogicLevelShifter();
  void EnableShifter();
  void DisableShifter();
};

} /* namespace pentair_control */

#endif /* SRC_LOGICLEVELSHIFTER_H_ */
