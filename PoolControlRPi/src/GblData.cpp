/*
 * GblData.cpp
 *
 *  Created on: Feb 12, 2021
 *      Author: dmounday
 */

#include "GblData.h"
#include "GblDataImpl.h"

namespace pentair_control {


GblData::GblData () :
    pimpl { std::make_shared<GblDataImpl>() } {
}
void GblData::Configure (const char* configFile,
                            const char* runSchedFile,
                            const char* severity,
                            bool consoleLog ) {
  pimpl->Configure(*this, configFile, runSchedFile, severity, consoleLog);
}
EquipmentPtr GblData::Sensor (std::string const &id) const {
  return pimpl->Sensor (id);
}

EquipmentPtr GblData::Equip (std::string const &id) const {
  return pimpl->Equip (id);
}
float
GblData::GetSensorValue(std::string const& id) const {
  return pimpl->GetSensorValue(id);
}
Equipment const&
GblData::AllEquipment () const {
  return pimpl->AllEquipment ();
}
boost::asio::io_context&
GblData::IOC ()const{
  return pimpl->IOC ();
}
ConfigScheduling&
GblData::Scheduling()const {
  return pimpl->Scheduling();
}
std::shared_ptr<RemoteAccess>
GblData::GetRemoteAccess() const {
  return pimpl->GetRemoteAccess();
}

void GblData::SetLogicShifter (std::shared_ptr<LogicLevelShifter> ls) {
  pimpl->SetLogicShifter (ls);
}
void
GblData::SetWirelessHandler(std::shared_ptr<WirelessHandler> wh){
  pimpl->SetWirelessHandler(wh);};

std::shared_ptr<WirelessHandler> GblData::GetWirelessHandler(){
  return pimpl->GetWirelessHandler();
}
void GblData::SetSensorDope (std::shared_ptr<SensorDope> sd) {
  pimpl->SetSensorDope (sd);
}
void GblData::SetRemoteAccess (std::shared_ptr<RemoteAccess> ra) {
  pimpl->SetRemoteAccess (ra);
}
void GblData::SetSchedConfig (std::shared_ptr<ConfigScheduling> sc) {
  pimpl->SetSchedConfig (sc);
}
void GblData::AddEquipment (std::string const &id,
                            std::shared_ptr<EquipmentBase> ep) {
  pimpl->AddEquipment (id, ep);
}
void GblData::EnableLogicShifter () {
  pimpl->EnableLogicShifter ();
}
pt::ptree& GblData::RunProperties()const{
  return pimpl->RunProperties();
}
void GblData::SetRunScheduleFile(const char* name){
  pimpl->SetRunScheduleFile(name);
}
void GblData::SaveSchedules() const{
  pimpl->SaveSchedules();
}
void GblData::Run(){
  pimpl->Run();
}

} /* namespace pentair_control */
