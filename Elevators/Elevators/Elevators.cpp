#include "Passenger.h"
#include "Building.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<Passenger*> readElevatorInput(string inputFile = "../Input/Elevators.csv")
{
    vector<Passenger*> passengers;
    ifstream file(inputFile);

    if (file)
    {
        string line;
        char delimeter = ',';
        int passengerNum;
        int startTime;
        int startFloor;
        int endFloor;

        while (file >> line)
        {
            cout << "Line: " << line << endl;
            vector<int> result;
            int splitLoc = 0;
            while (!(splitLoc == string::npos))
            {
                splitLoc = line.find(delimeter);
                if (!(splitLoc == string::npos))
                {
                    string nextValue = line.substr(0, splitLoc);
                    try
                    {
                        result.push_back(stoi(nextValue));
                    }
                    catch (invalid_argument e)
                    {
                        break;
                    }
                    line = line.substr(splitLoc + 1);
                }
                else
                {
                    try
                    {
                        result.push_back(stoi(line));
                    }
                    catch (exception e)
                    {
                        cout << e.what() << endl;
                        break;
                    }
                }
            }

            if (result.size() == 4)
            {
                passengerNum = result.at(0);
                startTime = result.at(1);
                startFloor = result.at(2);
                endFloor = result.at(3);
                Passenger *passenger = new Passenger(startFloor, endFloor, startTime);
                cout << "Read Passenger:\n" << *passenger << endl;
                passengers.push_back(passenger);
            }

            if (result.size() == 3)
            {
                startTime = result.at(0);
                startFloor = result.at(1);
                endFloor = result.at(2);
                Passenger* passenger = new Passenger(startFloor, endFloor, startTime);
                cout << "Read Passenger:\n" << *passenger << endl;
                passengers.push_back(passenger);
            }
        }
    }

    return passengers;
}

int main()
{
    const int NUM_FLOORS = 100;
    const int NUM_ELEVATORS = 4;
    const int startingSpeed = 10;
    const int newSpeed = 5;

    Building *origBuilding = new Building(NUM_FLOORS,
                                          NUM_ELEVATORS,
                                          startingSpeed);
    Building *newBuilding = new Building(NUM_FLOORS,
                                         NUM_ELEVATORS,
                                         newSpeed);

    vector<Passenger*> passengers = readElevatorInput();
    vector<Passenger*> passengersCopy;

    for (Passenger* p : passengers)
    {
        Passenger* newP = new Passenger(0, 0, 0);
        *newP = *p;
        passengersCopy.push_back(newP);

        origBuilding->addPassenger(p);
    }

    for (Passenger* p : passengersCopy)
    {
        newBuilding->addPassenger(p);
    }

    origBuilding->runElevatorSim();
    double waitTime1 = origBuilding->getAvgWaitTime();
    double travelTime1 = origBuilding->getAvgTravelTime();

    newBuilding->runElevatorSim();
    double waitTime2 = newBuilding->getAvgWaitTime();
    double travelTime2 = newBuilding->getAvgTravelTime();

    double waitReduction = (waitTime1 - waitTime2) / waitTime1 * 100;
    double travelReduction = (travelTime1 - travelTime2) / travelTime1 * 100;

    cout << "\nFor Elevator Speed " << startingSpeed << ":" << endl;
    cout << "\tAvg Wait Time: " << waitTime1 << " seconds" << endl;
    cout << "\tAvg Travel Time: " << travelTime1 << " seconds" << endl << endl;

    cout << "For Elevator Speed " << newSpeed << ":" << endl;
    cout << "\tAvg Wait Time: " << waitTime2 << " seconds" << endl;
    cout << "\tAvg Travel Time: " << travelTime2 << " seconds" << endl << endl;

    cout << "Wait Time Reduction: " << waitReduction << "%" << endl;
    cout << "Travel Time Reduction: " << travelReduction << "%" << endl;
    
    delete origBuilding;
    delete newBuilding;

}
