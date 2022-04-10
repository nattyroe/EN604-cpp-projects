#pragma once
#include <queue>

class Passenger;

using namespace std;

class Floor
{
public:
    void addPassenger(Passenger *passenger) { this->waitingPassengers.push(passenger); };
private:
    queue<Passenger*> waitingPassengers;
};
