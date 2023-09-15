/*
 * MainPumpSchedule.cpp
 *
 *  Created on: Feb 13, 2021
 *      Author: dmounday
 */

#include "MainPumpSchedule.h"

namespace pentair_control {

MainPumpSchedule::MainPumpSchedule (pt::ptree &prop_node, GblData &gData) :
    EquipSched (gData.IOC (), prop_node, gData.Equip (MAIN_PUMP)), gD_ { gData }, sTimer_ {
        gData.IOC () }, propNode_ { prop_node } {
  speed_ = propNode_.get ("Settings.Speed", 0);
  guardState_ =
      propNode_.get ("FreezeGuard.State", "on") == "on" ? true : false;
  guardTemp_ = propNode_.get ("FreezeGuard.LowTemp", 0.0);
  sensorID_ = propNode_.get ("FreezeGuard.SensorID", "");
  PLOG(plog::debug) << "Speed: " << speed_;
}
void MainPumpSchedule::ReSample (const boost::system::error_code &ec) {
  PLOG(plog::debug) << "guardTemp " << guardState_;
  if (ec == boost::asio::error::operation_aborted)
    return;
  if (!RunNow ()) {
    // If pump is not now running then check freeze guard state.
    float sTemp = gD_.GetSensorValue (sensorID_);
    if (guardState_) {
      if (sTemp <= guardTemp_) {
        PLOG(plog::debug) << "MainPump on: " << sTemp << " < GuardTemp: "
            << guardTemp_;
        Equip ()->SwitchOn ();
      } else if (Equip ()->State () == RelaySwitcher::RelayState::ON) {
        PLOG(plog::debug) << "MainPump off: " << sTemp << " > GuardTemp";
        Equip ()->SwitchOff ();
      }
    }
  }
  sTimer_.expires_after (
      std::chrono::seconds (std::chrono::seconds (SAMPLETIME)));
  sTimer_.async_wait (
      std::bind (&MainPumpSchedule::ReSample, this, std::placeholders::_1));
}
void MainPumpSchedule::Run () {
  PLOG(plog::debug);
  if (guardState_) {
    sTimer_.expires_after (std::chrono::seconds (SAMPLETIME));
    sTimer_.async_wait (
        std::bind (&MainPumpSchedule::ReSample, this, std::placeholders::_1));
  }
  EquipSched::Run();
}

} /* namespace pentair_control */
