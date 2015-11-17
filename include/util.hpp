#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#define DEBUG_MODE true

// Utility structures and debug functions
namespace Util
{
  void startDebugTimer(std::string tag);
  void endDebugTimer(std::string tag);
};

#endif // UTIL_HPP
