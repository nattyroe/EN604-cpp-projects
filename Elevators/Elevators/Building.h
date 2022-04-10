#pragma once
#include <vector>

class Floor;
class Elevator;
class Passenger;

using namespace std;

class Building
{
public:
    Building();
    Building(const int numFloors, const int numElevators);
    ~Building();

    Floor *getFloor(int floorIdx) { return this->floors.at(floorIdx); };
    Elevator *getElevator(int elevIdx) { return this->elevators.at(elevIdx); };

    void callElevator(Passenger *passenger);

private:
    int numFloors;
    int numElevators;
    vector<Floor*> floors;
    vector<Elevator*> elevators;
};
