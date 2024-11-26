#include <iostream>
#include <string>
#include <stdlib.h>
#include <Parser.h>
#include <Aircraft.h>
#include <Airspace.h>
#include <Aliases.h>
#include <Timer.h>
#include <CheckforSeparation.h>
#include <unistd.h> //For sleep()
#include <thread>
#include "operatorconsole.h"

//using namespace std;
static void Timer_handler(union sigval event);

int main ()
{
  Aircraft_T::Tuple_Vector  aircraft_data;
  std::vector<Aircraft>     aircraft_threads;
  Timer                     ATC_timer;

  ATC_timer.Set_timer_event_config(Timer_handler, &aircraft_threads);
  ATC_timer.Set_timer_specs(1, 1);
  ATC_timer.Create_timer();

  aircraft_data = Parser::Parse(Traffic::LOW); //Parse the file and extract aircraft data

  ATC_timer.Start_timer();
  auto tuple_itr = aircraft_data.begin();
  while(aircraft_data.end() != tuple_itr)
  {
    if(Aircraft::current_time >= std::get<0>(*tuple_itr))
    {
      aircraft_threads.emplace_back(*tuple_itr);
      aircraft_threads.back().Start_thread();
      std::cout << "Current time: " << Aircraft::current_time
                    << "Arrival time: " << std::get<0>(*tuple_itr) <<
          std::endl;

      tuple_itr++;
    }
    usleep(25000);
  }



  sleep(15);

//  for (auto &aircraft : aircraft_threads)
//  {
//    aircraft.Join();  // Join thread on the actual object
//  }

//  // Define a separation threshold for violations (e.g., 5.0 units)
//  double separation_threshold = 5.0;
//  CheckforSeparation checkForSeparation (separation_threshold);
//
//  // Create some aircraft
//  Aircraft aircraft1 (1, "AC001", Vectors (0, 0, 0), Vectors (1, 1, 1));
//  Aircraft aircraft2 (2, "AC002", Vectors (3, 3, 3), Vectors (-1, -1, -1));
//  Aircraft aircraft3 (3, "AC003", Vectors (6, 0, 0), Vectors (0, 1, 1));
//
//  // Add aircraft to the separation check system
//  checkForSeparation.AddAircraft (aircraft1);
//  checkForSeparation.AddAircraft (aircraft2);
//  checkForSeparation.AddAircraft (aircraft3);
//
//  // Check for any separation violations
//  checkForSeparation.CheckforViolations ();
//
//  thread operatorConsoleThread (OperatorConsole, ref (aircraft_threads));
//  thread dataDisplayThread (DataDisplaySystem, ref (aircraft_threads));
//
//  //wait till threads finish
//  operatorConsoleThread.join ();
//  dataDisplayThread.join ();
//
  for (auto &aircraft : aircraft_threads)
  {
    aircraft.Join ();
  }

  //Cleanup
  Aircraft::Mutex_destroy();

  std::cout << "Finished" << std::endl;
  return EXIT_SUCCESS;
}

void Timer_handler(union sigval event)
{
  std::vector<Aircraft>* aircraft_threads = static_cast<std::vector<Aircraft>*>(event.sival_ptr);

  Aircraft::current_time++;

  for(Aircraft aircraft : *aircraft_threads)
  {
    aircraft.Set_update_position(true);
  }
}
