/*
 * Sensor.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: dmounday
 */

#include <SensorBase.h>

namespace pentair_control {

SensorBase::SensorBase (const std::string& name):
  EquipmentBase{name}, refresh_stop_{false}
{}
void SensorBase::Start(){
  PLOG(plog::debug);
  return;
}
} /* namespace pentair_control */
