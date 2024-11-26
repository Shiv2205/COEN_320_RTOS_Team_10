#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <vector>     //dynamic array
#include <Vectors.h>
#include <Aircraft.h>
#include <time.h>
#include <sys/siginfo.h>
#include <Timer.h>

/*Types*/
enum Task_State
{
  MONITOR,
  UPDATE
};

using Aircraft_Iterator = std::vector<Aircraft>::iterator;

class Airspace
{
private:
  static Aircraft_Iterator  schedule_tracker;
  static pthread_attr_t     airspace_thread_attr;
  static int                current_time;
  static Task_State         airspace_task;

  Vectors                       dimensions;
  std::vector<Flying_Object*>   UFO_queue;
  std::vector<Aircraft*>        aircraft_queue;
  std::vector<Aircraft>&        aircraft_schedule;
  Timer                         airspace_timer;
  pthread_t                     airspace_thread;

  static void   Timer_handler(union sigval event);

public:
  Airspace(std::vector<Aircraft>& aircraft_schedule);

  //Getters
  const Vectors&                Get_dimensions(void) const;
  std::vector<Flying_Object*>&  Get_ufo_queue(void);
  std::vector<Aircraft*>&       Get_aircraft_queue(void);

  //Setters
  void Set_dimensions(const Vectors &dimensions);

  // Thread Specific
  static void*  Thread_routine(void* airspace_obj_ptr);
  void          Start_thread(void);
  void          Join(void);

  ~Airspace(void);
};

#endif
