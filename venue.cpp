#include "venue.h"
#include <fstream>
#include <iostream>
using namespace std;

Venue::Venue(const string& id, const string& room, int cap, const string& building)
    : venueId(id), roomNumber(room), capacity(cap), buildingId(building) {
}

void Venue::serialize(ofstream& out) const {
    if (!out.is_open() || !out.good()) {
        cerr << "Error: Cannot serialize Venue - output stream is not good" << endl;
        return;
    }

    try {
        // Serialize venueId
        size_t len = venueId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(venueId.c_str(), len);

        // Serialize roomNumber
        len = roomNumber.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(roomNumber.c_str(), len);

        // Serialize capacity
        out.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));

        // Serialize buildingId
        len = buildingId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(buildingId.c_str(), len);

        // Check if write was successful
        if (out.fail()) {
            throw runtime_error("Failed to write Venue data");
        }
    }
    catch (const exception& e) {
        cerr << "Venue serialization error: " << e.what() << endl;
    }
}

void Venue::deserialize(ifstream& in) {
    if (!in.is_open() || !in.good()) {
        cerr << "Error: Cannot deserialize Venue - input stream is not good" << endl;
        return;
    }

    try {
        size_t len;

        // Deserialize venueId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            venueId.resize(len);
            in.read(&venueId[0], len);
        }

        // Deserialize roomNumber
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            roomNumber.resize(len);
            in.read(&roomNumber[0], len);
        }

        // Deserialize capacity
        in.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));

        // Deserialize buildingId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            buildingId.resize(len);
            in.read(&buildingId[0], len);
        }

        // Check if read was successful
        if (in.fail()) {
            throw runtime_error("Failed to read Venue data");
        }
    }
    catch (const std::exception& e) {
        cerr << "Venue deserialization error: " << e.what() << endl;
    }
}