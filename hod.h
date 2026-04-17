#pragma once

#include "person.h"
#include <string>
#include<iostream>
using namespace std;

class HOD : public Person {
public:
    HOD(const string& id, const string& name, const string& email);

    void serialize(ofstream& out) const override;
    void deserialize(ifstream& in) override;
};

