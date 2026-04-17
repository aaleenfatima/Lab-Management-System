#pragma once

#include <string>
#include <fstream>  
#include <iostream>
using namespace std;

class Venue {
private:
    string venueId;
    string roomNumber;
    int capacity;
    string buildingId;

public:
    Venue(const string& id, const string& room, int cap, const string& building);

    // Getters
    string getVenueId() const { return venueId; }
    string getRoomNumber() const { return roomNumber; }
    int getCapacity() const { return capacity; }
    string getBuildingId() const { return buildingId; }

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};

