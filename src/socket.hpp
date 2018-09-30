/**
 * @file socket.hpp
 */

#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <iostream>
#include <memory>
#include <functional>

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <cstddef>
#include <string>

#include "utils.hpp"

namespace MW{

namespace asio = boost::asio;
namespace http = boost::beast::http;

using boost::asio::ip::tcp;

class Socket : public std::enable_shared_from_this<Socket> {
private:
  tcp::resolver resolver_;
  tcp::socket socket_;
  boost::beast::flat_buffer buff_;
  http::response<http::string_body> res_;
  http::request<http::empty_body> req_;

public:
  explicit Socket(asio::io_service& io):
    resolver_(io),
    socket_(io)
  {}

  void run(const std::string& host, const std::string& port, const std::string& path);

private:
  /**
   * アドレス解決ハンドラ
   */
  void onResolve(const boost::system::error_code& ec, tcp::resolver::results_type results);

  /**
   * コネクトハンドラ
   */
  void onConnect(const boost::system::error_code& ec);

  /**
   * リクエストハンドラ
   */
  void onRequest(const boost::system::error_code& ec, std::size_t nbytes_transferred);

  /**
   * レスポンスハンドラ
   */
  void onResponse(const boost::system::error_code& ec, std::size_t nbytes_transferred);
}; // class Socket

} // namespace MW

#endif // __SOCKET_HPP__
