#include <iostream>
#include <stdlib.h>
#include <Parser.h>
#include <Aircraft.h>
#include <Aliases.h>
#include <unistd.h> //For sleep()

int main()
{
  Aircraft_T::Tuple_Vector  aircraft_data;
  std::vector<Aircraft>     aircraft_threads;

  aircraft_data = Parser::Parse();//Parse the file and extract aircraft data
  for(auto itr = aircraft_data.begin(); itr != aircraft_data.end(); itr++)
  {
    Aircraft aircraft_obj(*itr);
    aircraft_threads.push_back(aircraft_obj);
    aircraft_obj.Start_thread();
  }

  sleep(10);

  for(auto itr = aircraft_threads.begin(); itr != aircraft_threads.end(); itr++)
  {
    Aircraft aircraft_obj = *itr;
    aircraft_obj.Join();
  }

  std::cout << "Finished" << std::endl;
  return EXIT_SUCCESS;
}
