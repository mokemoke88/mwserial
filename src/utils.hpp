/**
 * utils.hpp
 */

#ifndef __UTILS_HPP__

#include <string>
#include <iostream>
#include <boost/system/error_code.hpp>

#define __UTILS_HPP__

namespace MW
{
inline void fail(const boost::system::error_code &ec, const std::string &what)
{
  std::cerr << "[WARN] " << what << " : " << ec.message() << std::endl;
}

} // namespace MW

#endif // __UTILS_HPP__