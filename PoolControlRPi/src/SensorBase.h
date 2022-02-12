/*
 * Sensor.h
 *
 *  Created on: Jan 19, 2021
 *      Author: dmounday
 */

#ifndef SRC_SENSORBASE_H_
#define SRC_SENSORBASE_H_
#include <boost/asio.hpp>
#include "EquipmentBase.h"

namespace pentair_control {
using SensorIDs = std::vector<std::string const *>;
class SensorBase: public EquipmentBase {
public:
  SensorBase (const std::string& name);
  /**
   * Set refresh_stop flag. May stop refresh threads in derived objects.
   */
  virtual void Stop() override {refresh_stop_ = true;};
  virtual void Start();
  virtual SensorIDs GetSensorIDs() = 0;
  virtual float GetSensorValue(std::string const&) const = 0;
protected:
  bool refresh_stop_;
  std::chrono::system_clock::time_point last_reading_;
  std::string label;
};

} /* namespace pentair_control */

#endif /* SRC_SENSORBASE_H_ */
