#pragma once

#include "person.h"
#include <string>
#include<iostream>
using namespace std;

class Attendant : public Person {
private:
    string contact;

public:
    Attendant(const string& id, const string& name, const string& contactInfo);

    string getContact() const { return contact; }

    void serialize(ofstream& out) const override;
    void deserialize(ifstream& in) override;
};

