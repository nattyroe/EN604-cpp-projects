/// @file
/// @author Nathan Roe
#pragma once
#include <list>

class Building;
class Passenger;

using namespace std;

/// Object to represent an Elevator in a building
/// 
/// Tracks current passengers and elevator logic for moving
/// passengers between floors, stopping, and waiting for calls 
class Elevator
{
public:
    /// Current Elevator Operating Status
    enum class Status
    {
        STOPPED,
        STOPPING,
        MOVING_UP,
        MOVING_DOWN
    };

    // Current Elevator Goal Direction
    enum class Direction
    {
        NONE,
        UP,
        DOWN
    };

    /// Elevator Constructor
    /// 
    /// @param *building - pointer to building containing elevator
    /// @param numFloors - number of floors in building
    /// @param timeToFloor - number of seconds required for elevator
    ///    to travel between floors
    /// @param stopTime - number of seconds required for elevator
    ///    to come to a stop
    /// @param maxPassengers - maximum passenger count allowed
    ///    on elevator
    Elevator(Building *building, int numFloors, int timeToFloor = 10,
             int stopTime = 2, int maxPassengers = 8);

    /// Elevator destructor
    ~Elevator();

    /// Notify elevator that sim time has upticked 1 second
    ///
    /// Updates remaining time in current elevator status,
    /// or seeks new status if prevous operation complete
    void incrementTime();

    /// Call Elevator to given floor number
    /// 
    /// Attempts to call on elevator to given floor number,
    /// returns boolean of whether elevator is free to respond
    /// @param floor - floor number requiring elevator
    /// Return TRUE if elevator is now moving towards floor,
    ///    FALSE otherwise
    bool call(int floor);

    /// Getter for Elevator's current floor
    /// Return int of current floor number
    int getFloor() { return this->floor; };

    /// Getter for Elevator's current Status
    /// Returns an Elevator::Status
    Status getStatus() { return this->status; };

    /// Getter for Elevator's current direction
    /// Returns an Elevator::Direction
    Direction getDirection() { return this->direction; };

    /// Get the number of passengers on the Elevator
    /// Returns an int of the number of passengers onboard
    int getNumPassengers() { return this->passengers.size(); };

    /// Add given Passenger to Elevator
    /// @param *passenger - Pointer to boarding Passenger
    void receivePassenger(Passenger *p);

private:
    Building *building;
    int maxPassengers;
    int numFloors = 0;

    int floor = 0;

    int speed;
    int stopTime;
    int remainingTime = 0;

    Status status = Status::STOPPED;
    Direction direction = Direction::NONE;

    list<Passenger*> passengers;

    /// Determine whether Elevator should stop at current floor
    /// 
    /// Checks whether elevator is full and whether there are
    /// passengers waiting in the correct direction
    /// Returns TRUE if Elevator should stop, FALSE otherwise
    bool shouldStop();

    /// Move Passengers between Elevator<->Current Floor
    void movePassengers();
};
