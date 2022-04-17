#pragma once
#include <list>

class Building;
class Passenger;

using namespace std;

class Elevator
{
public:

    enum class Status
    {
        STOPPED,
        STOPPING,
        MOVING_UP,
        MOVING_DOWN
    };

    enum class Direction
    {
        NONE,
        UP,
        DOWN
    };

    Elevator(Building *building, int numFloors, int timeToFloor = 10,
             int stopTime = 2, int maxPassengers = 8);
    ~Elevator();

    void incrementTime();
    bool call(int floor);
    int getFloor() { return this->floor; };
    Status getStatus() { return this->status; };
    Direction getDirection() { return this->direction; };
    int getNumPassengers() { return this->passengers.size(); };
    void receivePassenger(Passenger *passenger) { this->passengers.push_back(passenger); };

private:
    int numFloors = 0;
    Building *building;
    int speed;
    int stopTime;
    int maxPassengers;
    int floor = 0;
    int remainingTime = 0;
    Status status = Status::STOPPED;
    Direction direction = Direction::NONE;
    list<Passenger*> passengers;

    bool shouldStop();
    void movePassengers();

};
