#pragma once

#include "person.h"
#include <string>
#include <fstream>  // Add this include
#include<iostream>
using namespace std;

class Instructor : public Person {
private:
    string department;

public:
    Instructor(const string& id, const string& name,
        const string& email, const string& dept);

    string getDepartment() const { return department; }

    void serialize(ofstream& out) const override;
    void deserialize(ifstream& in) override;
};
