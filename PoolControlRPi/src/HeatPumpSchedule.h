/*
 * HeatPumpSchedule.h
 *
 *  Created on: Feb 11, 2021
 *      Author: dmounday
 */

#ifndef HEATPUMPSCHEDULE_H_
#define HEATPUMPSCHEDULE_H_

#include "GblData.h"
#include "RelaySwitcher.h"
#include "EquipSched.h"

namespace pentair_control {
/**
 * @brief HeatPumpSchedule class used to schedule heat pump operation.
 * 
 */
class HeatPumpSchedule : public EquipSched {
  const int DEFAULT_INTERVAL{60};
  enum class State {
    OFF,
    ON
  };
public:
/**
 * @brief Construct a new Heat Pump Schedule object from parsed JSON schedule and
 * GblData reference.
 * 
 * @param sched_tree containing HEAT_PUMP node. Such as:
 * "HeatPump": {
 *   "Sensor": {
 *      "State": "on",          // enabled/disabled
 *      "ID": "HeatPumpInTemp",
 *      "Delay": "10",
 *      "Interval": "15",
 *      "Temp": "22.2240009",
 *      "Diff": "0.8"
 *    }
 * }
 *
 * @param GblData reference to the GblData class.
 */
  HeatPumpSchedule (pt::ptree& sched_tree, GblData& );
  /**
   * @brief Update enabled/disabled and on temperature from property tree. 
   * 
   * @param sensor_prop HeatPump node with State and Temp.
   */
  void SetSensor(const pt::ptree& sensor_prop) override;
  /**
   * @brief Start sampling timer.
   * 
   */
  void Run();
private:
  GblData const& gD_;
  boost::asio::system_timer sTimer_;
  pt::ptree& sensor_prop_;
  std::string sensorId_;
  int sensorDelay_;
  int sensorInterval_;
  float temp_;  // set temperature
  float diff_;  // turn-on difference from set value.
  State state_; // enable or disable heat pump.
  /**
   * @brief Callback from timer to sample water temperature and turn heat pump on or off.
   * Pump is on if sampled temperature is less that set tempeature - diff_.
   * 
   * @param ec boost error code.
   */
  void  ReSample(const boost::system::error_code &ec);
};

} /* namespace pentair_control */

#endif /* HEATPUMPSCHEDULE_H_ */
