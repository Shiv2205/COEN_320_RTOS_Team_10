#include <iostream>
#include <stdlib.h>
#include <Parser.h>
#include <Aircraft.h>
#include <Aliases.h>
#include <CheckforSeparation.h>
#include <unistd.h> //For sleep()
#include <thread>
#include "operatorconsole.h"

using namespace std;

int main()
{
  Aircraft_T::Tuple_Vector  aircraft_data;
  std::vector<Aircraft>     aircraft_threads;


  aircraft_data = Parser::Parse();//Parse the file and extract aircraft data
  for (auto& tuple : aircraft_data) {
      aircraft_threads.emplace_back(tuple);
      aircraft_threads.back().Start_thread();
  }


  //sleep(10);

  for (auto& aircraft : aircraft_threads) {
      aircraft.Join();  // Join thread on the actual object
  }


  // Define a separation threshold for violations (e.g., 5.0 units)
     double separation_threshold = 5.0;
     CheckforSeparation checkForSeparation(separation_threshold);

     // Create some aircraft
     Aircraft aircraft1(1, "AC001", Vectors(0, 0, 0), Vectors(1, 1, 1));
     Aircraft aircraft2(2, "AC002", Vectors(3, 3, 3), Vectors(-1, -1, -1));
     Aircraft aircraft3(3, "AC003", Vectors(6, 0, 0), Vectors(0, 1, 1));

     // Add aircraft to the separation check system
     checkForSeparation.AddAircraft(aircraft1);
     checkForSeparation.AddAircraft(aircraft2);
     checkForSeparation.AddAircraft(aircraft3);

     // Check for any separation violations
     checkForSeparation.CheckforViolations();

    thread operatorConsoleThread(OperatorConsole,ref(aircraft_threads));
    thread dataDisplayThread(DataDisplaySystem,ref(aircraft_threads));

    for (auto& aircraft : aircraft_threads) {
           aircraft.Join();
       }
     //wait till threads finish
     operatorConsoleThread.join();
     dataDisplayThread.join();


  std::cout << "Finished" << std::endl;
  return EXIT_SUCCESS;
}
