#include "Passenger.h"

Passenger::Passenger(int startFloor, int endFloor, int startTime)
{
    this->startFloor = startFloor;
    this->endFloor = endFloor;
    this->startTime = startTime;
}

// Less-than operator for comparing Passengers
bool Passenger::operator<(const Passenger & passenger)
{
    return this->startTime < passenger.startTime;
} // End < operator override

// Greater-than operator for comparing Passengers
bool Passenger::operator>(const Passenger & passenger)
{
    return this->startTime > passenger.startTime;
} // End > operator override

// Equality operator for comparing Passengers
bool Passenger::operator==(const Passenger & passenger)
{
    return this->startTime == passenger.startTime;
} // End == operator override