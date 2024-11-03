#ifndef AIRCRAFT_H
#define AIRCRAFT_H

/*Includes*/
#include <iostream>
#include <tuple>
#include <pthread.h>
#include <Vectors.h>
#include <Aliases.h>


/*Defines*/
#define NEWLINE   "\n"


/*Classes*/
class Aircraft
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

  //Constructor
  Aircraft();
  //Parametrized Constructor
  Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity);
  //Tuple Constructor
  Aircraft(Aircraft_T::Tuple& aircraft_tuple);

  //Getters
  int         Get_arrival_time(void);
  std::string Get_aircraft_id(void);
  Vectors     Get_displacement(void);
  Vectors     Get_velocity(void);

  //Setters
  void Set_arrival_time(int arrival_time);
  void Set_aircraft_id(std::string aircraft_id);
  void Set_displacement(Vectors displacement);
  void Set_velocity(Vectors velocity);

  //Thread Specific
  void Start_thread(void);
  void Join(void);

  //Destructor
  ~Aircraft(void);

  friend std::ostream& operator<<(std::ostream& cout, const Aircraft& aircraft_ref);
};

#endif
