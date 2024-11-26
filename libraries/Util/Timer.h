#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <iostream>
#include <time.h>
#include <sys/siginfo.h>

#define TIMER_OK         1
#define TIMER_FAILURE   -1

class Timer
{
private:
  static int timer_count;

  timer_t             timer_id;
  struct itimerspec   timer_specs;
  struct sigevent     timer_event_config;

public:
  Timer(void);

  //Setter
  void Set_timer_event_config(void (*event_handler)(union sigval), void* event_data);
  void Set_timer_event_config(int event_notif_mode, void (*event_handler)(union sigval), void* event_data);

  void Set_timer_specs(int event_start_sec, int event_interval_sec);
  void Set_timer_specs(int event_start_sec, int event_start_nsec, int event_interval_sec, int event_interval_nsec);

  //Timer functions
  int Create_timer(void); //Create the timer
  int Start_timer(void);  //Start  the timer
  int Delete_timer(void); //Delete the timer

  ~Timer(void);
};

#endif
