/*
 * CheckforSeparation.cpp
 *
 *  Created on: 07-Nov-2024
 *      Author: hp
 */
#include "CheckforSeparation.h"
#include <cmath>
#include <iostream>

CheckforSeparation::CheckforSeparation(double threshold) : separation_threshold(threshold) {}

void CheckforSeparation::AddAircraft(const Aircraft& aircraft) {
    aircrafts.push_back(aircraft);
}

void CheckforSeparation::CheckforViolations() const {
    for (size_t i = 0; i < aircrafts.size(); ++i) {
        for (size_t j = i + 1; j < aircrafts.size(); ++j) {
            double distance = CalculateDistance(aircrafts[i].Get_displacement(), aircrafts[j].Get_displacement());
            if (distance < separation_threshold) {
                std::cout << "Separation violation detected between "
                          << aircrafts[i].Get_aircraft_id() << " and " << aircrafts[j].Get_aircraft_id()
                          << " - Distance: " << distance << " (Threshold: " << separation_threshold << ")\n";
            }
        }
    }
}

double CheckforSeparation::CalculateDistance(const Vectors& pos1, const Vectors& pos2) const {
    double dx = pos1.x - pos2.x;
    double dy = pos1.y - pos2.y;
    double dz = pos1.z - pos2.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}




