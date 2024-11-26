#ifndef AIRCRAFT_H
#define AIRCRAFT_H

/*Includes*/
#include <iostream>
#include <tuple>
#include <cmath>
#include <pthread.h>
#include <Vectors.h>
#include <Aliases.h>
#include <Flying_Object.h>
#include <Timer.h>


/*Defines*/
#define NEWLINE   "\n"
#define X_BOUND   100000
#define Y_BOUND   100000
#define Z_BOUND   25000


/*Classes*/
class Aircraft: public Flying_Object
{
private:
  static pthread_mutex_t aircraft_mutex;
  static bool            is_mutex_init;
  static int             thread_count;

  int             arrival_time;
  std::string     aircraft_id;
  Vectors         displacement;
  Vectors         velocity;
  bool            update_position;

  Vectors         entry_point;

  pthread_t       aircraft_thread;
  pthread_attr_t  aircraft_thread_attr;
  Timer           aircraft_timer;

  static void  Timer_handler(union sigval event);
  static void  Mutex_init(void);

public:
  static int current_time;

  // Constructor
  Aircraft();
  // Parametrized Constructor
  Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity);
  // Tuple Constructor
  Aircraft(Aircraft_T::Tuple& aircraft_tuple);

  // Getters
  std::string       Get_aircraft_id(void)   	const;
  int               Get_arrival_time(void)  	const override;
  const Vectors&    Get_displacement(void)  	const override;
  const Vectors&    Get_velocity(void)      	const override;
  bool              Is_update_position(void)  const;

  // Setters
  void Set_arrival_time(int arrival_time);
  void Set_aircraft_id(std::string aircraft_id);
  void Set_displacement(Vectors displacement);
  void Set_velocity(Vectors velocity);
  void Set_update_position(bool update_position);

  bool Is_out_of_bound(void);

  // Thread Specific
  static void* Thread_routine(void* aircraft_obj_ptr);
  static void  Mutex_destroy(void);
  void         Start_thread(void)   override;
  void         Join(void)           override;

  // Radar functions
  Flying_Object* PSR_ping_response(void) override;
  Flying_Object* SSR_ping_response(void) override;

  // Destructor
  ~Aircraft(void) override;

  friend std::ostream& operator<<(std::ostream& cout, const Aircraft& aircraft_ref);
};


#endif
