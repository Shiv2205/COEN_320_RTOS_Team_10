#ifndef AIRCRAFT_H
#define AIRCRAFT_H

/*Includes*/
#include <iostream>
#include <tuple>
#include <pthread.h>
#include <Vectors.h>
#include <Aliases.h>
#include "Flying_Object.h"


/*Defines*/
#define NEWLINE   "\n"


/*Classes*/
class Aircraft: Flying_Object
{
private:
  static pthread_attr_t aircraft_thread_attr;

  int             arrival_time;
  std::string     aircraft_id;
  Vectors         displacement;
  Vectors         velocity;
  pthread_t       aircraft_thread;
  
  static void* Thread_routine(void* aircraft_obj_ptr);

public:

  // Constructor
  Aircraft();
  // Parametrized Constructor
  Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity);
  // Tuple Constructor
  Aircraft(Aircraft_T::Tuple& aircraft_tuple);

  // Getters
  std::string Get_aircraft_id(void)   const;
  int         Get_arrival_time(void)  const override;
  Vectors     Get_displacement(void)  const override;
  Vectors     Get_velocity(void)      const override;

  // Setters
  void Set_arrival_time(int arrival_time);
  void Set_aircraft_id(std::string aircraft_id);
  void Set_displacement(Vectors displacement);
  void Set_velocity(Vectors velocity);

  // Thread Specific
  void Start_thread(void);
  void Join(void);

  // Radar functions
  Flying_Object* PSR_ping_response(void) override;
  Flying_Object* SSR_ping_response(void) override;

  // Destructor
  ~Aircraft(void) override;

  friend std::ostream& operator<<(std::ostream& cout, const Aircraft& aircraft_ref);
};


#endif
