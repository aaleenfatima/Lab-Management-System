#pragma once


#include "person.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class TA : public Person {
private:
    bool isGraduate;

public:
    TA(const string& id, const string& name,
        const string& email, bool graduate);

    bool getIsGraduate() const { return isGraduate; }

    void serialize(ofstream& out) const override;
    void deserialize(ifstream& in) override;
};
