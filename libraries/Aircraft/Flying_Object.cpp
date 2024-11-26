#include "Flying_Object.h"


Flying_Object::Flying_Object(void)
{
  this->arrival_time  = 0;
  this->displacement  = Vectors(0, 0, 0);
  this->velocity      = Vectors(0, 0, 0);
}

Flying_Object::Flying_Object(int arrival_time, Vectors displacement, Vectors velocity)
{
  this->arrival_time  = arrival_time;
  this->displacement  = displacement;
  this->velocity      = velocity;
}

int Flying_Object::Get_arrival_time () const
{
  return arrival_time;
}

const Vectors& Flying_Object::Get_displacement () const
{
  return displacement;
}

const Vectors& Flying_Object::Get_velocity () const
{
  return velocity;
}

void Flying_Object::Start_thread(void)
{
  std::cout << "Placeholder start" << std::endl;
}

void Flying_Object::Join(void)
{
  std::cout << "Placeholder join" << std::endl;
}

Flying_Object* Flying_Object::PSR_ping_response (void)
{
  return this;
}

Flying_Object* Flying_Object::SSR_ping_response (void)
{
  return this;
}

Flying_Object::~Flying_Object (void)
{
}

