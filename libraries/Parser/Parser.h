#ifndef PARSER_H
#define PARSER_H

/*Defines*/
#define LOW             0
#define MEDIUM          1
#define HIGH            2
#define OVERLOAD        3

#ifndef TRAFFIC
  #define TRAFFIC       MEDIUM
#endif

#ifndef DATA_PATH
  #define DATA_PATH     "/tmp/shared/data_traffic.txt"
#endif

#define EMPTY_STR       ""


/*Inlcudes*/
#include <string>
#include <fstream>
#include <tuple>
#include <vector>     //dynamic array
#include <Vectors.h>  //User defined type
#include <Aliases.h>


/*Namespaces*/
namespace Parser
{
  //Main Parse functions
  std::vector<Aircraft_T::Tuple> Parse(void);
  std::vector<Aircraft_T::Tuple> Parse(std::string file_path);

  //Create file if it does not exist
  void Handle_missing_file(const std::string& file_path, std::ifstream& reader);

  //Split line one delimiter to separate line into an array of words
  void Split(std::string line, char delim, std::string* words);

  //Parse the line and return a tuple
  Aircraft_T::Tuple Line_to_tuple(std::string* words);
}


#endif
