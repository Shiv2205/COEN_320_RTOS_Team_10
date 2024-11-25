#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <vector>     //dynamic array
#include <Vectors.h>
#include <Aircraft.h>
#include <time.h>
#include <sys/siginfo.h>

/*Types*/
struct Timer
{
  timer_t             timer_id;
  struct itimerspec   timer_specs;
  struct sigevent     timer_event_config;
};


class Airspace
{
private:
  static pthread_attr_t airspace_thread_attr;

  Vectors                       dimensions;
  std::vector<Flying_Object>    UFO_queue;
  std::vector<Aircraft>         aircraft_queue;
  std::vector<Aircraft>&        aircraft_schedule;
  Timer                         airspace_timer;
  pthread_t                     airspace_thread;

  static void* Thread_routine(void* airspace_obj_ptr);

public:
  Airspace(std::vector<Aircraft>& aircraft_schedule);
  ~Airspace(void);
};

#endif
