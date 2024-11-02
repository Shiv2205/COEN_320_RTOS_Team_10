#ifndef AIRCRAFT_H
#define AIRCRAFT_H

/*Includes*/
#include <iostream>


/*Defines*/
#define NEWLINE       "\n"
#define NEWLINE_TAB   "\n\t"


/*Types*/
struct Vectors
{
  int   x;
  int   y;
  int   z;

  // Default constructor
  Vectors():
    x(0), y(0), z(0) {}

  // Parameterized constructor
  Vectors(int x_val, int y_val, int z_val):
    x(x_val), y(y_val), z(z_val){}

};


/*Classes*/
class Aircraft
{
private:
  int             arrival_time;
  std::string     aircraft_id;
  Vectors         displacement;
  Vectors         velocity;
  
public:

  //Constructor
  Aircraft();
  //Parametrized Constructor
  Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity);

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

  //Destructor
  ~Aircraft();

  friend std::ostream& operator<<(std::ostream& cout, const Aircraft& aircraft_ref);
};

#endif
