#include "ta.h"
#include <fstream>
#include <iostream>
using namespace std;
TA::TA(const string& id, const string& name,
    const string& email, bool graduate)
    : Person(id, name, email), isGraduate(graduate) {
}

void TA::serialize(ofstream& out) const {
    if (!out.good()) return;

    // First serialize the base class data
    Person::serialize(out);

    // Then serialize TA-specific data
    out.write(reinterpret_cast<const char*>(&isGraduate), sizeof(isGraduate));
}

void TA::deserialize(ifstream& in) {
    if (!in.good()) return;

    // First deserialize the base class data
    Person::deserialize(in);

    // Then deserialize TA-specific data
    in.read(reinterpret_cast<char*>(&isGraduate), sizeof(isGraduate));
}