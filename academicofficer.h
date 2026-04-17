#pragma once

#include "person.h"
#include <string>
#include<iostream>
using namespace std;

class AcademicOfficer : public Person {
public:
    AcademicOfficer(const std::string& id, const std::string& name, const std::string& email);

    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};

