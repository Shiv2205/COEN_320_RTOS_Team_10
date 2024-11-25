#include "Timer.h"

Timer::Timer(void){}

void Timer::Set_timer_event_config(int event_notif_mode, void (*event_handler)(union sigval), void* event_data)
{
  //Initialize sigevent struct
  this->timer_event_config.sigev_notify             = event_notif_mode;
  this->timer_event_config.sigev_notify_function    = event_handler;
  this->timer_event_config.sigev_value.sival_ptr    = event_data;
  this->timer_event_config.sigev_notify_attributes  = nullptr;
}

void Timer::Set_timer_event_config(void (*event_handler)(union sigval), void* event_data)
{
  this->Set_timer_event_config(SIGEV_THREAD, event_handler, event_data);
}

void Timer::Set_timer_specs(int event_start_sec, int event_start_nsec, int event_interval_sec, int event_interval_nsec)
{
  this->timer_specs.it_value.tv_sec       = event_start_sec;
  this->timer_specs.it_value.tv_nsec      = event_start_nsec;
  this->timer_specs.it_interval.tv_sec    = event_interval_sec;
  this->timer_specs.it_interval.tv_nsec   = event_interval_nsec;
}

void Timer::Set_timer_specs(int event_start_sec, int event_interval_sec)
{
  this->Set_timer_specs(event_start_sec, 0,event_interval_sec, 0);
}

int Timer::Create_timer(void)
{
  if(TIMER_FAILURE == timer_create(CLOCK_REALTIME, &this->timer_event_config, &this->timer_id)){
    return TIMER_FAILURE;
  }
  else
  {
    return TIMER_OK;
  }
}

int Timer::Start_timer(void)
{
  if(TIMER_FAILURE == timer_settime(this->timer_id, 0, &this->timer_specs, nullptr)){
    return TIMER_FAILURE;
  }
  else
  {
    return TIMER_OK;
  }
}

int Timer::Delete_timer(void)
{
  if(TIMER_FAILURE == timer_delete(this->timer_id)){
    return TIMER_FAILURE;
  }
  else
  {
    return TIMER_OK;
  }
}

Timer::~Timer(void)
{
  this->Delete_timer();
}
