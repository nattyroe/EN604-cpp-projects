/// @file
/// @author Nathan Roe
/// Elevator Simulation
/// 
/// Runs an elevator simulation for a 100 floor building
/// and 4 elevators, carrying passengers described in input
/// file. Simulation is run twice with elevators of differing
/// speeds, and the sim run times are compared for each.
#include "Passenger.h"
#include "Building.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// Read passenger input file (Elevators.csv)
/// 
/// Reads a CSV describing required passenger info.
/// Either:
///    passengerNumber, startTime, startFloor, endFloor
/// Or:
///    startTime, startFloor, endFloor
/// @param inputFile - String of filepath to Elevators.csv
/// Returns a vector of pointers to created Passengers
vector<Passenger*> readElevatorInput(string inputFile = "../Input/Elevators.csv")
{
    vector<Passenger*> passengers;
    ifstream file(inputFile);

    // Verify file exists
    if (file)
    {
        cout << "Reading Passengers from File " << inputFile << endl;
        string line;
        char delimeter = ',';
        int passengerNum;
        int startTime;
        int startFloor;
        int endFloor;

        // Iterate through lines in the file
        while (file >> line)
        {
            cout << "Line: " << line << endl;
            vector<int> result;
            int splitLoc = 0;
            // Split line at each ',' for CSV
            while (!(splitLoc == string::npos))
            {
                splitLoc = line.find(delimeter);
                // Attempt to read integers preceeding a ','
                if (!(splitLoc == string::npos))
                {
                    string nextValue = line.substr(0, splitLoc);
                    // Attempt to parse integer from line
                    try
                    {
                        result.push_back(stoi(nextValue));
                    }
                    catch (invalid_argument e)
                    {
                        cout << e.what() << endl;
                        break;
                    }
                    line = line.substr(splitLoc + 1);
                }
                // Attempt to read final integer in line
                else
                {
                    // Attempt to parse integer from line
                    try
                    {
                        result.push_back(stoi(line));
                    }
                    catch (invalid_argument e)
                    {
                        cout << e.what() << endl;
                        break;
                    }
                }
            }

            // Create passenger for format with PassengerNumber
            // as column 1
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
            // Create passenger for format with StartTime as
            // column 1
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
} // End function readElevatorInput

/// Primary Simulation Loop
/// 
/// Runs two Elevator sims: one with 10s between floors, and
/// one with 5s between floors, then compares runtimes.
/// Returns exit status
int main()
{
    const int NUM_FLOORS = 100;
    const int NUM_ELEVATORS = 4;
    const int START_SPEED = 10;
    const int NEW_SPEED = 5;

    // Create Bulding with 10s Elevator TimeToFloor
    Building *origBuilding = new Building(NUM_FLOORS,
                                          NUM_ELEVATORS,
                                          START_SPEED);
    // Create Bulding with 5s Elevator TimeToFloor
    Building *newBuilding = new Building(NUM_FLOORS,
                                         NUM_ELEVATORS,
                                         NEW_SPEED);

    // Read Input File
    vector<Passenger*> passengers = readElevatorInput();
    vector<Passenger*> passengersCopy;

    // Add Passengers to Original Building
    for (Passenger* p : passengers)
    {
        // Create Passengers copy for use in new building
        Passenger* newP = new Passenger(0, 0, 0);
        *newP = *p;
        passengersCopy.push_back(newP);

        origBuilding->addPassenger(p);
    }

    // Add Passengers to New Building
    for (Passenger* p : passengersCopy)
    {
        newBuilding->addPassenger(p);
    }

    // Run 10s TimeToFloor Simulation
    cout << "Running Sim with Elevator TimeToFloor " << START_SPEED << endl;
    origBuilding->runElevatorSim();
    double waitTime1 = origBuilding->getAvgWaitTime();
    double travelTime1 = origBuilding->getAvgTravelTime();
    cout << "Sim Complete" << endl;

    cout << "Running Sim with Elevator TimeToFloor " << NEW_SPEED << endl;
    // Run 5s TimeToFloor Simulation
    newBuilding->runElevatorSim();
    double waitTime2 = newBuilding->getAvgWaitTime();
    double travelTime2 = newBuilding->getAvgTravelTime();
    cout << "Sim Complete" << endl;

    // Calculate runtime reductions
    double waitReduction = (waitTime1 - waitTime2) / waitTime1 * 100;
    double travelReduction = (travelTime1 - travelTime2) / travelTime1 * 100;

    // Print results
    cout << "\nFor Elevator Speed " << START_SPEED << ":" << endl;
    cout << "\tAvg Wait Time: " << waitTime1 << " seconds" << endl;
    cout << "\tAvg Travel Time: " << travelTime1 << " seconds" << endl << endl;

    cout << "For Elevator Speed " << NEW_SPEED << ":" << endl;
    cout << "\tAvg Wait Time: " << waitTime2 << " seconds" << endl;
    cout << "\tAvg Travel Time: " << travelTime2 << " seconds" << endl << endl;

    cout << "Wait Time Reduction: " << waitReduction << "%" << endl;
    cout << "Travel Time Reduction: " << travelReduction << "%" << endl;
    
    delete origBuilding;
    delete newBuilding;

    return EXIT_SUCCESS;
} // End function main
