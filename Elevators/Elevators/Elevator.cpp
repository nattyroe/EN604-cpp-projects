#include "Elevator.h"
#include "Building.h"
#include "Floor.h"
#include "Passenger.h"
#include <utility>

/// Elevator Constructor
Elevator::Elevator(Building *building, int numFloors,
                   int timeToFloor, int stopTime,
                   int maxPassengers)
{
    this->building = building;
    this->numFloors = numFloors;
    this->speed = timeToFloor;
    this->stopTime = stopTime;
    this->maxPassengers = maxPassengers;
} // End elevator Constructor

/// Elevator destructor
Elevator::~Elevator()
{
    while (!this->passengers.empty())
    {
        delete this->passengers.front();
        this->passengers.pop_front();
    }
} // End elevator destructor

/// Notify elevator that sim time has upticked 1 second
void Elevator::incrementTime()
{
    // If current operation ongoing, decrement time
    if (this->remainingTime > 0)
    {
        --this->remainingTime;
    }
    // If Elevator completed STOPPING, change to STOPPED
    else if (this->status == Status::STOPPING)
    {
        this->status = Status::STOPPED;
        cout << "\tElevator " << this << " stopped at floor " << this->floor << endl;
        // Move passengers between elevator/floor
        movePassengers();
        // Reset elevator direction if there are no
        // onboard passengers
        if (this->passengers.empty())
        {
            this->direction = Direction::NONE;
        }
    }
    // If Elevator completed MOVING_UP, see whether
    // stop is required
    else if (this->status == Status::MOVING_UP)
    {
        // Arrive at new floor
        ++this->floor;
        // If at bottom of building, come to a stop
        if (this->floor == this->numFloors - 1)
        {
            cout << "\tElevator " << this << " stopping at floor " << this->floor << endl;
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        // Check to see if stop is needed
        else if (shouldStop())
        {
            cout << "\tElevator " << this << " stopping at floor " << this->floor << endl;
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        // Otherwise, continue moving up
        else
        {
            cout << "\tElevator " << this << " continuing Up" << endl;
            this->remainingTime = this->speed;
        }
    }
    // If Elevator completed MOVING_DOWN, see whether
    // stop is required
    else if (this->status == Status::MOVING_DOWN)
    {
        // Arrive at new floor
        --this->floor;
        // If at top of building, come to a stop
        if (this->floor == 0)
        {
            cout << "\tElevator " << this << " stopping at floor " << this->floor << endl;
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        // Check to see if stop is needed
        else if (shouldStop())
        {
            cout << "\tElevator " << this << " stopping at floor " << this->floor << endl;
            this->status = Status::STOPPING;
            this->remainingTime = stopTime;
        }
        // Otherwise, continue moving down
        else
        {
            cout << "\tElevator " << this << " continuing Up" << endl;
            this->remainingTime = this->speed;
        }
    }
    // Update status if elevator is stopped
    else if (this->status == Status::STOPPED)
    {
        // Return to moving up
        if (this->direction == Direction::UP)
        {
            cout << "\tElevator " << this << " starting Up" << endl;
            this->status = Status::MOVING_UP;
            this->remainingTime = speed;
        }
        // Return to moving down
        else if (this->direction == Direction::DOWN)
        {
            cout << "\tElevator " << this << " starting Down" << endl;
            this->status = Status::MOVING_DOWN;
            this->remainingTime = speed;
        }
        // Check to see if passengers just arrived
        else if (shouldStop())
        {
            movePassengers();
        }
    }
} // End function incrementTime

/// Call Elevator to given floor number
bool Elevator::call(int floor)
{
    // If Elevator has no current destination,
    // begin moving towards called floor
    if (this->direction == Direction::NONE &&
        this->status == Status::STOPPED)
    {
        // Move UP
        if (floor > this->floor)
        {
            this->status = Status::MOVING_UP;
            this->remainingTime = this->speed;
            return true;
        }
        // Move Down
        else if (floor < this->floor)
        {
            this->status = Status::MOVING_DOWN;
            this->remainingTime = this->speed;
            return true;
        }
        // Passengers at current floor
        else
        {
            return true;
        }
    }
    // Elevator is busy
    return false;
} // End function call


/// Determine whether Elevator should stop at current floor
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
        // If continuing up, see if there are up passengers
        if (this->direction == Direction::UP)
        {
            if (waitingUp > 0)
            {
                return true;
            }
        }
        // If continuing down, see if there are down passengers
        else if (this->direction == Direction::DOWN)
        {
            if (waitingDown > 0)
            {
                return true;
            }
        }
        // If no destination, see if there are any waiting passengers
        else
        {
            if (waitingUp > 0 || waitingDown > 0)
            {
                return true;
            }
        }
    }
    return false;
} // End function shouldStop

/// Move Passengers between Elevator<->Current Floor
void Elevator::movePassengers()
{
    // Let Passengers Off
    list<Passenger*>::iterator iter = this->passengers.begin();
    while (iter != this->passengers.end())
    {
        Passenger *p = *iter;
        if (p->getEndFloor() == this->floor)
        {
            cout << "\tPassenger " << &p << " exiting elevator " << this << " at floor " << this->floor << endl;
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
            // If continuing UP, request up passengers
            if (this->direction == Direction::UP)
            {
                floor->giveUpPassengers(this, passengerSpace);
            }
            // If continuing DOWN, request down passengers
            else if (this->direction == Direction::DOWN)
            {
                floor->giveDownPassengers(this, passengerSpace);
            }
            // If no destination, request max of up/down passengers
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
} // End function movePassengers

/// Add given Passenger to Elevator
void Elevator::receivePassenger(Passenger *p)
{
    cout << "\tPassenger " << &p << " entering elevator " << this << " at floor " << this->floor << endl;
    this->passengers.push_back(p); 
}
