#ifndef FLY_OBJ_H
#define FLY_OBJ_H

#include <Vectors.h>

class Flying_Object
{
private:
  int     	arrival_time;
  Vectors 	displacement;
  Vectors 	velocity;

public:
  Flying_Object(void);
  Flying_Object(int arrival_time, Vectors displacement, Vectors velocity);

  // Getters
  virtual int               Get_arrival_time(void)  const;
  virtual const Vectors&    Get_displacement(void)  const;
  virtual const Vectors&    Get_velocity(void)      const;

  virtual void Start_thread(void);
  virtual void Join(void);

  virtual Flying_Object* PSR_ping_response(void);
  virtual Flying_Object* SSR_ping_response(void);

  virtual                ~Flying_Object(void);
};

#endif
