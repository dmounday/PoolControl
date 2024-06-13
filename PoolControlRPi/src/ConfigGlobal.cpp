/*
 * ConfigGlobal.cpp
 *
 *  Created on: Feb 15, 2021
 *      Author: dmounday
 */

#include "ConfigGlobal.h"

#include "LogicLevelShifter.h"
#include "MomentarySwitch.h"
#include "RemoteAccess.h"
#include "SensorDope.h"
#include "WirelessHandler.h"

namespace pentair_control {

ConfigGlobal::ConfigGlobal(GblData &gData, const char *configFile,
                           const char *schedFile, const char *severity,
                           bool consoleLog) : gD_{gData} {
  // open config and schedule files.
  std::ifstream cfin(configFile, std::ios_base::in);
  if (!cfin.is_open()) {
    std::cerr << "Unable to open " << configFile << '\n';
    exit(99);
  }
  std::ifstream schedIn(schedFile, std::ios_base::in);
  if (!schedIn.is_open()) {
    std::cerr << "Unable to open " << schedFile << '\n';
    exit(99);
  }
  gData.SetRunScheduleFile(schedFile);
  std::string runFile;
  try {
    pt::ptree configProps;
    pt::read_json(cfin, configProps);  // parse config_file as json
    runFile = configProps.get<std::string>(SCHEDULEFILE);
    PlogConfig(configProps.get_child(LOGGING), severity, consoleLog);
    PLOG(plog::info) << "Program Start ---";
    if ( !EquipConfig(configProps) ){
      exit(99);
    }
    gD_.SetRunScheduleFile(runFile.c_str());  // from config file.
    if (!RunConfig(schedFile, runFile)) {
      PLOG(plog::error) << "Corrupt or missing schedule file\n";
      exit(99);
    }
  } catch (pt::json_parser_error &e) {
    std::cerr << "Config file Parsing error: " << e.what();
    exit(99);
  }
}

bool ConfigGlobal::EquipConfig(const pt::ptree &tree) {
  PLOG(plog::debug);
  std::exception_ptr eptr;
  try {
    gD_.SetLogicShifter(
        std::make_shared<LogicLevelShifter>(tree.get_child(LEVELSHIFTER)));
    try {
      auto wirelessHdlrNode = tree.get_child(WIRELESSHANDLER);
      auto wirelessHdlr =
          std::make_shared<WirelessHandler>(gD_.IOC(), wirelessHdlrNode);
      gD_.SetWirelessHandler(wirelessHdlr);
    } catch (pt::ptree_bad_path) {
      gD_.SetWirelessHandler(nullptr);
    }

    auto sdp =
        std::make_shared<SensorDope>(gD_, tree.get_child(SENSORS));
    gD_.SetSensorDope(sdp);

    auto const &relays = tree.get_child(RELAYS);
    RelayConfig(relays);
    auto const &reqStates = tree.get_child(REQ_STATES);
    StateConfig(reqStates);
    // HTTP remote access
    auto const &remote = tree.get_child(REMOTE_ACCESS);
    gD_.SetRemoteAccess(std::make_shared<RemoteAccess>(remote, gD_));
  } catch (pt::ptree_bad_path &e) {
    PLOG(plog::error) << "Config File error: " << e.what();
    return false;
  } catch (...) {
    eptr = std::current_exception();
    return false;
  }
  gD_.EnableLogicShifter();
  return true;
}

void ConfigGlobal::StateConfig(const pt::ptree &required) {
  PLOG(plog::debug);
  try {
    for (const auto &r : required) {
      PLOG(plog::debug) << "RequiredStates: " << r.first;
      auto e = gD_.Equip(r.first);
      auto rs = std::dynamic_pointer_cast<RelaySwitcher>(e);
      rs->RequiredStates(gD_.AllEquipment(), r.second);
    }
  } catch (pt::ptree_error &e) {
    std::cerr << "RequiredState config error: " << e.what() << '\n';
    throw;
  } catch (std::range_error &e) {
    PLOG(plog::error) << "No equipment found:" << e.what();
  }
}
/**
 * Construct MomentarySwitch or RelaySwitcher with name and property sub-treegD_.SetRunScheduleFile(runFile.c_str()); // from config file.
 * such as:
 *
 "Relays": {
 "MainPump":
 {
 "label", "Pump",
 "RelayGPIO": "17",
 "SwitchGPIO": "24",   <- optional push button
 "LEDGPIO": 6
 },
 **/
void ConfigGlobal::RelayConfig(const pt::ptree &relays) {
  PLOG(plog::debug);

  try {
    for (const auto &relay : relays) {
      const auto &r = relay.second;
      std::string label = r.get<std::string>("label");
      unsigned relayGPIO = r.get<unsigned>("RelayGPIO", 0);
      unsigned pilotGPIO = r.get<unsigned>("LEDGPIO", 0);
      unsigned pushButton = r.get<unsigned>("SwitchGPIO", 0);
      if (pushButton == 0) {
        auto switcher = std::make_shared<RelaySwitcher>(relay.first, label, relayGPIO,
                                                        pilotGPIO);
        gD_.AddEquipment(relay.first,
                         std::dynamic_pointer_cast<EquipmentBase>(switcher));
      } else {
        auto switcher = std::make_shared<MomentarySwitch>(relay.first,
                                                          label,
                                                          relayGPIO,
                                                          pushButton,
                                                          pilotGPIO);
        gD_.AddEquipment(relay.first,
                         std::dynamic_pointer_cast<EquipmentBase>(switcher));
      }
    }
  } catch (pt::ptree_error &e) {
    std::cerr << "Relay config error: " << e.what() << '\n';
    throw;
  } catch (std::range_error &e) {
    PLOG(plog::error) << "Unknow equipment switcher:" << e.what();
  }
}

bool ConfigGlobal::RunConfig(const char *schedFile, const std::string &runFile) {
  std::ifstream fs(runFile, std::ios_base::in);
  if (!fs.is_open()) {
    // no run file exists, use static schedule file.
    fs.open(schedFile, std::ios_base::in);
    if (!fs.is_open()) {
      std::cerr << "Unable to open " << schedFile << '\n';
      return false;
    }
  }
  gD_.SetRunScheduleFile(runFile.c_str());  // from config file.
  try {
    pt::read_json(fs, gD_.RunProperties());
  } catch (pt::json_parser_error &e) {
    PLOG(plog::debug) << "Json Parsing error in schedule file: " << e.what();
    return false;
  }
  auto &sched = gD_.RunProperties().get_child(SCHEDULE);
  gD_.SetSchedConfig(std::make_shared<ConfigScheduling>(sched, gD_));
  return true;
}

}  // namespace pentair_control
