#pragma once
#include <queue>
#include <utility>

class Building;
class Elevator;
class Passenger;

using namespace std;

class Floor
{
public:
    Floor(Building *building) { this->building = building; };
    ~Floor();

    void addPassenger(Passenger *passenger);
    void incrementTime();
    int getNumFuturePassengers();
    void resetCallButton() { this->elevatorCalled = false; };
    bool isElevatorCalled() { return this->elevatorCalled; };
    int getUpPassengerCount() { return this->waitingUpPassengers.size(); };
    int getDownPassengerCount() { return this->waitingDownPassengers.size(); };
    void giveUpPassengers(Elevator *elevator, int maxPassengers);
    void giveDownPassengers(Elevator *elevator, int maxPassengers);

    pair<int, int> getNumPassengersAtFloor();

private:
    Building *building;

    bool elevatorCalled = false;

    priority_queue<Passenger*> futurePassengers;
    queue<Passenger*> waitingUpPassengers;
    queue<Passenger*> waitingDownPassengers;

    void shiftPassengers();
};
