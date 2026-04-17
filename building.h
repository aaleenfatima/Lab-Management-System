#pragma once

#include <string>
#include <vector>
#include <fstream>
#include<iostream>
using namespace std;

class Building {
private:
    string buildingId;
    string buildingName;
    string location;
    vector<string> attendantIds;

public:
    Building(const string& id, const string& name, const string& loc);

    // Getters
    string getBuildingId() const { return buildingId; }
    string getBuildingName() const { return buildingName; }
    string getLocation() const { return location; }
    vector<string> getAttendantIds() const { return attendantIds; }

    // Methods
    void addAttendant(const string& attendantId);
    void removeAttendant(const string& attendantId);

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};

