#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

namespace Debug
{
  //Basic logging functions
  template <typename T>
  void Log(T log_data);
  void Log(const char* log_data);          //Overload for const char*
  void Log(const std::string& log_data);   //Overload for std::string

  //Error logging function
  void Log_error(void);
}

#endif
