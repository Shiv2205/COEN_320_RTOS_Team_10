#include "operatorconsole.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <limits>
#include "Aircraft.h"
#include "Parser.h"

using namespace std;

// Declare the mutex
mutex MUTEX;

void OperatorConsole (vector<Aircraft> &aircraft_threads)
{
  string command;
  ofstream logFile("commands.log", ios::app); // Open commands.log in append mode

  while (true)
  {
    string Aircraft_ID;
    double X, Y, Z;

    // ask user for input
    cout
        << "Enter the command in the following order: AircraftID NewX NewY NewZ: ";
    cin >> Aircraft_ID >> X >> Y >> Z;

    // Lock the mutex before accessing shared resources
    lock_guard<mutex> lock(MUTEX);
    bool found = false;

    // Iterate through the aircraft threads
    for (auto &aircraft : aircraft_threads)
    {
      if (aircraft.Get_aircraft_id() == Aircraft_ID)
      {
        //TODO: Implement Update_parameters(x, y, z)
        aircraft.Set_displacement(Vectors(X,Y,Z));
        logFile << "Time: "
            << chrono::system_clock::to_time_t(chrono::system_clock::now())
            << " | " << "Aircraft ID: " << Aircraft_ID << " | New Position: ("
            << X << ", " << Y << ", " << Z << ")\n";
        logFile.flush();
        cout << "Aircraft " << Aircraft_ID << " updated to position (" << X
            << ", " << Y << ", " << Z << ").\n";
        found = true;
        break;
      }
    }

    if (!found)
    {
      cout << "Aircraft ID " << Aircraft_ID << " is not found!!!\n";
      break;  // Exit the while loop if the aircraft ID is not found
    }
  }
}

void DataDisplaySystem (const vector<Aircraft> &aircraft_threads)
{

  // Open the data log file
  ofstream logFile("/tmp/shared/aircraft_data.log", ios::app);

  while (true)
  {
    // Lock  mutex
    lock_guard<mutex> lock(MUTEX);

    // Iterate through each aircraft in the vector
    for (const auto &aircraft : aircraft_threads)
    {
      logFile << "Aircraft ID: " << aircraft.Get_aircraft_id()
          << " | Position: ("
          << aircraft.Get_displacement().x << ", "
          << aircraft.Get_displacement().y << ", "
          << aircraft.Get_displacement().z << ")\n";

    }

    // Sleep for 5 seconds before the next iteration
    this_thread::sleep_for(chrono::seconds(5));
  }
  this_thread::sleep_for(chrono::seconds(5));
}

