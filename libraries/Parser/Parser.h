#ifndef PARSER_H
#define PARSER_H

#ifndef DATA_PATH
  #define DATA_PATH "../../test_data/low_traffic.txt"
#endif

/*Inlcudes*/
#include <iostream>
#include <fstream>


/*Namespaces*/
namespace Parser
{
  void Parse(void);
  void Parse(std::string file_path);
}


#endif
