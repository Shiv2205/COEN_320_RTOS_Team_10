#ifndef PARSER_H
#define PARSER_H

/*Inlcudes*/
#include <string>
#include <fstream>
#include <tuple>
#include <vector>     //dynamic array
#include <Vectors.h>  //User defined type
#include <Aliases.h>


/*Defines*/
#define EMPTY_STR       ""


/*Namespaces*/
namespace Traffic
{
  typedef enum
  {
    LOW,
    MEDIUM,
    HIGH,
    OVERLOAD
  } Level;

  //Getters
  std::string Get_traffic_data(const Traffic::Level& current_traffic);

}

namespace Parser
{
  //Main Parse functions
  std::vector<Aircraft_T::Tuple> Parse(void);
  std::vector<Aircraft_T::Tuple> Parse(Traffic::Level current_traffic);

  //Create file if it does not exist
  void Handle_missing_file(const std::string& file_path, std::ifstream& reader);

  //Split line one delimiter to separate line into an array of words
  void Split(std::string line, char delim, std::string* words);

  //Parse the line and return a tuple
  Aircraft_T::Tuple Line_to_tuple(std::string* words);
}


#endif
