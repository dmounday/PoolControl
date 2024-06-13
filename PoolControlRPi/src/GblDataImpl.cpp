/*
 * GblDataImpl.cpp
 *
 *  Created on: Feb 16, 2021
 *      Author: dmounday
 */

#include "GblDataImpl.h"

namespace pentair_control {

GblDataImpl::GblDataImpl ():
  ioc_(),
  signals_{ioc_}
{
  // Register to handle the signals that indicate when the server should exit.
    // It is safe to register for the same signal multiple times in a program,
    // provided all registration for the specified signal is made through Asio.
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
    signals_.add(SIGHUP);
  #if defined(SIGQUIT)
    signals_.add(SIGQUIT);
  #endif // defined(SIGQUIT)
    DoWaitStop();
}
void GblDataImpl::Configure(GblData &gData, const char *configFile,
                   const char *runSchedFile, const char *severity,
                   bool consoleLog){
  ConfigGlobal cg{gData, configFile, runSchedFile, severity, consoleLog};
}
EquipmentPtr
GblDataImpl::Sensor(std::string const& id)const
{
  return sensorDope_->Sensor(id);
}

float GblDataImpl::GetSensorValue(std::string const& id) const{
  auto sm =  std::static_pointer_cast<SensorBase>(Sensor(id));
  return sm->GetSensorValue(id);
}

EquipmentPtr
GblDataImpl::Equip(std::string const& id)const
{
  try {
    return equipment_.at(id);
  } catch (std::out_of_range& e){
      PLOG(plog::error)<< id << ": "<< e.what();
      throw(e);
  }
}
void
GblDataImpl::StartEquipment(){
  for ( auto& e: equipment_){
    // Start all equipment objects
    PLOG(plog::debug)<< "Start: "<< e.first;
    e.second->Start();
  }
}
void
GblDataImpl::StopEquipment(){
  for ( auto& e: equipment_){
    // Start all equipment objects
    PLOG(plog::debug)<< "Stop: "<< e.first;
    e.second->Stop(); // Stop also switches off relays
  }
}

void GblDataImpl::SetRunScheduleFile(const char* name){
  runScheduleFile_ = name;
}
void GblDataImpl::SaveSchedules() const{
  std::string fn = runScheduleFile_;
  pt::write_json(fn, runProps_);
}
void
GblDataImpl::Run(){
  StartEquipment();
  PLOG(plog::debug)<< "RunSchedule";
  schedConfig_->RunSchedule();
  PLOG(plog::debug)<< "Start RemoteAccess";
  remoteAccess_->Start();
  ioc_.run();
}
void
GblDataImpl::DoWaitStop(){
  signals_.async_wait(
        [this](boost::system::error_code /*ec*/, int signo)
        {
          PLOG(plog::info)<< "SigNo: "<< signo;
          StopEquipment();
          // The server is stopped by cancelling all outstanding asynchronous
          // operations. Once all operations have finished the io_service::run()
          // call will exit.
          //acceptor_.close();
          //connection_manager_.stop_all();
          ioc_.stop();
          exit(0);
        });
}

} /* namespace pentair_control */
