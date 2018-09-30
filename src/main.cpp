/**
 * @file main.cpp
 */

#include <iostream>
#include <thread>
#include <memory>
#include <functional>
#include <cstddef>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

#include "socket.hpp"
#include "serialport.hpp"

/**
 * エントリポイント
 */
int main(int argc, char **argv)
{
  namespace asio = boost::asio;

  try{
    asio::io_service io;

    // std::make_shared<MW::Socket>(io)->run("www.seekers.jp", "http", "/");
    std::make_shared<MW::SerialPort>(io)->run("/dev/cu.usbmodem1451");
    
    std::thread th([&io]() {
      io.run();
    });
    th.join();

  }catch(std::exception& e){
    std::cerr << "[FATAL] " << e.what() << std::endl;
  }
  return 0;
}
