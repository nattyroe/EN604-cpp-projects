#pragma once
#include "Statistic.hpp"
#include <vector>
#include <list>

class Floor;
class Elevator;
class Passenger;

using namespace std;

class Building
{
public:
    Building();
    Building(const int numFloors, const int numElevators,
             const int timeToFloor = 10, const int stopTime = 2,
             const int maxPassengersInElevator = 8);
    ~Building();

    Floor *getFloor(int floorIdx) { return this->floors.at(floorIdx); };
    Elevator *getElevator(int elevIdx) { return this->elevators.at(elevIdx); };

    void addPassenger(Passenger *passenger);

    void runElevatorSim();
    int getSimTime() { return this->simTime; };

    void completePassenger(Passenger *passenger);
    double getAvgWaitTime() { return this->waitStats->average(); };
    double getAvgTravelTime() { return this->travelStats->average(); };

private:
    int numFloors;
    int numElevators;
    vector<Floor*> floors;
    vector<Elevator*> elevators;
    Statistic *waitStats = new Statistic();
    Statistic *travelStats = new Statistic();
    list<Passenger*> completedPassengers;

    int simTime = 0;

    bool passengersRemaining();
    const int NOCALL = -1;
    int elevatorCalled();
    void commandElevator(int floor);
};