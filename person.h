#pragma once

#include <string>
#include <fstream>  // Add this
#include <iostream>
using namespace std;

class Person {
protected:
    string id;
    string name;
    string email;

public:
    Person(const string& id, const string& name, const string& email);
    virtual ~Person() = default;

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    // Serialization - add these declarations
    virtual void serialize(ofstream& out) const;
    virtual void deserialize(ifstream& in);
};

