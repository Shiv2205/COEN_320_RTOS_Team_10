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

#define LOW_TRAFFIC     "0,A1,10000,20000,15000,250,300,-20\n5,A2,30000,40000,15000,200,-250,15\n10,A3,50000,60000,16000,-150,250,-10"


/*Inlcudes*/
#include <iostream>
#include <fstream>


/*Namespaces*/
namespace Parser
{
  //Main Parse functions
  void Parse(void);
  void Parse(std::string file_path);

  //Create file if it does not exist
  void Handle_missing_file(const std::string& file_path, std::ifstream& reader);
}


#endif
