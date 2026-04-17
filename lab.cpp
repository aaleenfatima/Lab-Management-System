#include "lab.h"
#include <fstream>
#include <iostream>
using namespace std;
Lab::Lab(const string& id, const string& name,
    const string& course, int credits)
    : labId(id), labName(name), courseCode(course), creditHours(credits) {
}

void Lab::serialize(ofstream& out) const {
    if (!out.is_open() || !out.good()) {
        cerr << "Error: Cannot serialize Lab - output stream is not good" << endl;
        return;
    }

    try {
        // Serialize labId
        size_t len = labId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(labId.c_str(), len);

        // Serialize labName
        len = labName.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(labName.c_str(), len);

        // Serialize courseCode
        len = courseCode.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(courseCode.c_str(), len);

        // Serialize creditHours
        out.write(reinterpret_cast<const char*>(&creditHours), sizeof(creditHours));

        // Check if write was successful
        if (out.fail()) {
            throw runtime_error("Failed to write Lab data");
        }
    }
    catch (const exception& e) {
        cerr << "Lab serialization error: " << e.what() << endl;
    }
}

void Lab::deserialize(ifstream& in) {
    if (!in.is_open() || !in.good()) {
        cerr << "Error: Cannot deserialize Lab - input stream is not good" << endl;
        return;
    }

    try {
        size_t len;

        // Deserialize labId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            labId.resize(len);
            in.read(&labId[0], len);
        }

        // Deserialize labName
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            labName.resize(len);
            in.read(&labName[0], len);
        }

        // Deserialize courseCode
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            courseCode.resize(len);
            in.read(&courseCode[0], len);
        }

        // Deserialize creditHours
        in.read(reinterpret_cast<char*>(&creditHours), sizeof(creditHours));

        // Check if read was successful
        if (in.fail()) {
            throw runtime_error("Failed to read Lab data");
        }
    }
    catch (const exception& e) {
        cerr << "Lab deserialization error: " << e.what() << endl;
    }
}