#include <Parser.h>
#include <Debug.h>
using namespace Debug;


/*Defines*/
#if TRAFFIC == LOW
  const std::string traffic_data[] = {
                                        "0,A1,10000,20000,15000,250,300,-20",
                                        "5,A2,30000,40000,15000,200,-250,15",
                                        "10,A3,50000,60000,16000,-150,250,-10"
                                     };

#elif TRAFFIC == MEDIUM
  const std::string traffic_data[] = {
                                        "0,A1,10000,20000,15000,250,300,-20",
                                        "1,A2,30000,40000,14500,200,-250,15",
                                        "3,A3,50000,60000,15500,-150,250,-10",
                                        "5,A4,40000,50000,15000,220,270,5",
                                        "7,A5,60000,70000,16000,-100,200,-15",
                                        "9,A6,35000,45000,14500,150,-300,20",
                                        "11,A7,45000,55000,15500,-180,240,25",
                                        "13,A8,70000,80000,15000,200,-220,10",
                                        "15,A9,25000,35000,16000,-220,200,-5",
                                        "17,A10,15000,25000,14500,300,-200,0"
                                     };
#elif TRAFFIC == HIGH
  const std::string traffic_data[] = {
                                        "0,A1,10000,20000,15000,250,300,-20",
                                        "1,A2,30000,40000,14500,200,-250,15",
                                        "2,A3,50000,60000,15500,-150,250,-10",
                                        "3,A4,40000,50000,15000,220,270,5",
                                        "4,A5,60000,70000,16000,-100,200,-15",
                                        "5,A6,35000,45000,14500,150,-300,20",
                                        "6,A7,45000,55000,15500,-180,240,25",
                                        "7,A8,70000,80000,15000,200,-220,10",
                                        "8,A9,25000,35000,16000,-220,200,-5",
                                        "9,A10,15000,25000,14500,300,-200,0",
                                        "10,A11,11000,21000,15200,260,310,-15",
                                        "11,A12,32000,41000,14800,210,-240,10",
                                        "12,A13,52000,61000,15800,-140,260,-5",
                                        "13,A14,41000,51000,15300,230,280,8",
                                        "14,A15,61000,71000,16200,-90,210,-12",
                                        "15,A16,36000,46000,14800,160,-290,18",
                                        "16,A17,47000,57000,15700,-170,230,22",
                                        "17,A18,72000,82000,15100,190,-210,15",
                                        "18,A19,26000,36000,15900,-210,210,-2",
                                        "19,A20,16000,26000,14800,290,-190,3"
                                     };

#endif

#define TRAFFIC_DATA_SIZE            ((int)(sizeof(traffic_data)/sizeof(traffic_data[0])))


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

  if(reader.is_open())
  {
    Log("File open");
  }
  else
  {
    Parser::Handle_missing_file(file_path, reader);
  }

  while(reader.good())
  {
    getline(reader, line);
    std::cout << line << std::endl;
  }

  reader.close();
}

void Parser::Handle_missing_file(const std::string& file_path, std::ifstream& reader)
{
  std::ofstream   writer;
  int             itr;

  writer.open(file_path, std::ofstream::out);

  for(itr = 0; itr < TRAFFIC_DATA_SIZE; itr++)
  {
    writer << traffic_data[itr] << "\n";
  }

  writer.close();
  reader.open(file_path, std::ifstream::in);
}
