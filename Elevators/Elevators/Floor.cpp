#include "Floor.h"
#include "Building.h"
#include "Elevator.h"
#include "Passenger.h" 

/// Floor destructor
Floor::~Floor()
{
    // Delete future passengers
    while (!this->futurePassengers.empty())
    {
        delete this->futurePassengers.top();
        this->futurePassengers.pop();
    }
    // Delete waiting up passengers
    while (!this->waitingUpPassengers.empty())
    {
        delete this->waitingUpPassengers.front();
        this->waitingUpPassengers.pop();
    }
    // Delete waiting down passengers
    while (!this->waitingDownPassengers.empty())
    {
        delete this->waitingDownPassengers.front();
        this->waitingDownPassengers.pop();
    }
} // End floor destructor

/// Adds provided passenger to the floor
void Floor::addPassenger(Passenger *passenger)
{
    this->futurePassengers.push(passenger);
} // End function addPassenger

/// Notify Floor that sim time has upticked 1 second
void Floor::incrementTime()
{
    shiftPassengers();
} // End function incrementTime

/// Moves future passengers to either Up queue or Down queue
void Floor::shiftPassengers()
{
    while (!this->futurePassengers.empty())
    {
        // Check to see whether any passengers arrive at this second
        if (this->futurePassengers.top()->getStartTime() > this->building->getSimTime())
        {
            break;
        }
        // If Passenger arrives, move to appropriate queue (up/down)
        else
        {
            Passenger *p = this->futurePassengers.top();
            if (p->getStartFloor() > p->getEndFloor())
            {
                this->waitingDownPassengers.push(p);
                this->elevatorCalled = true;
            }
            else if (p->getStartFloor() < p->getEndFloor())
            {
                this->waitingUpPassengers.push(p);
                this->elevatorCalled = true;
            }
            else
            {
                this->building->completePassenger(p);
            }
            this->futurePassengers.pop();
        }
    }
} // End function shiftPassengers

/// Get the total number of passengers waiting at the floor
/// Returns an pair - Passengers Waiting to go up,
///                   Passengers Waiting to go down
pair<int, int> Floor::getNumPassengersAtFloor()
{
    return make_pair(this->getUpPassengerCount(),
                     this->getDownPassengerCount());
} // End function getNumPassengersAtFloor

/// Adds up to the provided number of UP passengers to the elevator
void Floor::giveUpPassengers(Elevator *elevator, int maxPassengers)
{
    int passCount = 0;
    while (passCount < maxPassengers && !this->waitingUpPassengers.empty())
    {
        Passenger *p = this->waitingUpPassengers.front();
        p->startTravel(this->building->getSimTime());
        elevator->receivePassenger(p);
        this->waitingUpPassengers.pop();
        ++passCount;
    }
    if (this->waitingUpPassengers.empty() && this->waitingDownPassengers.empty())
    {
        this->elevatorCalled = false;
    }
} // End function giveUpPassengers

/// Adds up to the provided number of DOWN passengers to the elevator
void Floor::giveDownPassengers(Elevator *elevator, int maxPassengers)
{
    int passCount = 0;
    while (passCount < maxPassengers && !this->waitingDownPassengers.empty())
    {
        Passenger *p = this->waitingDownPassengers.front();
        p->startTravel(this->building->getSimTime());
        elevator->receivePassenger(p);
        this->waitingDownPassengers.pop();
        ++passCount;
    }
    if (this->waitingUpPassengers.empty() && this->waitingDownPassengers.empty())
    {
        this->elevatorCalled = false;
    }
} // End function giveDownPassengers
