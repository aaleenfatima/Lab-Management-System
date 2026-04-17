#include "attendant.h"
#include <fstream>
#include<iostream>
using namespace std;
Attendant::Attendant(const string& id, const string& name, const string& contactInfo)
    : Person(id, name, ""), contact(contactInfo) { // Empty email for attendant
}

void Attendant::serialize(ofstream& out) const {
    if (!out.good()) return;

    // Serialize base class data
    Person::serialize(out);

    // Serialize attendant-specific data
    size_t len = contact.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(contact.c_str(), len);
}

void Attendant::deserialize(ifstream& in) {
    if (!in.good()) return;

    // Deserialize base class data
    Person::deserialize(in);

    // Deserialize attendant-specific data
    size_t len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    contact.resize(len);
    in.read(&contact[0], len);
}