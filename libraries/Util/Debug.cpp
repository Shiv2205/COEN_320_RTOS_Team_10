#include <Debug.h>

template <typename T>
void Debug::Log(T* log_data)
{
  std::cout << log_data << std::endl;
}

void Debug::Log(const char* log_data)
{
  std::cout << std::string(log_data) << std::endl;
}

//Overload for std::string
void Debug::Log(const std::string& log_data) {
    std::cout << log_data << std::endl;
}

void Debug::Log_error(void)
{
  std::cout << strerror(errno) << std::endl;
}
