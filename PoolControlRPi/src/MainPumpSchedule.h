/*
 * MainPumpSchedule.h
 *
 *  Created on: Feb 13, 2021
 *      Author: dmounday
 */

#ifndef SRC_MAINPUMPSCHEDULE_H_
#define SRC_MAINPUMPSCHEDULE_H_

#include "EquipSched.h"
#include "GblData.h"
#include "RelaySwitcher.h"


namespace pentair_control {

class MainPumpSchedule : public EquipSched {
  const int SAMPLETIME{60};
public:
  MainPumpSchedule (pt::ptree& node, GblData& gData );
  void Run();

private:
  GblData const& gD_;
  boost::asio::system_timer sTimer_;
  pt::ptree& propNode_;
  int speed_;     // pump speed setting
  bool guardState_;
  float guardTemp_;
  std::string sensorID_;

  void ReSample(const boost::system::error_code &ec);
};

} /* namespace pentair_control */

#endif /* SRC_MAINPUMPSCHEDULE_H_ */
