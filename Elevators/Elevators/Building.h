/// @file
/// @author Nathan Roe
#pragma once
#include "Statistic.hpp"
#include <vector>
#include <list>

class Floor;
class Elevator;
class Passenger;

using namespace std;

/// Object to represent a Building for an Elevator Simulation
/// 
/// Creates and trakcs specified numers of Elevators and Floors,
/// handles simulation control, and tracks completed passengers
class Building
{
public:
    /// Default Building constructior, uses values as shown below
    Building();
    /// Building constructor providing additional simulation control params
    Building(const int numFloors = 100, const int numElevators = 4,
             const int timeToFloor = 10, const int stopTime = 2,
             const int maxPassengersInElevator = 8);
    /// Building destructor
    ~Building();

    /// Get pointer to Floor with given index
    /// @param floorIdx - Integer value for floor number
    /// Returns a pointer to the specified floor if one exits,
    ///    nullptr otherwise
    Floor *getFloor(int floorIdx) { return this->floors.at(floorIdx); };

    /// Adds a new passenger to the elevator simulation
    /// 
    /// Used to add future Passenger to simulation before running, places
    /// them at the appropriate starting floor to arrive at their 
    /// associated starting time
    void addPassenger(Passenger *passenger);

    /// Begins simulation of carrying passengers around building
    /// 
    /// Runs elevator sim, with passengers arriving at floor, elevators
    /// carrying passengers, and then exiting at their floors. Completes
    /// when all floors/elevators are empty, and no future passengers
    /// are yet to arrive.
    void runElevatorSim();

    /// Getter for current simulation time (seconds)
    /// Returns int of current simulation time in seconds
    int getSimTime() { return this->simTime; };

    /// Tracks given Passenger as having arrived at destination
    /// 
    /// Adds Passenger to container of arrived Passengers, and
    /// tracks their Wait time and Travel time for simulation stats
    /// @param *passenger - pointer to Passenger that has completed travel
    void completePassenger(Passenger *passenger);

    /// Get Average Wait Time of Passengers who have completed travels
    /// Returns average wait time in seconds
    double getAvgWaitTime() { return this->waitStats->average(); };

    /// Get Travel Wait Time of Passengers who have completed travels
    /// Returns average travel time in seconds
    double getAvgTravelTime() { return this->travelStats->average(); };

private:
    int numFloors;
    vector<Floor*> floors;
    int numElevators;
    vector<Elevator*> elevators;

    int simTime = 0;

    list<Passenger*> completedPassengers;
    Statistic* waitStats = new Statistic();
    Statistic* travelStats = new Statistic();

    /// Check all floors and elevators to see if there are remaining passengers
    /// Returns TRUE if any passengers have not completed travels
    bool passengersRemaining();

    const int NOCALL = -1;
    /// Checks for lowest Floor index that has passengers waiting for elevator
    /// 
    /// Returns index of lowest floor needing elevator, or NOCALL otherwise
    int elevatorCalled();

    /// Find non-busy elevator and send to commanded floor
    /// 
    /// Attempt to find elevator without a job, and alert them that given
    /// floor has waiting passengers
    void commandElevator(int floor);
};
