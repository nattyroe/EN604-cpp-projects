#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"
#include <vector>

using namespace std;

Building::Building()
{
    const int FLOORS = 100;
    const int ELEVATORS = 4;

    this->numFloors = FLOORS;
    this->numElevators = ELEVATORS;

    for (int floor = 0; floor < FLOORS; ++floor)
    {
        this->floors.push_back(new Floor(this));
    }
    for (int elev = 0; elev < ELEVATORS; ++elev)
    {
        this->elevators.push_back(new Elevator(this, numFloors));
    }
}

Building::Building(const int numFloors, const int numElevators,
                   const int timeToFloor, const int stopTime,
                   const int maxPassengers)
{
    this->numFloors = numFloors;
    this->numElevators = numElevators;
    for (int floor = 0; floor < numFloors; ++floor)
    {
        this->floors.push_back(new Floor(this));
    }
    for (int elev = 0; elev < numElevators; ++elev)
    {
        this->elevators.push_back(new Elevator(this,
                                               numFloors,
                                               timeToFloor,
                                               stopTime,
                                               maxPassengers));
    }
}

Building::~Building()
{
    while (!this->completedPassengers.empty())
    {
        delete this->completedPassengers.front();
        this->completedPassengers.pop_front();
    }
    for (Floor *floor : this->floors)
    {
        delete floor;
    }
    for (Elevator *elevator : this->elevators)
    {
        delete elevator;
    }
    delete this->waitStats;
    delete this->travelStats;
}

void Building::addPassenger(Passenger *passenger)
{
    int floor = passenger->getStartFloor();
    this->floors.at(floor)->addPassenger(passenger);
}

void Building::runElevatorSim()
{
    while (passengersRemaining())
    {
        ++this->simTime;
        if (this->simTime == 2670)
        {
            continue;
        }
        cout << "Sim Time: " << this->simTime << endl;
        for (Floor *floor : this->floors)
        {
            floor->incrementTime();
        }
        for (Elevator *elevator : this->elevators)
        {
            elevator->incrementTime();
        }

        int callingFloor = elevatorCalled();
        if (!(callingFloor == NOCALL))
        {
            commandElevator(callingFloor);
        }
    }
    return;
}

bool Building::passengersRemaining()
{
    for (Floor *floor : this->floors)
    {
        if (floor->getNumFuturePassengers() > 0 ||
            floor->getUpPassengerCount() > 0 ||
            floor->getDownPassengerCount() > 0)
        {
            return true;
        }
    }
    for (Elevator *elevator : this->elevators)
    {
        if (elevator->getNumPassengers() > 0)
        {
            return true;
        }
    }
    return false;
}

//TODO: Use iterator
int Building::elevatorCalled()
{
    for (unsigned int floorIdx = 0; floorIdx < this->floors.size(); ++floorIdx)
    {
        Floor *floor = this->floors.at(floorIdx);
        if (floor->isElevatorCalled())
        {
            return floorIdx;
        }
    }
    return NOCALL;
}

void Building::commandElevator(int floor)
{
    for (Elevator *elevator : this->elevators)
    {
        if (elevator->call(floor))
        {
            break;
        }
    }
}

void Building::completePassenger(Passenger *passenger)
{
    passenger->endTravel(this->simTime);
    this->completedPassengers.push_back(passenger);
    this->waitStats->add(passenger->getWaitTime());
    this->travelStats->add(passenger->getTravelTime());
}
