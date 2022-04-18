/// @file
/// @author Nathan Roe
#pragma once
#include <queue>
#include <list>
#include <utility>

class Building;
class Elevator;
class Passenger;

using namespace std;

/// Object to represent a Floor in a building
/// 
/// Tracks future and currently waiting passengers,
/// and provides status on need for an elevator
class Floor
{
public:
    /// Floor constructor
    Floor(Building *building) { this->building = building; };
    /// Floor destructor
    ~Floor();

    /// Adds provided passenger to the floor
    /// 
    /// Adds future passenger, to be shifted to waiting
    /// at the passenger's StartTime
    void addPassenger(Passenger *passenger);

    /// Notify Floor that sim time has upticked 1 second
    ///
    /// Checks to see if any future passengers arrive to
    /// wait for elevators
    void incrementTime();

    /// Get number of future passengers
    /// Returns int of futrure passenger count
    int getNumFuturePassengers() { return this->futurePassengers.size(); };

    /// Get number of passengers waiting to go up
    /// Returns int of waitingUpPassenger count
    int getUpPassengerCount() { return this->waitingUpPassengers.size(); };

    /// Get number of passengers waiting to go up
    /// Returns int of waitingUpPassenger count
    int getDownPassengerCount() { return this->waitingDownPassengers.size(); };

    /// Checks whether elevator is needed at this floor
    /// Returns TRUE if elevator is needed, FALSE otherwise
    bool isElevatorCalled() { return this->elevatorCalled; };

    /// Adds up to the provided number of passengers to the elevator
    /// 
    /// Shifts passengers waiting to go UP onto the elevator. Number
    /// of passengers shifted will be the maxPassengers asked for,
    /// or all up-waiting passengers if less than the cap
    /// @param *elevator - pointer to the Elevator picking up passengers
    /// @param maxPassengers - maximum allowed passengers to get on Elevator
    void giveUpPassengers(Elevator *elevator, int maxPassengers);

    /// Adds up to the provided number of passengers to the elevator
    /// 
    /// Shifts passengers waiting to go DOWN onto the elevator. Number
    /// of passengers shifted will be the maxPassengers asked for,
    /// or all down-waiting passengers if less than the cap
    /// @param *elevator - pointer to the Elevator picking up passengers
    /// @param maxPassengers - maximum allowed passengers to get on Elevator
    void giveDownPassengers(Elevator *elevator, int maxPassengers);

    /// Get the total number of passengers waiting at the floor
    /// Returns an pair - Passengers Waiting to go up,
    ///                   Passengers Waiting to go down
    pair<int, int> getNumPassengersAtFloor();

private:
    Building *building;

    bool elevatorCalled = false;

    list<Passenger*> futurePassengers;
    queue<Passenger*> waitingUpPassengers;
    queue<Passenger*> waitingDownPassengers;

    /// Moves future passengers to either Up queue or Down queue
    /// if it is their arrival time
    void shiftPassengers();
};
