#include "Airspace.h"

//Definition of the static member variable
pthread_attr_t Airspace::airspace_thread_attr;

Airspace::Airspace(std::vector<Aircraft>& aircraft_schedule): aircraft_schedule(aircraft_schedule)
{
  this->dimensions        = Vectors(100000, 100000, 25000);
  this->airspace_thread   = 0;
}

Airspace::~Airspace(void)
{

}
