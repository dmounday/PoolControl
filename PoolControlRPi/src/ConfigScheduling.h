/*
 * ConfigScheduling.h
 *
 *  Created on: Feb 10, 2021
 *      Author: dmounday
 */

#ifndef CONFIGSCHEDULING_H_
#define CONFIGSCHEDULING_H_
#include <boost/bind/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/utility/string_view.hpp>
using namespace boost::placeholders;
#include "GblData.h"
#include "MainPumpSchedule.h"
#include "HeatPumpSchedule.h"
#include "IC40.h"


namespace pentair_control {
  inline const std::string SCHEDULE{"Schedule"};
  inline const std::string RUNSCHEDULE{"RunSchedule"};
  inline const std::string SUCCESS("Success");
  inline const std::string FAILURE("Failure");

class ConfigScheduling {
public:
  /**
   * ConfigScheduling is an object containing the scheduling objects for eqch of
   * the pieces of equipment.
   * @param ioc
   * @param props property tree for Scheduling.
   * @param Equipment vector.
   * Property tree sample
   *
   *"MainPump":
      {
      "Start": "08:00",
      "Stop": "20:00",
      "Settings": {
        "Speed": 1
        }
      }
      },
      "IC40":
        {
        "Start": "08:10",
        "Stop": "20:00",
        "Settings": {
          "Rate": "30"
        }
        },
      "Booster":
        {
        "Start": "manual"
        },
      "Lighting":
        {
        "Start": "manual"
        },
    "HeatPump":{
      "Start": "08:05",
      "Stop": "20:00",
      "Sensor": {
       "ID": "HeatPumpInTemp",
       "Delay": "120",
        "TempOn": "88",
        "TempOff": "90"
      }
    }
   */
  ConfigScheduling (pt::ptree& props, GblData& );

  /// @brief If RunSchedule is enabled for each EquipSched object run any that are presently
  /// schduled to run.
  void RunSchedule();

  /// @brief Create a json string of the equipment properties and
  // schedules.
  /// @return ostringstring of json schedules.
  std::string GetSchedules();

  /// @brief Update equipment schedule from Json string
  /// @param  json string with equipment schedules. Such as:
  /// {"MainPump":{"Start":"8:00","Stop":"18:00"},
  /// "IC40":{"Start":"08:10","Stop":"14:03"},"Booster":{"Start":"manual","Stop":"manual"},
  /// "Lighting":{"Start":"manual","Stop":"manual"}}
  /// @return "Success" or "Failure" 
  std::string SetSchedules(boost::string_view );
  
  /// @brief Set sheduling of equipement on or off.
  /// @param json string {"RunSchedule": "true"}
  /// @return "Success" or "Failure"
  std::string SetRunSchedule(boost::string_view );

  /// @brief Update sensors identified in json string.
  /// @param  json string with data such as:
  ///  {"HeatPump":{"State":"off"}}
  /// @return "Success" or "Failure" 
  std::string SetSensors(boost::string_view);
private:
  GblData const& gD_;
  std::map<std::string, std::unique_ptr<EquipSched>> sched_;

};

} /* namespace SwitchTiming */

#endif /* CONFIGSCHEDULING_H_ */
