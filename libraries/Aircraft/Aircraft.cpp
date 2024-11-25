#include <Aircraft.h>
#include <Debug.h>


//Definition of the static member variable
pthread_attr_t Aircraft::aircraft_thread_attr;

void* Aircraft::Thread_routine(void* aircraft_obj_ptr)
{
  Aircraft* aircraft_ptr = static_cast<Aircraft*>(aircraft_obj_ptr);

  std::cout << "Aircraft ID: " << aircraft_ptr->aircraft_id << std::endl;

  return nullptr;
}

Aircraft::Aircraft(void)
{
  this->arrival_time    = 0;
  this->aircraft_id     = "";
  this->displacement    = Vectors(0,0,0);
  this->velocity        = Vectors(0,0,0);
  this->aircraft_thread = 0;
}

Aircraft::Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity)
{
  this->arrival_time    = arrival_time;
  this->aircraft_id     = aircraft_id;
  this->displacement    = displacement;
  this->velocity        = velocity;
  this->aircraft_thread = 0;
}

Aircraft::Aircraft(Aircraft_T::Tuple& aircraft_tuple)
{
  this->arrival_time    = std::get<0>(aircraft_tuple);
  this->aircraft_id     = std::get<1>(aircraft_tuple);
  this->displacement    = std::get<2>(aircraft_tuple);
  this->velocity        = std::get<3>(aircraft_tuple);
  this->aircraft_thread = 0;
}

void Aircraft::Start_thread(void)
{
  //Initialize thread attributes
  pthread_attr_init(&(Aircraft::aircraft_thread_attr));

  //Create and start thread
  if(pthread_create(&(this->aircraft_thread),
                    &(Aircraft::aircraft_thread_attr),
                    Aircraft::Thread_routine,
                    this))
  {
    std::cout << "Thread creation failure!" << "/n";
    pthread_attr_destroy(&(Aircraft::aircraft_thread_attr));//Clean up
  }
}

void Aircraft::Join(void)
{
  pthread_join(this->aircraft_thread, nullptr);
  pthread_attr_destroy(&(Aircraft::aircraft_thread_attr));
}

Aircraft::~Aircraft(void)
{
  /*Debug::Log("Aircraft obj destroyed");*/
  //pthread_attr_destroy(&(Aircraft::aircraft_thread_attr));
}
int Aircraft::Get_arrival_time (void) const
{
  return this->arrival_time;
}

std::string Aircraft::Get_aircraft_id (void) const
{
  return this->aircraft_id;
}

Vectors Aircraft::Get_displacement (void) const
{
  return this->displacement;
}

Vectors Aircraft::Get_velocity (void) const
{
  return this->velocity;
}

Flying_Object* Aircraft::PSR_ping_response(void)
{
  return this;
}

Flying_Object* Aircraft::SSR_ping_response(void)
{
  return this;
}

std::ostream& operator<<(std::ostream& cout, const Aircraft& aircraft_ref)
{
  return cout <<
           "Arrival Time: "  << aircraft_ref.arrival_time << NEWLINE <<
           "Aircraft ID: "   << aircraft_ref.aircraft_id  << NEWLINE <<
           "Displacement: "  << aircraft_ref.displacement << NEWLINE <<
           "Velocity:\t\t"   << aircraft_ref.velocity     << NEWLINE <<
         NEWLINE;
}
