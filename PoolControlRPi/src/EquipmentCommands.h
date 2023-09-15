/*
 * EquipmentCommands.h
 *
 *  Created on: Jul 28, 2020
 *      Author: dmounday
 */

#ifndef SRC_EQUIPMENTCOMMANDS_H_
#define SRC_EQUIPMENTCOMMANDS_H_
#include <string>
#include <boost/utility/string_view.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "RelaySwitcher.h"
#include "ConfigScheduling.h"

namespace pentair_control {
//
// 
/**
 * @brief Class handles commands from the web interface to change the state of equipment.
 * 
 */
class EquipmentCommands {

	std::string equip_name;
	std::string command;

public:
/**
 * @brief Construct a new Equipment Commands object
 * 
 * @param path Path in request URI.
 * @param json containing equipment name and command. {"Set":{"MainPump": "off"}}
 */
	EquipmentCommands(boost::string_view path, boost::string_view json);
  /**
   * @brief Run command from JSON string.
   * 
   * @param equipment 
   * @return true command executed.
   * @return false error - bad equipment name, bad command.
   */
	bool RunCommand(Equipment equipment);
};

} /* namespace pentair_control */

#endif /* SRC_EQUIPMENTCOMMANDS_H_ */
