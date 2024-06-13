/*
 * GblData.h
 *
 *  Created on: Feb 12, 2021
 *      Author: dmounday
 */

#ifndef SRC_ROOTDATA_H_
#define SRC_ROOTDATA_H_
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include "EquipmentBase.h"


namespace pentair_control {
namespace pt = boost::property_tree;
class GblDataImpl;
class WirelessHandler;
class SensorDope;
class ConfigScheduling;
class RemoteAccess;
class LogicLevelShifter;

/**
 * @brief GblData is a pimpl interface to the GblDataImpl class that contains the
 * global equipment configuration and scheduling.
 * 
 */
class GblData {
public:
/**
 * @brief Construct a new Gbl Data object and the GblDataImpl class.
 * 
 */
  GblData ();
  /**
   * @brief Read the configuration and scheduling files and set logging severity.
   * 
   * @param configFile 
   * @param runSchedFile 
   * @param severity 
   * @param consoleLog 
   */
  void Configure (const char* configFile,
                  const char* runSchedFile,
                  const char* severity,
                  bool consoleLog );
  /**
   * @brief Get equipment pointer by ID.
   * 
   * @param id 
   * @return EquipmentPtr 
   */
  EquipmentPtr Sensor(std::string const& id) const;
  /**
   * @brief Get the Sensor Value by id.
   * 
   * @param id 
   * @return float 
   */
  float GetSensorValue(std::string const& id) const;
  /**
   * @brief Get equipment pointer by id.
   * 
   * @param id 
   * @return EquipmentPtr 
   */
  EquipmentPtr Equip(std::string const& id) const;
  /**
   * @brief Get map of equipment pointers.
   * 
   * @return Equipment const& 
   */
  Equipment const& AllEquipment() const;
  /**
   * @brief Get the Remote Access pointer to RemoteAccess object.
   * 
   * @return std::shared_ptr<RemoteAccess> 
   */
  std::shared_ptr<RemoteAccess> GetRemoteAccess() const;
  /**
   * @brief Get reference to io_context object
   * 
   * @return boost::asio::io_context& 
   */
  boost::asio::io_context& IOC()const;
  /**
   * @brief Get reference to RunProperties that contains schedule.
   * 
   * @return pt::ptree& 
   */
  pt::ptree& RunProperties() const;

  ConfigScheduling& Scheduling()const;
  void
  SetLogicShifter (std::shared_ptr<LogicLevelShifter> ls);

  void
  SetWirelessHandler(std::shared_ptr<WirelessHandler>);

  std::shared_ptr<WirelessHandler> GetWirelessHandler();
  void
  SetSensorDope (std::shared_ptr<SensorDope> sd);
  void
  SetRemoteAccess (std::shared_ptr<RemoteAccess> ra);
  void
  SetSchedConfig (std::shared_ptr<ConfigScheduling> sc);
  void
  AddEquipment (std::string const &id, std::shared_ptr<EquipmentBase> ep);
  void
  EnableLogicShifter ();
  void SetRunScheduleFile(const char* name);
  /**
   * @brief Save the schedule into a file.
   * 
   */
  void SaveSchedules()const;
  void StartEquipment();
  /**
   * Start equipment and scheduling.
   */
  void Run();

private:
  std::shared_ptr<GblDataImpl> pimpl;

};

} /* namespace pentair_control */

#endif /* SRC_ROOTDATA_H_ */
