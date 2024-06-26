/*
 * HeatPumpSchedule.cpp
 *
 *  Created on: Feb 11, 2021
 *      Author: dmounday
 */
#define DEBUG
#ifdef DEBUG
#define DBG_LOG(x) x
#else
#define DBG_LOG(x)
#endif
#include "HeatPumpSchedule.h"
#include <cmath>

namespace pentair_control {

HeatPumpSchedule::HeatPumpSchedule (pt::ptree& prop_node,
                                    GblData& gData):
   EquipSched(gData.IOC(), prop_node, gData.Equip(HEAT_PUMP)),
   gD_{gData}, sTimer_{gData.IOC()},
   sensor_prop_{prop_node.get_child("Sensor")}
{
   sensorId_ = sensor_prop_.get<std::string>("ID");
   sensorDelay_ = sensor_prop_.get<int>("Delay", 0);
   sensorInterval_ = sensor_prop_.get<int>("Interval", DEFAULT_INTERVAL);
   temp_ = sensor_prop_.get<float>("Temp", 0);
   diff_ = sensor_prop_.get<float>("Diff", 0);
   state_ = sensor_prop_.get<std::string>("State", "off") == "off"?
       State::OFF: State::ON;
   PLOG(plog::debug)<< "ID:"<< sensorId_ << " Delay: " << sensorDelay_ <<
       " Temp: "<< temp_ << " Diff: "<< diff_;
}
void HeatPumpSchedule::SetSensor(const pt::ptree& props){
  temp_ = props.get<float>("Temp", temp_);
  std::string dfltState = state_==State::ON? "on": "off";
  auto const& statestr = props.get<std::string>("State", dfltState);
  state_ = statestr == "off"? State::OFF: State::ON;
  // update Sensor Property tree in schedule runtime configuration.
  PLOG(plog::debug)<< "temp: " << temp_ << " state:"<< statestr;
  sensor_prop_.put("Temp", temp_);
  sensor_prop_.put("State", statestr);
  if ( sTimer_.cancel()> 0){
    const boost::system::error_code ec{boost::asio::error::in_progress};
    ReSample(ec);
  }
}
void HeatPumpSchedule::ReSample (const boost::system::error_code &ec) {
  if ( ec == boost::asio::error::operation_aborted)
    return;
  float sTemp = gD_.GetSensorValue (sensorId_);
  if (state_ == State::ON ) {
    if (sTemp < temp_-diff_) {
      DBG_LOG(PLOG(plog::debug)<< "HeatPump SwitchON: " << sTemp << " "<< temp_);
      Equip ()->SwitchOn ();
      Equip()->setAuxStatus(std::make_pair(std::string("heat"), std::string("Running")));
    } else {
      DBG_LOG(PLOG(plog::debug)<< "HeatPump SwitchOFF Standby: "<< sTemp << " "<< temp_);
      Equip ()->SwitchOff ();
      Equip()->setAuxStatus(std::make_pair(std::string("heat"), std::string("Standby")));
    }
  } else {
    DBG_LOG(PLOG(plog::debug)<< "HeatPump SwitchOff: "<< sTemp << " "<< temp_);
    Equip()->SwitchOff();
    Equip()->setAuxStatus(std::make_pair(std::string("heat"), std::string("OFF")));
  }
  sTimer_.expires_after(std::chrono::seconds(sensorInterval_));
  sTimer_.async_wait(
      std::bind(&HeatPumpSchedule::ReSample, this, std::placeholders::_1));
}
void HeatPumpSchedule::Run () {
  PLOG(plog::debug);
  sTimer_.expires_after (std::chrono::seconds (sensorDelay_));
  sTimer_.async_wait (
      std::bind (&HeatPumpSchedule::ReSample, this, std::placeholders::_1));
}

} /* namespace pentair_control */
