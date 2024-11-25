#ifndef FLY_OBJ_H
#define FLY_OBJ_H

#include <Vectors.h>

class Flying_Object
{
public:

  // Getters
  virtual int         Get_arrival_time(void)  const = 0;
  virtual Vectors     Get_displacement(void)  const = 0;
  virtual Vectors     Get_velocity(void)      const = 0;

  virtual Flying_Object* PSR_ping_response(void) = 0;
  virtual Flying_Object* SSR_ping_response(void) = 0;
  virtual                ~Flying_Object()        = default;
};

#endif
