#ifndef AIRSPACE_H
#define AIRSPACE_H

#include <vector>     //dynamic array
#include <fstream>
#include <Vectors.h>
#include <Aircraft.h>
#include <time.h>
#include <sys/siginfo.h>
#include <Timer.h>

class Airspace
{
private:
  static pthread_attr_t     airspace_thread_attr;
  static int                current_time;

  Vectors                       dimensions;
  std::vector<Aircraft>*        aircraft_queue;
  pthread_t                     airspace_thread;

public:
  Airspace(std::vector<Aircraft>* aircraft_schedule);

  //Getters
  const Vectors&               Get_dimensions(void) const;
  std::vector<Aircraft>*       Get_aircraft_queue(void);

  //Setters
  void Set_dimensions(const Vectors &dimensions);

  // Thread Specific
  static void*  Thread_routine(void* airspace_obj_ptr);
  void          Start_thread(void);
  void          Join(void);

  ~Airspace(void);
};

#endif
