#include "hod.h"
#include <fstream>
#include<iostream>
using namespace std;

HOD::HOD(const string& id, const string& name, const string& email)
    : Person(id, name, email) {
}

void HOD::serialize(ofstream& out) const {
    if (!out.good()) return;
    Person::serialize(out);
}

void HOD::deserialize(ifstream& in) {
    if (!in.good()) return;
    Person::deserialize(in);
}