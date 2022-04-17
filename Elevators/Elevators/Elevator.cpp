#include "Elevator.h"
#include "Building.h"
#include "Floor.h"
#include "Passenger.h"
#include <utility>

Elevator::Elevator(Building *building, int numFloors,
                   int timeToFloor, int stopTime,
                   int maxPassengers)
{
    this->building = building;
    this->numFloors = numFloors;
    this->speed = timeToFloor;
    this->stopTime = stopTime;
    this->maxPassengers = maxPassengers;
}

Elevator::~Elevator()
{
    while (!this->passengers.empty())
    {
        delete this->passengers.front();
        this->passengers.pop_front();
    }
}

void Elevator::incrementTime()
{

    if (this->remainingTime > 0)
    {
        --this->remainingTime;
    }
    else if (this->status == Status::STOPPING)
    {
        this->status = Status::STOPPED;
        movePassengers();
        if (this->passengers.empty())
        {
            this->direction = Direction::NONE;
        }
    }
    else if (this->status == Status::MOVING_UP)
    {
        ++this->floor;
        if (this->floor == this->numFloors - 1)
        {
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        else if (shouldStop())
        {
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        else
        {
            this->remainingTime = this->speed;
        }
    }
    else if (this->status == Status::MOVING_DOWN)
    {
        --this->floor;
        if (this->floor == 0)
        {
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        else if (shouldStop())
        {
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        else
        {
            this->remainingTime = this->speed;
        }
    }
    else if (this->status == Status::STOPPED)
    {
        if (this->direction == Direction::UP)
        {
            this->status = Status::MOVING_UP;
            this->remainingTime = speed;
        }
        else if (this->direction == Direction::DOWN)
        {
            this->status = Status::MOVING_DOWN;
            this->remainingTime = speed;
        }
        else if (shouldStop())
        {
            movePassengers();
        }
    }
}

bool Elevator::call(int floor)
{
    if (this->direction == Direction::NONE &&
        this->status == Status::STOPPED)
    {
        if (floor > this->floor)
        {
            this->status = Status::MOVING_UP;
            this->remainingTime = this->speed;
            return true;
        }
        else if (floor < this->floor)
        {
            this->status = Status::MOVING_DOWN;
            this->remainingTime = this->speed;
            return true;
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool Elevator::shouldStop()
{
    // Check if Passenger needs off
    for (Passenger* passenger : this->passengers)
    {
        if (passenger->getEndFloor() == this->floor)
        {
            return true;
        }
    }

    // Check if elevator is full
    if (static_cast<int>(this->passengers.size()) >= this->maxPassengers)
    {
        return false;
    }

    // Check for waiting passengers
    Floor *floor = this->building->getFloor(this->floor);
    if (floor)
    {
        pair<int, int> passengerCounts = floor->getNumPassengersAtFloor();
        int waitingUp = passengerCounts.first;
        int waitingDown = passengerCounts.second;
        if (this->direction == Direction::UP)
        {
            if (waitingUp > 0)
            {
                return true;
            }
        }
        else if (this->direction == Direction::DOWN)
        {
            if (waitingDown > 0)
            {
                return true;
            }
        }
        else
        {
            if (waitingUp > 0 || waitingDown > 0)
            {
                return true;
            }
        }
    }
    return false;
}

void Elevator::movePassengers()
{
    // Let Passengers Off
    list<Passenger*>::iterator iter = this->passengers.begin();
    while (iter != this->passengers.end())
    {
        Passenger* p = *iter;
        if (p->getEndFloor() == this->floor)
        {
            this->building->completePassenger(p);
            this->passengers.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }

    // Let Passengers On
    int passengerSpace = this->maxPassengers - static_cast<int>(this->passengers.size());
    if (passengerSpace > 0)
    {
        Floor* floor = this->building->getFloor(this->floor);
        if (floor)
        {
            if (this->direction == Direction::UP)
            {
                floor->giveUpPassengers(this, passengerSpace);
            }
            else if (this->direction == Direction::DOWN)
            {
                floor->giveDownPassengers(this, passengerSpace);
            }
            else
            {
                pair<int, int> passCounts = floor->getNumPassengersAtFloor();
                if (passCounts.first >= passCounts.second)
                {
                    floor->giveUpPassengers(this, passengerSpace);
                    this->direction = Direction::UP;
                }
                else
                {
                    floor->giveDownPassengers(this, passengerSpace);
                    this->direction = Direction::DOWN;
                }
            }
        }
    }
}
