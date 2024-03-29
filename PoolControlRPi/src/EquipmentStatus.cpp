/*
 * EquipmentStatus.cpp
 *
 *  Created on: Jul 22, 2020
 *      Author: dmounday
 */

#include "EquipmentStatus.h"
#include "plog/Log.h"
namespace pentair_control {


EquipmentStatus::EquipmentStatus (GblData const &gD, boost::string_view req) {
  Equipment equip = gD.AllEquipment ();
  PLOG(plog::debug) << req;
  // loop thru the equipment list and get status list for each.
  for (auto const& [id, ptr] : equip) {
    pt::ptree unit;  //  contains units state
    StatusList status_list = ptr->GetStatusList ();
    for (auto const &state : status_list) {
      unit.put (state.first, state.second);
    }
    root.add_child (id, unit);
  }

}

std::string
EquipmentStatus::operator()(){
  std::ostringstream os;
  pt::write_json(os, root);
  return os.str();
}
} /* namespace pentair_control */
