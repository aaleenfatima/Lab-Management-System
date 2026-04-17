#include<iostream>
#include "academicofficer.h"
#include <fstream>
using namespace std;

AcademicOfficer::AcademicOfficer(const string& id, const string& name, const string& email)
    : Person(id, name, email) {
}

void AcademicOfficer::serialize(ofstream& out) const {
    if (!out.good()) return;
    Person::serialize(out);
}

void AcademicOfficer::deserialize(ifstream& in) {
    if (!in.good()) return;
    Person::deserialize(in);
}