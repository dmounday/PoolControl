/*
 * GblDataImpl.h
 *
 *  Created on: Feb 16, 2021
 *      Author: dmounday
 */

#ifndef SRC_GBLDATAIMPL_H_
#define SRC_GBLDATAIMPL_H_
#include "ConfigGlobal.h"
#include "WirelessHandler.h"
#include "EquipmentBase.h"
#include "SensorDope.h"
#include "ConfigScheduling.h"
#include "JsonHandler.h"
#include "LogicLevelShifter.h"
#include "RemoteAccess.h"
namespace pentair_control {

class GblDataImpl {
public:
  GblDataImpl ();
  void Configure (GblData &gData, const char *configFile,
                  const char *runSchedFile, const char *severity,
                  bool consoleLog);
  EquipmentPtr Sensor(std::string const& id) const;
  EquipmentPtr Equip(std::string const& id) const;
  inline Equipment const& AllEquipment() const {return equipment_;};
  inline std::shared_ptr<RemoteAccess> GetRemoteAccess() const
      {return remoteAccess_;};
  inline pt::ptree& RunProperties(){return runProps_;};
  inline boost::asio::io_context& IOC()
  { return ioc_;};
  float GetSensorValue(std::string const& id) const;

  inline void
  SetLogicShifter(std::shared_ptr<LogicLevelShifter> ls){ logicShifter_ = ls;};
  inline void
  SetWirelessHandler(std::shared_ptr<WirelessHandler> wh){wirelessHandler_ = wh;};
  inline void
  SetSensorDope(std::shared_ptr<SensorDope> sd){sensorDope_ = sd;};

  inline void
  SetRemoteAccess( std::shared_ptr<RemoteAccess> ra){remoteAccess_ =ra;};

  inline void
  SetSchedConfig( std::shared_ptr<ConfigScheduling> sc){schedConfig_ = sc;};

  inline ConfigScheduling&
  Scheduling()const {
    return *schedConfig_;
  }
  inline void
  AddEquipment(std::string const& id, std::shared_ptr<EquipmentBase> ep ){
    equipment_[id] = ep;
  }
  inline void
  EnableLogicShifter(){logicShifter_->EnableShifter();};

  void SetScheduleFile(const char* fileName);
  void SaveSchedules() const;
  void Run();
private:
  boost::asio::io_context ioc_;
  boost::asio::signal_set signals_;
  std::shared_ptr<SensorDope> sensorDope_;
  std::shared_ptr<RemoteAccess> remoteAccess_;
  std::shared_ptr<ConfigScheduling> schedConfig_;
  std::shared_ptr<LogicLevelShifter> logicShifter_;  // +3.3v -> 5V shifter enable
  std::shared_ptr<WirelessHandler> wirelessHandler_;
  pt::ptree runProps_;
  std::string schedFile_;   // run properties file name
  Equipment equipment_;
  void DoWaitStop();
  void StartEquipment();
  void StopEquipment();
};

} /* namespace pentair_control */

#endif /* SRC_GBLDATAIMPL_H_ */
