#include <Parser.h>


/*Implementations*/
void Parser::Parse(void)
{
  Parser::Parse(DATA_PATH);
}

void Parser::Parse(std::string file_path)
{
  std::ifstream   reader;
  std::string     line;

  reader.open(file_path, std::ifstream::in);

  while(getline(reader, line))
  {
    std::cout << line << std::endl;
  }
}
