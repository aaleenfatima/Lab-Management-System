#pragma once 

#include <string>
#include <vector>
#include <fstream>  
#include<iostream>
using namespace std;
class Lab {
private:
    string labId;
    string labName;
    string courseCode;
    int creditHours;

public:
    Lab(const string& id, const string& name,
        const string& course, int credits);

    // Getters
    string getLabId() const { return labId; }
    string getLabName() const { return labName; }
    string getCourseCode() const { return courseCode; }
    int getCreditHours() const { return creditHours; }

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};
