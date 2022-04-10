#pragma once
class Passenger
{
public:
    Passenger(int startFloor, int endFloor, int startTime);

    int getStartFloor() { return this->startFloor; };
    int getEndFloor() { return this->endFloor; };
    int getStartTime() { return this->startTime; };
    int getWaitTime() { return this->waitTime; };
    int getTravelTime() { return this->travelTime; };

    // Override comparitor operators to compare Passengers
    bool operator<(const Passenger &passenger);
    bool operator>(const Passenger &passenger);
    bool operator==(const Passenger &passenger);

private:
    int startFloor;
    int endFloor;
    int startTime;
    int waitTime = 0;
    int travelTime = 0;
};
