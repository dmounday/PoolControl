/*
 * ConfigGlobal.h
 *
 *  Created on: Feb 15, 2021
 *      Author: dmounday
 */

#ifndef SRC_CONFIGGLOBAL_H_
#define SRC_CONFIGGLOBAL_H_
#include <memory>
#include <iostream>
#include <string>
#include "plog/Log.h"
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "GblData.h"


namespace pentair_control {
/**
 * @brief ConfigGobal is a temporaty wrapper that creates equipment configuration as
 * defined by the configurtion file and the scheduling from the schedule file. The
 * configuraiton and scheduing contained in the GblData object.
 * 
 */
class ConfigGlobal {

static inline const std::string LEVELSHIFTER{"LogicLevelShifter"};
static inline const std::string WIRELESSHANDLER{"WirelessHandler"};
static inline const std::string SENSORS{"Sensors"};
static inline const std::string RELAYS{"Relays"};
static inline const std::string REQ_STATES{"RequiredStates"};
static inline const std::string REMOTE_ACCESS{"RemoteAccess"};
static inline const std::string SCHEDULE{"Schedule"};

struct PlogConfig{
  std::string filePath;
  std::size_t fileSz;
  int       fileCnt;
  plog::Severity severity;
  PlogConfig(pt::ptree const& lp, char const* cmdLevel, bool consoleLog){
    try {
      auto logLevel = lp.get<std::string>("Severity", "info").c_str();
      filePath = lp.get("FilePath", "/var/log/poolsmartz/pool.log");
      fileSz = lp.get<std::size_t>("FileSize", 1000000);
      fileCnt = lp.get<int>("FileCount", 2);
      if ( cmdLevel ){
        logLevel = cmdLevel;
      }
      if (!strcmp(logLevel, "none"))
        severity = plog::none;
      else if (!strcmp(logLevel, "fatal"))
        severity = plog::fatal;
      else if (!strcmp(logLevel, "error"))
        severity = plog::error;
      else if (!strcmp(logLevel, "warning"))
        severity = plog::error;
      else if (!strcmp(logLevel, "info"))
        severity = plog::info;
      else if (!strcmp(logLevel, "debug"))
        severity = plog::debug;
      else if (!strcmp(logLevel, "verbose"))
        severity = plog::verbose;
      std::cerr << "Log to "<< filePath;
      static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(filePath.c_str(), fileSz, fileCnt);
      static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
      if ( consoleLog )
        plog::init(severity, &fileAppender).addAppender(&consoleAppender);
      else
        plog::init(severity, &fileAppender);
    } catch (pt::ptree_error& e){
      std::cerr << "Logging property error: "<< e.what()<< '\n';
      exit(EXIT_FAILURE);
    }
  }
};

public:
/*
 * ConfigGlobal is a temporary wrapper around the functions that initialize the
 * GblData from the configuration properties and the run properties (scheduling).
 */

/**
 * @brief Construct a new Config Global object
 * ConfigGlobal is a temporary wrapper around the functions that initialize the
 * GblData from the configuration properties and the run properties (scheduling).
 * 
 * @param configFile path to the configuration file.
 * @param runSchedFile path to the schdule file.
 * @param severity logging severity level.
 * @param consoleLog if true configure logging to console.
 */
  ConfigGlobal (GblData&,
                const char* configFile,
                const char* runSchedFile,
                const char* severity,
                bool consoleLog );

private:
  GblData& gD_;
  /**
    * Read configuration file and construct the relay and sensor
    * objects.
    * @param config_file
    */
  void EquipConfig(const pt::ptree&);
  void StateConfig(const pt::ptree&);
  void SensorConfig(const pt::ptree& );
  void RelayConfig(const pt::ptree&);
  void RemoteAccessConfig(const pt::ptree&);
  /**
    * Read the runtime file that specifies the scheduling and
    * variable equipment configuration (i.e. pump speed, on/off temps, ...).
    * @param run_file
    */
   bool RunConfig(const std::string& schedFile);

};

} /* namespace SwitchTiming */

#endif /* SRC_CONFIGGLOBAL_H_ */
