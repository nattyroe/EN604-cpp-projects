/// @file
/// @author Nathan Roe
#pragma once
#include <iostream>

using namespace std;

/// Object to represent a Passenger in an Elevator Sim
/// 
/// Tracks Passenger start floor, destination floor,
/// arrival time, and durations of Waiting and Traveling
class Passenger
{
public:
    /// Passenger Constructor
    /// 
    /// @param startFloor - Passengers starting floor number
    /// @param endFloor - Floor number of destination
    /// @param startTime - Time at which passenger arrives at floor (seconds)
    Passenger(int startFloor, int endFloor, int startTime);

    /// Getter for Passenger's starting floor
    /// Returns int of startFloor
    const int getStartFloor() { return this->startFloor; };

    /// Getter for Passenger's destination floor
    /// Returns int of endFloor
    const int getEndFloor() { return this->endFloor; };

    /// Getter for Passenger's arrival time (seconds)
    /// Returns int of startTime
    const int getStartTime() { return this->startTime; };

    /// Getter for Passenger's total Wait Time (seconds)
    /// Returns int of waitTime
    const int getWaitTime() { return this->waitTime; };

    /// Getter for Passengers total Travel Time (seconds)
    /// Returns int of travel'Time
    const int getTravelTime() { return this->travelTime; };

    /// Starts Travel timer, and ends Wait timer
    void startTravel(int time) { this->waitTime = time - this->startTime; };
    /// Ends Travel timer
    void endTravel(int time) { this->travelTime = time - (this->startTime + this->travelTime); };

    /// Override comparitor operators to compare Passengers
    /// Used for sorting Passengers by arrival time
    bool operator<(const Passenger &passenger);
    bool operator>(const Passenger &passenger);
    bool operator==(const Passenger &passenger);

private:
    int startFloor;
    int endFloor;
    int startTime;
    int waitTime = 0;
    int travelTime = 0;
};

/// Stream insertion override for printing tree info
ostream &operator<<(ostream &os, Passenger &passenger);
