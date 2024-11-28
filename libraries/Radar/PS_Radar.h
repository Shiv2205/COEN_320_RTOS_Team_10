#ifndef PS_RADAR_H
#define PS_RADAR_H

#include <vector>
#include <pthread.h>
#include <Aircraft.h>

class PS_Radar
{
private:
  std::vector<Aircraft>*   aircraft_threads;

  pthread_t       PSR_thread;
  pthread_attr_t  PSR_thread_attr;

public:
  PS_Radar(void);

  // Thread Specific
  static void* Thread_routine(void* PSR_obj_ptr);
  void         Start_thread(void);
  void         Join(void);

  ~PS_Radar(void);
};

#endif
