#include "Airspace.h"

//Definition of the static member variable
Aircraft_Iterator   Airspace::schedule_tracker;
pthread_attr_t      Airspace::airspace_thread_attr;
int                 Airspace::current_time          = 0;
Task_State          Airspace::airspace_task         = Task_State::MONITOR;

void Airspace::Timer_handler(union sigval event)
{
  Airspace* airspace = static_cast<Airspace*>(event.sival_ptr);

  std::cout << "Airspace X" << std::endl;
  airspace->Thread_routine(airspace);

  sched_yield();
}

void* Airspace::Thread_routine(void* airspace_obj_ptr)
{
  Airspace* airspace = static_cast<Airspace*>(airspace_obj_ptr);

  if ((airspace->aircraft_queue.empty()) && (airspace->UFO_queue.empty()))
  {
    Airspace::schedule_tracker = airspace->aircraft_schedule.begin();
  }

  if ((airspace->aircraft_schedule.end() != Airspace::schedule_tracker) &&
      (Airspace::current_time >= Airspace::schedule_tracker->Get_arrival_time()))
  {
    airspace->UFO_queue.emplace_back(&(*Airspace::schedule_tracker));
    Airspace::schedule_tracker++;
  }

  Airspace::current_time++;
  std::cout << "current time: " << Airspace::current_time << std::endl;

  //Start aircraft threads to update their position
  auto  aircraft_itr  = airspace->aircraft_queue.begin();
  while(airspace->aircraft_queue.end() != aircraft_itr)
  {
    (*aircraft_itr)->Start_thread();
    aircraft_itr++;
  }

  //Wait for aircraft threads to finish
  aircraft_itr  = airspace->aircraft_queue.begin();
  while(airspace->aircraft_queue.end() != aircraft_itr)
  {
    (*aircraft_itr)->Join();
    aircraft_itr++;
  }

  return nullptr;
}

Airspace::Airspace(std::vector<Aircraft>& aircraft_schedule): aircraft_schedule(aircraft_schedule)
{
  this->dimensions        = Vectors(100000, 100000, 25000);
  this->airspace_thread   = 0;
}

void Airspace::Set_dimensions (const Vectors& dimensions)
{
  this->dimensions = dimensions;
}

const Vectors& Airspace::Get_dimensions () const
{
  return dimensions;
}

std::vector<Flying_Object*>& Airspace::Get_ufo_queue ()
{
  return UFO_queue;
}

std::vector<Aircraft*>& Airspace::Get_aircraft_queue ()
{
  return aircraft_queue;
}

void Airspace::Start_thread(void)
{
  //Initialize thread attributes
  pthread_attr_init(&(Airspace::airspace_thread_attr));

  //Create and start thread
  if(pthread_create(&(this->airspace_thread),
                    &(Airspace::airspace_thread_attr),
                    Airspace::Thread_routine,
                    this))
  {
    std::cout << "Thread creation failure!" << "/n";
    pthread_attr_destroy(&(Airspace::airspace_thread_attr));//Clean up
  }

  pthread_setschedprio(this->airspace_thread, 250);

}

void Airspace::Join(void)
{
  pthread_join(this->airspace_thread, nullptr);
  pthread_attr_destroy(&(Airspace::airspace_thread_attr));
}

Airspace::~Airspace(void)
{

}
