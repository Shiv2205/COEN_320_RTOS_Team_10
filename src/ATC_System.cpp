#include <iostream>
#include <stdlib.h>
#include <Parser.h>
#include <Aircraft.h>
#include <Aliases.h>
#include <CheckforSeparation.h>
#include <unistd.h> //For sleep()

int main()
{
  Aircraft_T::Tuple_Vector  aircraft_data;
  std::vector<Aircraft>     aircraft_threads;

  aircraft_data = Parser::Parse();//Parse the file and extract aircraft data

  std::cout << "Parsed " << aircraft_data.size() << " aircraft data." << std::endl;

  if (aircraft_data.empty()) {
      std::cout << "No aircraft data found." << std::endl;
  }
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


     double separation_threshold = 5.0;
     CheckforSeparation checkForSeparation(separation_threshold);


     Aircraft aircraft1(1, "AC001", Vectors(0, 0, 0), Vectors(1, 1, 1));
     Aircraft aircraft2(2, "AC002", Vectors(-1, 1, 0), Vectors(-1, -1, -1));
     Aircraft aircraft3(3, "AC003", Vectors(20, 20, 20), Vectors(0, 1, 1));


     std::cout << "Adding aircraft to the separation system..." << std::endl;
     checkForSeparation.AddAircraft(aircraft1);
     checkForSeparation.AddAircraft(aircraft2);
     checkForSeparation.AddAircraft(aircraft3);

     // Check for any separation violations
     checkForSeparation.CheckforViolations();


  std::cout << "Finished" << std::endl;
  return EXIT_SUCCESS;
}
