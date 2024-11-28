#include "Airspace.h"

//Definition of the static member variable
pthread_attr_t      Airspace::airspace_thread_attr;
int                 Airspace::current_time          = 0;

void* Airspace::Thread_routine(void* airspace_obj_ptr)
{
  Airspace* airspace = static_cast<Airspace*>(airspace_obj_ptr);

  std::ofstream writer;
  writer.open("/tmp/shared/airspace.txt", std::ofstream::app);
  //std::cout << *aircraft_ptr << "\n\n" << std::endl;
  writer << "Airspace at time: " << Aircraft::current_time << "\n";
  for(const Aircraft& aircraft : *(airspace->aircraft_queue))
  {
    writer << aircraft << "\n";
  }
  writer << "\n=====================================================================================\n" << "\n";
  writer.close();

  return nullptr;
}

Airspace::Airspace(std::vector<Aircraft>* aircraft_queue): aircraft_queue(aircraft_queue)
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

std::vector<Aircraft>* Airspace::Get_aircraft_queue ()
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
}

void Airspace::Join(void)
{
  pthread_join(this->airspace_thread, nullptr);
  pthread_attr_destroy(&(Airspace::airspace_thread_attr));
}

Airspace::~Airspace(void)
{

}
