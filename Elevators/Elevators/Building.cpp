#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include "Passenger.h"

using namespace std;

/// Default Building Constructor with 100 Floors and 4 Elevators 
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
} // End default building constructor

/// Building constructor providing additional simulation control params
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
} // End building constructor

/// Building destructor
Building::~Building()
{
    // Call destructor for all completed passengers
    while (!this->completedPassengers.empty())
    {
        delete this->completedPassengers.front();
        this->completedPassengers.pop_front();
    }
    // Call floor destructors
    for (Floor *floor : this->floors)
    {
        delete floor;
    }
    // Call elevator destructors
    for (Elevator *elevator : this->elevators)
    {
        delete elevator;
    }
    delete this->waitStats;
    delete this->travelStats;
} // End building destructor

/// Adds a new passenger to the elevator simulation
void Building::addPassenger(Passenger *passenger)
{
    int floorIdx = passenger->getStartFloor();
    Floor *floor = this->floors.at(floorIdx);
    if (floor)
    {
        floor->addPassenger(passenger);
    }
} // End function addPassenger

/// Begins simulation of carrying passengers around building
void Building::runElevatorSim()
{
    // Verify simulation has remaining passengers
    while (passengersRemaining())
    {
        // Increment sim time
        ++this->simTime;
        cout << "Sim Time: " << this->simTime << endl;

        // Update current status of each floor
        for (Floor *floor : this->floors)
        {
            floor->incrementTime();
        }
        // Update current status of each elevator
        for (Elevator *elevator : this->elevators)
        {
            elevator->incrementTime();
        }

        // Check to see if any floors need elevators
        int callingFloor = elevatorCalled();
        if (!(callingFloor == NOCALL))
        {
            // Call elevator to first floor with passengers
            commandElevator(callingFloor);
        }
    }
} // End function runElevatorSim

/// Check all floors and elevators to see if there are remaining passengers
bool Building::passengersRemaining()
{
    // Check floors for passengers
    for (Floor *floor : this->floors)
    {
        if (floor->getNumFuturePassengers() > 0 ||
            floor->getUpPassengerCount() > 0 ||
            floor->getDownPassengerCount() > 0)
        {
            return true;
        }
    }
    // Check elevators for passengers
    for (Elevator *elevator : this->elevators)
    {
        if (elevator->getNumPassengers() > 0)
        {
            return true;
        }
    }
    return false;
} // End function passengersRemaining

/// Checks for lowest Floor index that has passengers waiting for elevator
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
} // End function elevatorCalled

/// Find non-busy elevator and send to commanded floor
void Building::commandElevator(int floor)
{
    for (Elevator *elevator : this->elevators)
    {
        if (elevator->call(floor))
        {
            break;
        }
    }
} // End function commandElevator

/// Tracks given Passenger as having arrived at destination
void Building::completePassenger(Passenger *passenger)
{
    passenger->endTravel(this->simTime);
    this->completedPassengers.push_back(passenger);
    this->waitStats->add(passenger->getWaitTime());
    this->travelStats->add(passenger->getTravelTime());
} // End function completePassenger
