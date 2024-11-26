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

using namespace std;
static void Timer_handler(union sigval event);

/*Global variables*/
// Define a separation threshold for violations (e.g., 5.0 units)
double separation_threshold = 500.0;
CheckforSeparation checkForSeparation(separation_threshold);

int main ()
{
  Aircraft_T::Tuple_Vector  aircraft_data;
  std::vector<Aircraft>     aircraft_threads;
  Timer                     ATC_timer;

  ATC_timer.Set_timer_event_config(Timer_handler, &aircraft_threads);
  ATC_timer.Set_timer_specs(1, 1);
  ATC_timer.Create_timer();

  aircraft_data = Parser::Parse(Traffic::HIGH); //Parse the file and extract aircraft data

  ATC_timer.Start_timer();

  auto tuple_itr = aircraft_data.begin();
  while(aircraft_data.end() != tuple_itr)
  {
    if(Aircraft::current_time >= std::get<0>(*tuple_itr))
    {
      aircraft_threads.emplace_back(*tuple_itr);
      Aircraft& active_aircraft = aircraft_threads.back();
      checkForSeparation.AddAircraft(active_aircraft);
      active_aircraft.Start_thread();

      tuple_itr++;
    }
    usleep(25000);
  }

  thread operatorConsoleThread (OperatorConsole, ref (aircraft_threads));
  thread dataDisplayThread (DataDisplaySystem, ref (aircraft_threads));

  while(1);

  //wait till threads finish
//  operatorConsoleThread.join ();
//  dataDisplayThread.join ();

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

  if(0 == (Aircraft::current_time % 5))
  {
    // Check for any separation violations
    checkForSeparation.CheckforViolations();
  }

  if(0 == (Aircraft::current_time % 30))
  {
    //log airspace
  }

  for(auto aircraft_itr = (*aircraft_threads).begin(); aircraft_itr != (*aircraft_threads).end(); aircraft_itr++)
  {
    if((*aircraft_itr).Is_out_of_bounds())
    {
      std::cout << "Leaving airspace: \n" << *aircraft_itr << std::endl;
      (*aircraft_itr).Join();
      (*aircraft_threads).erase(aircraft_itr);
      std::cout << "Number of aircrafts still in airspace: " << (*aircraft_threads).size() << std::endl;
    }
    else
    {
      Aircraft::Thread_routine(&(*aircraft_itr));
    }
  }
}
