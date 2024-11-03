#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>


#define TAB         "\t\t"
#define SPACE       " "


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

  //Display
  friend std::ostream& operator<<(std::ostream& cout, const Vectors& vector_data)
  {
    return cout << "{"                    << SPACE
                << "X: " << vector_data.x << TAB
                << "Y: " << vector_data.y << TAB
                << "Z: " << vector_data.z << SPACE
                << "}";
  }

};


#endif
