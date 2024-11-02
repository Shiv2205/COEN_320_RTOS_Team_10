#include <Aircraft.h>

Aircraft::Aircraft(void)
{
  this->arrival_time  = 0;
  this->aircraft_id   = "";
  this->displacement  = Vectors(0,0,0);
  this->velocity      = Vectors(0,0,0);
}

Aircraft::Aircraft(int arrival_time, std::string aircraft_id, Vectors displacement, Vectors velocity)
{
  this->arrival_time  = arrival_time;
  this->aircraft_id   = aircraft_id;
  this->displacement  = displacement;
  this->velocity      = velocity;
}

std::ostream& operator<<(std::ostream& cout, const Aircraft& aircraft_ref)
{
  return cout <<
           "Arrival Time: " << aircraft_ref.arrival_time << NEWLINE <<
           "Aircraft ID: "  << aircraft_ref.aircraft_id  << NEWLINE <<
           "Displacement=>"
               <<NEWLINE_TAB<<
                   "X: " << aircraft_ref.displacement.x <<NEWLINE_TAB<<
                   "Y: " << aircraft_ref.displacement.y <<NEWLINE_TAB<<
                   "Z: " << aircraft_ref.displacement.z
               <<  NEWLINE  <<
           "Velocity=>"
               <<NEWLINE_TAB<<
                   "X: " << aircraft_ref.velocity.x <<NEWLINE_TAB<<
                   "Y: " << aircraft_ref.velocity.y <<NEWLINE_TAB<<
                   "Z: " << aircraft_ref.velocity.z
               <<  NEWLINE  <<
         NEWLINE;
}
