#pragma once
#include <iostream>

using namespace std;

class Passenger
{
public:
    Passenger(int startFloor, int endFloor, int startTime);
    ~Passenger();

    const int getStartFloor() { return this->startFloor; };
    const int getEndFloor() { return this->endFloor; };
    const int getStartTime() { return this->startTime; };
    const int getWaitTime() { return this->waitTime; };
    const int getTravelTime() { return this->travelTime; };
    void startTravel(int time) { this->waitTime = time - this->startTime; };
    void endTravel(int time) { this->travelTime = time - (this->startTime + this->travelTime); };

    // Override comparitor operators to compare Passengers
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
