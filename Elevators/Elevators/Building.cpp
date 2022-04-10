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
        this->floors.push_back(new Floor);
    }
    for (int elev = 0; elev < ELEVATORS; ++elev)
    {
        this->elevators.push_back(new Elevator);
    }
}

Building::Building(const int numFloors, const int numElevators)
{
    this->numFloors = numFloors;
    this->numElevators = numElevators;
    for (int floor = 0; floor < numFloors; ++floor)
    {
        this->floors.push_back(new Floor);
    }
    for (int elev = 0; elev < numElevators; ++elev)
    {
        this->elevators.push_back(new Elevator);
    }
}

Building::~Building()
{
    for (int floor = 0; floor < this->numFloors; ++floor)
    {
        delete this->floors.at(floor);
    }
    for (int elev = 0; elev < this->numElevators; ++elev)
    {
        delete this->elevators.at(elev);
    }
}

void Building::callElevator(Passenger *passenger)
{
    int floor = passenger->getStartFloor();
    this->floors.at(floor)->addPassenger(passenger);
}
