#include "Passenger.h"
#include <iostream>

using namespace std;

Passenger::Passenger(int startFloor, int endFloor, int startTime)
{
    this->startFloor = startFloor;
    this->endFloor = endFloor;
    this->startTime = startTime;
}

// Less-than operator for comparing Passengers
bool Passenger::operator<(const Passenger &passenger)
{
    return this->startTime < passenger.startTime;
} // End < operator override

// Greater-than operator for comparing Passengers
bool Passenger::operator>(const Passenger &passenger)
{
    return this->startTime > passenger.startTime;
} // End > operator override

// Equality operator for comparing Passengers
bool Passenger::operator==(const Passenger &passenger)
{
    return this->startTime == passenger.startTime;
} // End == operator override

/// Stream insertion override for printing tree info
ostream &operator<<(ostream &os, Passenger &passenger)
{
    // Print out tree nodes
    os << "Passenger " << &passenger << ":\n";
    os << "\tStart Time: " << passenger.getStartTime() << "\n";
    os << "\tStart Floor: " << passenger.getStartFloor() << "\n";
    os << "\tEnd Floor: " << passenger.getEndFloor() << "\n";
    return os;
} // End << operator override
