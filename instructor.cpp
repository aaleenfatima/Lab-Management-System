#include "instructor.h"
#include <fstream>
#include <iostream>
using namespace std;
Instructor::Instructor(const string& id, const string& name,
    const string& email, const string& dept)
    : Person(id, name, email), department(dept) {
}

void Instructor::serialize(ofstream& out) const {
    if (!out.is_open() || !out.good()) {
        cerr << "Error: Cannot serialize Instructor - output stream is not good" << endl;
        return;
    }

    try {
        // First serialize the base class data
        Person::serialize(out);

        // Then serialize Instructor-specific data
        size_t len = department.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(department.c_str(), len);

        // Check if write was successful
        if (out.fail()) {
            throw runtime_error("Failed to write Instructor data");
        }
    }
    catch (const exception& e) {
        cerr << "Instructor serialization error: " << e.what() << endl;
    }
}

void Instructor::deserialize(ifstream& in) {
    if (!in.is_open() || !in.good()) {
        cerr << "Error: Cannot deserialize Instructor - input stream is not good" << endl;
        return;
    }

    try {
        // First deserialize the base class data
        Person::deserialize(in);

        // Then deserialize Instructor-specific data
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            department.resize(len);
            in.read(&department[0], len);
        }

        // Check if read was successful
        if (in.fail()) {
            throw runtime_error("Failed to read Instructor data");
        }
    }
    catch (const exception& e) {
        cerr << "Instructor deserialization error: " << e.what() << endl;
    }
}