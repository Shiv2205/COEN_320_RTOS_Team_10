#include <Aircraft.h>
#include <Debug.h>
#include <fstream>

pthread_mutex_t Aircraft::aircraft_mutex;
bool            Aircraft::is_mutex_init = false;
int             Aircraft::thread_count  = 0;
int             Aircraft::current_time  = 0;

void Aircraft::Mutex_init(void)
{
  if(!(Aircraft::is_mutex_init))
  {
    pthread_mutex_init(&Aircraft::aircraft_mutex, nullptr);
    Aircraft::is_mutex_init = true;
  }
}

void Aircraft::Mutex_destroy(void)
{
  if(Aircraft::is_mutex_init)
  {
    pthread_mutex_destroy(&Aircraft::aircraft_mutex);
    Aircraft::is_mutex_init = false;
  }
}

void* Aircraft::Thread_routine(void* aircraft_obj_ptr)
{
  Aircraft* aircraft_ptr = static_cast<Aircraft*>(aircraft_obj_ptr);

  aircraft_ptr->arrival_time = Aircraft::current_time;
  aircraft_ptr->displacement.x += aircraft_ptr->velocity.x;
  aircraft_ptr->displacement.y += aircraft_ptr->velocity.y;
  aircraft_ptr->displacement.z += aircraft_ptr->velocity.z;

  //Critical section
  pthread_mutex_lock(&Aircraft::aircraft_mutex);
    std::ofstream writer;
    writer.open("/tmp/shared/debug.txt", std::ofstream::app);
    //std::cout << *aircraft_ptr << "\n\n" << std::endl;
    writer << *aircraft_ptr << "\n";
    writer.close();
  pthread_mutex_unlock(&Aircraft::aircraft_mutex);


  return nullptr;
}

Aircraft::Aircraft():
  Aircraft(0, "", Vectors(0, 0, 0), Vectors(0, 0, 0)) {}

Aircraft::Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity):
  arrival_time    (arrival_time),
  aircraft_id     (aircraft_id),
  displacement    (displacement),
  velocity        (velocity),
  entry_point     (displacement),
  aircraft_thread (Aircraft::thread_count++)
{
  Aircraft::Mutex_init();
}

Aircraft::Aircraft(Aircraft_T::Tuple& aircraft_tuple):
  Aircraft(
    std::get<0>(aircraft_tuple),
    std::get<1>(aircraft_tuple),
    std::get<2>(aircraft_tuple),
    std::get<3>(aircraft_tuple)
          ) {}

void Aircraft::Set_displacement(Vectors displacement)
{
  this->displacement = displacement;
}

bool Aircraft::Is_out_of_bounds(void)
{
  Vectors distance_travelled;
  distance_travelled.x = this->displacement.x - this->entry_point.x;
  distance_travelled.y = this->displacement.y - this->entry_point.y;
  distance_travelled.z = this->displacement.z - this->entry_point.z;

  if(std::abs(distance_travelled.x) >= std::abs(X_BOUND - this->entry_point.x))
  {
    return true;
  }
  if(std::abs(distance_travelled.y) >= std::abs(Y_BOUND - this->entry_point.y))
  {
    return true;
  }
  if(std::abs(distance_travelled.z) >= std::abs(Z_BOUND - this->entry_point.z))
  {
    return true;
  }

  return false;
}

void Aircraft::Start_thread(void)
{
  //Initialize thread attributes
  pthread_attr_init(&(Aircraft::aircraft_thread_attr));

  //Create and start thread
  if(pthread_create(&(this->aircraft_thread),
                    &(this->aircraft_thread_attr),
                    Aircraft::Thread_routine,
                    this))
  {
    std::cout << "Thread creation failure!" << "/n";
    pthread_attr_destroy(&(Aircraft::aircraft_thread_attr));//Clean up
  }

  std::cout << "Thread count: " << Aircraft::thread_count << std::endl;
}

void Aircraft::Join(void)
{
  pthread_join(this->aircraft_thread, nullptr);
  pthread_attr_destroy(&(this->aircraft_thread_attr));
}

int Aircraft::Get_arrival_time (void) const
{
  return this->arrival_time;
}

std::string Aircraft::Get_aircraft_id (void) const
{
  return this->aircraft_id;
}

const Vectors& Aircraft::Get_displacement (void) const
{
  return this->displacement;
}

const Vectors& Aircraft::Get_velocity (void) const
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

Aircraft::~Aircraft(void)
{

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

