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

void OperatorConsole(vector<Aircraft>& aircraft_threads) {
    string command;
    ofstream logFile("commands.log", ios::app); // Open commands.log in append mode

    while (true) {
        int Aircraft_ID;
        double X, Y, Z;

        // Prompt the user for input
        cout << "Enter the command in the following order: AircraftID NewX NewY NewZ: ";
        cin >> Aircraft_ID >> X >> Y >> Z;

        // Check if the input is valid
        if (!(cin >> Aircraft_ID >> X >> Y >> Z)) {
            cout << "Invalid input. Please enter valid values for AircraftID, X, Y, and Z.\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }

        // Lock the mutex before accessing shared resources
        lock_guard<mutex> lock(MUTEX);
        bool found = false;

        // Iterate through the aircraft threads
        for (auto& aircraft : aircraft_threads) {
            if (aircraft.GetID() == Aircraft_ID) {
                
                // Update the aircraft's parameters
                aircraft.UpdateParameters(X, Y, Z);

                // Log the command to the file
                logFile << "Time: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << " | "
                        << "Aircraft ID: " << Aircraft_ID << " | New Position: (" << X << ", " << Y << ", " << Z << ")\n";
                
                cout << "Aircraft " << Aircraft_ID << " updated to position (" << X << ", " << Y << ", " << Z << ").\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Aircraft ID " << Aircraft_ID << " not found.\n";
        }
    }
}

void DataDisplaySystem(const vector<Aircraft>& aircraft_threads) {

    // Open the data log file in append mode
    ofstream logFile("aircraft_data.log", ios::app);

    while (true) {
        // Lock  mutex 
        lock_guard<mutex> lock(MUTEX);

        // Iterate through each aircraft in the vector
        for (const auto& aircraft : aircraft_threads) {
            // Log the aircraft's data (ID and position)
            logFile << "Time: " << chrono::system_clock::to_time_t(chrono::system_clock::now()) << " | "
                    << "Aircraft ID: " << aircraft.GetID() << " | Position: " << aircraft.GetPosition() << "\n";
        }
        
        // Sleep for 5 seconds before the next iteration
        this_thread::sleep_for(chrono::seconds(5));
    }
    datalogFile.close();
}


