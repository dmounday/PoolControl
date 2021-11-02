/*
 * SensorTests.cpp
 *
 *  Created on: Oct 30, 2021
 *      Author: dmounday
 */
#define CATCH_CONFIG_MAIN
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "WirelessSensors.h"
#include <catch2/catch.hpp>
namespace pt = boost::property_tree;
using namespace pentair_control;

TEST_CASE("RTSensor Tests", "[main]")
{
  RTSensor sensor{709, "WC", "PoolTemp", 0.0};
  CHECK( sensor.SensorID() == "WC");
  CHECK( sensor.SensorLabel() == "PoolTemp");
  sensor.Update(": 25.50 SS:-20");
  CHECK( sensor.LastSample() == 25.50);
}
TEST_CASE("Sensor Tests", "[main]")
{
  std::string WIRELESS{"Wireless"};
  std::string SENSORS{"Sensors"};
  std::string configFile{"configtest.json"};
  pt::ptree configProps;
  pt::read_json (configFile, configProps); // parse config_file as json
  const auto& sensors = configProps.get_child (SENSORS);
  const auto &wirelessProp = sensors.get_child (WIRELESS);
  auto ws = WirelessSensors(nullptr, WIRELESS, wirelessProp);

  std::string t1{"[790] WC:27.00 SS:-29"};
  ws.Update(t1);
  float c = ws.GetSensorValue("WC");
  CHECK( c == Approx(27.0));

}



