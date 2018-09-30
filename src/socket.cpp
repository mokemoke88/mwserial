/**
 * @file socket.cpp
 */

#include "socket.hpp"
#include "utils.hpp"

namespace MW{

namespace asio = boost::asio;
namespace http = boost::beast::http;

using boost::asio::ip::tcp;

/**
 * httpリクエストの発行
 *
 * @param host: ホストアドレス
 * @param port: ホストポート
 * @param path: パス
 */
void Socket::run(const std::string& host, const std::string& port, const std::string& path){
  tcp::resolver::query q(host, port);

  req_.method(http::verb::get);
  req_.target(path);
  req_.set(http::field::host, host);
  req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  
  resolver_.async_resolve(q,
    std::bind(
      &Socket::onResolve,
      shared_from_this(),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
}

/**
 * アドレス解決ハンドラ
 */
void Socket::onResolve(const boost::system::error_code& ec, tcp::resolver::results_type results)
{
  if(ec){
    return fail(ec, "onRecieve()");
  }

  asio::async_connect(socket_, results,
    std::bind(
      &Socket::onConnect,
      shared_from_this(),
      std::placeholders::_1
    )
  );
}

/**
 * コネクトハンドラ
 */
void Socket::onConnect(const boost::system::error_code& ec)
{
  if(ec){
    return fail(ec, "onConnect()");
  }

  http::async_write(socket_,
    req_,
    std::bind(
      &Socket::onRequest,
      shared_from_this(),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );    
}

/**
 * リクエストハンドラ
 */
void Socket::onRequest(const boost::system::error_code& ec, std::size_t nbytes_transferred)
{
  if(ec){
    return fail(ec, "onRequest()");
  }

  http::async_read(socket_,
    buff_,
    res_,
    std::bind(
      &Socket::onResponse,
      shared_from_this(),
      std::placeholders::_1,
      std::placeholders::_2
    )
  );
}

/**
 * レスポンスハンドラ
 */
void Socket::onResponse(const boost::system::error_code& ec, std::size_t nbytes_transferred)
{
  if(ec){
    return fail(ec, "onResponse()");
  }
  std::clog << res_.body().data() << std::endl;
  socket_.shutdown(socket_.shutdown_both);    
}

} // namespace MW
