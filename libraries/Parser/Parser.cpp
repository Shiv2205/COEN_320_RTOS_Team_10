#include <Parser.h>
#include <Debug.h>
using namespace Debug;

/*Global variables*/
Traffic::Level default_traffic = Traffic::Level::MEDIUM;


/*Implementations*/
std::string Traffic::Get_traffic_data(const Traffic::Level& current_traffic)
{
  using Level = Traffic::Level;
  switch(current_traffic)
  {
    case Level::LOW       : return "low.txt"      ;
    case Level::MEDIUM    : return "medium.txt"   ;
    case Level::HIGH      : return "high.txt"     ;
    case Level::OVERLOAD  : return "overload.txt" ;
    default               : return ""             ;
  }
}

Aircraft_T::Tuple_Vector Parser::Parse(void)
{
  return Parser::Parse(default_traffic);
}

Aircraft_T::Tuple_Vector Parser::Parse(Traffic::Level current_traffic)
{
  Aircraft_T::Tuple_Vector    aircraft_data;
  std::ifstream               reader;
  std::string                 line;
  std::string                 file_path;

  file_path = "/tmp/shared/" + Traffic::Get_traffic_data(current_traffic);

  reader.open(file_path, std::ifstream::in);

  //File existence verification
  if(reader.is_open())
  {
    Log("File open");
  }
  else
  {
    std::cout
      << "File not found! Error:" << "\n"
      << strerror(errno)          <<
    std::endl;
  }

  //Parsing
  while(reader.good())
  {
    std::string words[8];

    getline(reader, line);//get line from file
    Parser::Split(line, ',', &words[0]);//Split line into words

    if(EMPTY_STR != words[0])//Check if there are words
    {
      //Turn the words into a tuple and Push the tuples into an array
      aircraft_data.push_back(Parser::Line_to_tuple(&words[0]));
    }
  }

  reader.close();

  return aircraft_data;
}

void Parser::Split(std::string line, char delim, std::string* words)
{
  int         word_count  = 0;
  std::size_t delim_pos   = line.find(delim);

  while(std::string::npos != delim_pos)
  {
    *(words + word_count) = line.substr(0, delim_pos);

    line = line.substr(delim_pos + 1);

    delim_pos = line.find(delim);
    word_count++;
  }

  if(std::string::npos == delim_pos)
  {
    *(words + word_count) = line.substr(0);
  }
}

Aircraft_T::Tuple Parser::Line_to_tuple(std::string* words)
{
  return std::make_tuple(
      /*Time of arrival*/ std::stoi(*(words + 0), nullptr, 10),
      /*Aircraft ID*/     *(words + 1),
      /*Displacement*/    Vectors(
                                    std::stoi(*(words + 2), nullptr, 10),
                                    std::stoi(*(words + 3), nullptr, 10),
                                    std::stoi(*(words + 4), nullptr, 10)
                                 ),
      /*Velocity*/        Vectors(
                                   std::stoi(*(words + 5), nullptr, 10),
                                   std::stoi(*(words + 6), nullptr, 10),
                                   std::stoi(*(words + 7), nullptr, 10)
                                 )
                        );
}
