/**
 * @file serialport.hpp
 */

#ifndef __SERIALPORT_HPP__
#define __SERIALPORT_HPP__

#include <memory>
#include <functional>
#include <cstddef>

#include <boost/asio.hpp>

#include <iostream>

namespace MW{

namespace asio = boost::asio;

class SerialPort : public std::enable_shared_from_this<SerialPort> {
  asio::serial_port sp_;
  asio::streambuf buf_;

public:
  explicit SerialPort(asio::io_context& io) :
    sp_(io)
  {}

  void run(const std::string& port);
  void close(void);

private:
  void onRecieve(const boost::system::error_code& ec, std::size_t nbytes_transferred);
};

} // namespace MW

#endif // __SERIALPORT_HPP__
