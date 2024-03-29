/*
 * JsonHandler.h
 *
 *  Created on: Feb 5, 2021
 *      Author: dmounday
 */

#ifndef SRC_JSONHANDLER_H_
#define SRC_JSONHANDLER_H_
#include <memory>

#include "HTTPServerLib.h"
#include "GblData.h"
#include "EquipmentBase.h"
#include "EquipmentCommands.h"
#include "EquipmentStatus.h"
#include "ConfigScheduling.h"

namespace pentair_control {
/**
 * @brief JsonHandler processes requests in JSON format from HTTP server.
 * 
 */
class JsonHandler: public std::enable_shared_from_this<JsonHandler> {
  static constexpr char CMD_SET[] ="/set";
  static constexpr char CMD_SETSCHED[] = "/setSched";
  static constexpr char CMD_RUNSCHEDULE[] = "/runSchedule";
  static constexpr char REQ_STATUS[]="/status";
  static constexpr char REQ_SCHED[] = "/sched";
  static constexpr char CMD_SETSENSORS[] = "/setSensors";
  static constexpr std::size_t STATUS_LTH = std::char_traits<char>::length(REQ_STATUS);
  static constexpr std::size_t SCHED_LTH = std::char_traits<char>::length(REQ_SCHED);

public:
/**
 * @brief Construct a new Json Handler object with GlbData reference.
 * 
 * @param gD Reference to GblData object.
 */
  JsonHandler (GblData const & gD);
  virtual ~JsonHandler ();
  /**
   * @brief Request handler
   * 
   * @param http::verb a GET or POST.
   * @param path Used as commnad string i.e. /set, /status, ...
   * @param json data for PUT type commands.
   * @return std::string response in JSON format.
   */
  std::string RequestHandler(http::verb, beast::string_view path, beast::string_view);
  std::shared_ptr<JsonHandler> getptr();
private:
  std::string PostHandler(beast::string_view path, beast::string_view json);
  std::string GetHandler(beast::string_view path);
  std::string result_;
  GblData const & gD_;
};

} /* namespace pentair_control */

#endif /* SRC_JSONHANDLER_H_ */
