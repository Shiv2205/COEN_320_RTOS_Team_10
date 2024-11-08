#ifndef CHECKFORSEPARATION_H
#define CHECKFORSEPARATION_H

#include "Aircraft.h"
#include <vector>

class CheckforSeparation {
private:
    std::vector<Aircraft> aircrafts;
    double separation_threshold;

public:

    CheckforSeparation(double threshold);

    void AddAircraft(const Aircraft& aircraft);

    void CheckforViolations() const;

    double CalculateDistance(const Vectors& pos1, const Vectors& pos2) const;
};

#endif
