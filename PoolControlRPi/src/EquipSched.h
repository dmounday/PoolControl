/*
 * EquipSched.h
 *
 *  Created on: Feb 10, 2021
 *      Author: dmounday
 */

#ifndef EQUIPSCHED_H_
#define EQUIPSCHED_H_
#include <string>
#include <chrono>
#include <vector>
#include <exception>
#include <string>
#include <boost/optional.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/asio.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include "plog/Log.h"
#include "RelaySwitcher.h"

namespace pentair_control {
namespace pt = boost::property_tree;


class ScheduleFileException: std::exception {
public:
  const char* msg;
  ScheduleFileException(const char* message):msg{message}
  {}
};

class EquipSched {
public:

    EquipSched(boost::asio::io_context& ioc,
                           pt::ptree& node,
                           EquipmentPtr ep);

    virtual ~EquipSched(){};

    /// @brief Update schdule object with new times.
    /// @param node parsed json schedule tree node.
    void Reschedule(const pt::ptree& node);

    virtual void SetSensor(const pt::ptree& node);

    /// @brief Set objects timers to start/stop equipment at scheduled time.
    virtual void Run();

    /// @brief Calculate the start and stop times from the equipment schedule
    /// and update the objects start and stop times.
    void CalcStartStopTimes();

    /// @brief Return true if schedule is manual.
    /// @return true if manual.
    inline bool Maunal()const {return manual_;};

    /// @brief Calculate the start and stop times and return true if current
    /// time is between start and stop time.
    /// @return true if time to run.
    bool RunNow();
    inline RelayPtr Equip()const {return std::static_pointer_cast<RelaySwitcher>(ep_);};
    static bool isRunSchedule() { return runSchedule; };
    static void setRunSchedule(bool run){ runSchedule = run;};
private:
    boost::asio::io_context& ioc_;
    EquipmentPtr ep_;
    boost::asio::system_timer timer_;
    bool manual_;
    bool runNow_;
    pt::ptree& schedProp_;
    std::string stopTime;
    std::string startTime;

    boost::posix_time::ptime start_date_time;
    boost::posix_time::ptime stop_date_time;

    int GetSeconds(std::string hr_min);
    std::chrono::system_clock::duration duration_since_midnight();

    void GetStartStop(const pt::ptree& node);
    void StopEquipment(const boost::system::error_code &ec);
    void StartEquipment(const boost::system::error_code &ec);
    long unsigned StopAfter();
    long unsigned StartAfter();
    static bool runSchedule;
};

} /* namespace pentair_control */

#endif /* EQUIPSCHED_H_ */
