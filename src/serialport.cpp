/**
 * @file serialport.cpp
 */

#include <memory>
#include <functional>
#include <cstddef>

#include <boost/asio.hpp>

#include <iostream>

#include "serialport.hpp"

#include "utils.hpp"

namespace MW{

namespace asio = boost::asio;

void SerialPort::run(const std::string& port)
{
  boost::system::error_code ec;
  sp_.open(port, ec);
  if(ec){
    return fail(ec, "run()");
  }
  
  sp_.set_option(asio::serial_port::baud_rate(9600), ec);
  sp_.set_option(asio::serial_port::character_size(8), ec);
  sp_.set_option(asio::serial_port::parity(asio::serial_port::parity::none), ec);
  sp_.set_option(asio::serial_port::stop_bits(asio::serial_port::stop_bits::one), ec);

  asio::async_read_until(sp_, buf_, '\n',
    std::bind(
      &SerialPort::onRecieve,
      shared_from_this(),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
}

void SerialPort::close(void)
{
  if( !sp_.is_open() )
    return;
  sp_.close();
}

void SerialPort::onRecieve(const boost::system::error_code& ec, std::size_t nbytes_transferred)
{
  if(ec)
    return fail(ec, "onRecieve()");

  const std::string data(asio::buffer_cast<const char*>(buf_.data()), nbytes_transferred);
  buf_.consume(nbytes_transferred);

  asio::async_read_until(sp_, buf_, '\n',
    std::bind(
      &SerialPort::onRecieve,
      shared_from_this(),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );

  std::cerr << data;
}

} // namespace MW
