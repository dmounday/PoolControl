/*
 * main.cpp
 *
 *  Created on: Jan 19, 2021
 *      Author: dmounday
 */
#include <iostream>
#include "plog/Log.h"
#include "GblData.h"


namespace st = pentair_control;

int main (int argc, char *argv[]) {

  if (argc < 3) {
    std::cerr
        << "Usage: PoolControllerRPi" <<
        " <equip-config.json> <run-file.json> [fatal|warning|info|none|error|debug|verbose] [console]\n";
    return 1;
  }
  try {
    //boost::asio::io_context ioc;
    st::GblData gblData;
    bool consoleLog = argc == 5 ? !strcmp (argv[4], "console") : false;
    gblData.Configure(argv[1], argv[2], argc >= 4 ? argv[3] : nullptr,
                     consoleLog);
    gblData.Run();

  } catch (std::exception &e) {
    std::cerr << "Terminate with exception: " << e.what () << std::endl;
  }
  return 0;
}



