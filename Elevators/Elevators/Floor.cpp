#include "Floor.h"
#include "Building.h"
#include "Elevator.h"
#include "Passenger.h" 

Floor::~Floor()
{
    while (!this->futurePassengers.empty())
    {
        delete this->futurePassengers.top();
        this->futurePassengers.pop();
    }
    while (!this->waitingUpPassengers.empty())
    {
        delete this->waitingUpPassengers.front();
        this->waitingUpPassengers.pop();
    }
    while (!this->waitingDownPassengers.empty())
    {
        delete this->waitingDownPassengers.front();
        this->waitingDownPassengers.pop();
    }
}

void Floor::addPassenger(Passenger *passenger)
{
    this->futurePassengers.push(passenger);
};

void Floor::incrementTime()
{
    shiftPassengers();
}

void Floor::shiftPassengers()
{
    while (!this->futurePassengers.empty())
    {
        if (this->futurePassengers.top()->getStartTime() > this->building->getSimTime())
        {
            break;
        }
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
}

int Floor::getNumFuturePassengers()
{
    return this->futurePassengers.size();
}

pair<int, int> Floor::getNumPassengersAtFloor()
{
    return make_pair(this->getUpPassengerCount(),
                     this->getDownPassengerCount());
}

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
}

void Floor::giveDownPassengers(Elevator *elevator, int maxPassengers)
{
    int passCount = 0;
    while (passCount < maxPassengers && !this->waitingDownPassengers.empty())
    {
        Passenger* p = this->waitingDownPassengers.front();
        p->startTravel(this->building->getSimTime());
        elevator->receivePassenger(p);
        this->waitingDownPassengers.pop();
        ++passCount;
    }
    if (this->waitingUpPassengers.empty() && this->waitingDownPassengers.empty())
    {
        this->elevatorCalled = false;
    }
}
