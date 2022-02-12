/*
 * WirelessRT.cpp
 *
 *  Created on: Jul 26, 2020
 *      Author: dmounday
 */
#include "plog/Log.h"
//#define DEBUG
#ifdef DEBUG
#define DBG_LOG(x) x
#else
#define DBG_LOG(x)
#endif
#include "WirelessSensors.h"

namespace pentair_control {

WirelessSensors::WirelessSensors(std::shared_ptr<WirelessHandler> wh,
                                 const std::string& name, const pt::ptree& node):
  SensorBase(name), signal_strength_{0}
{
  const auto& sensors = node.get_child("Sensors");
  label = node.get<std::string>("label");
  for (const auto& s: sensors){
    std::string label = s.first;
    const auto& si = s.second;
    int rf_id = si.get<int>("RemoteID");
    std::string prefix = si.get<std::string>("MsgPrefix");
    float correction = si.get<float>("Correction", 0.0);
    PLOG(plog::debug)<< "label:"<< label << " rid:"
        << rf_id << " MsgPrefix:"<< prefix << " Correction: "<< correction;
    sensors_.push_back({rf_id, prefix, label, correction});
  }
  if ( wh )
    wh->RegisterConsumer(this);
}
/**
WirelessSensors::WirelessSensors(const std::string& name, int id, std::vector<RTSensor> sensors):
	EquipmentBase(name),
	wireless_id_{id}, sensors_{sensors}, signal_strength_{0}
{
}
****/
bool WirelessSensors::Consume(const std::string& data){
  return Update(data);
}
bool WirelessSensors::Update (const std::string &data) {
  DBG_LOG(PLOG(plog::debug) << data);
  bool found { false };
  last_reading_ = std::chrono::system_clock::now ();
  auto s = data.find ("SS:");
  if (s != std::string::npos) {
    signal_strength_ = std::stoi (&data[s + 3]);
  }
  s = data.find (']');
  s = data.find_first_not_of (' ', s + 1);
  if (s != std::string::npos) {
    auto e = data.find (':');
    std::string id = data.substr (s, e - s);
    for (auto &sensor : sensors_) {
      DBG_LOG(PLOG(plog::debug) << "id: " << id << " target? " << sensor.SensorID ());
      if (sensor.SensorID () == id) {
        sensor.Update (data.substr (e));
        found = true;
      }
    }
  }
  return found;
}

pentair_control::StatusList
WirelessSensors::GetStatusList(){
  status.push_back(std::make_pair("label", label));
	for ( auto& s: sensors_)
		status.push_back(std::make_pair(s.SensorLabel(),
		                                std::to_string(s.LastSample())));
	std::ostringstream time_str;
	std::time_t t_c = std::chrono::system_clock::to_time_t(last_reading_);
	time_str << std::to_string(t_c); //std::put_time(std::localtime(&t_c), "%F %T");
	status.push_back(std::make_pair("Time", time_str.str() ));
	status.push_back(std::make_pair("Signal", std::to_string( signal_strength_)));
	return status;
}

float
WirelessSensors::GetSensorValue(std::string const &id ) const{
  auto p = std::find_if(std::begin(sensors_), std::end(sensors_),
                        [&id](auto p){ return p.SensorID() ==id;});
  if ( p != std::end(sensors_))
    return p->LastSample();
  return 0.0;
}
SensorIDs
WirelessSensors::GetSensorIDs()
{
  SensorIDs ids;
  for(auto& i: sensors_){
    ids.push_back(&i.SensorLabel());
  }
  return ids;
}
} /* namespace WirelessSerialSensors */
