#include "building.h"
#include <fstream>
#include <iostream>

using namespace std;

Building::Building(const string& id, const string& name, const string& loc)
    : buildingId(id), buildingName(name), location(loc) {
}

void Building::addAttendant(const string& attendantId) {
    // Manual search instead of std::find
    bool found = false;
    for (const auto& id : attendantIds) {
        if (id == attendantId) {
            found = true;
            break;
        }
    }
    if (!found) {
        attendantIds.push_back(attendantId);
    }
}

void Building::removeAttendant(const string& attendantId) {
    // Manual search and remove instead of std::find
    for (auto it = attendantIds.begin(); it != attendantIds.end(); ++it) {
        if (*it == attendantId) {
            attendantIds.erase(it);
            break;
        }
    }
}

void Building::serialize(ofstream& out) const {
    if (!out.good()) return;

    // Serialize basic fields
    size_t len = buildingId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(buildingId.c_str(), len);

    len = buildingName.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(buildingName.c_str(), len);

    len = location.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(location.c_str(), len);

    // Serialize attendantIds vector
    size_t attendantCount = attendantIds.size();
    out.write(reinterpret_cast<const char*>(&attendantCount), sizeof(attendantCount));
    for (const auto& attendantId : attendantIds) {
        len = attendantId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(attendantId.c_str(), len);
    }
}

void Building::deserialize(ifstream& in) {
    if (!in.good()) return;

    size_t len;

    // Deserialize basic fields
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buildingId.resize(len);
    in.read(&buildingId[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    buildingName.resize(len);
    in.read(&buildingName[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    location.resize(len);
    in.read(&location[0], len);

    // Deserialize attendantIds vector
    size_t attendantCount;
    in.read(reinterpret_cast<char*>(&attendantCount), sizeof(attendantCount));
    attendantIds.clear();
    for (size_t i = 0; i < attendantCount; ++i) {
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        string attendantId;
        attendantId.resize(len);
        in.read(&attendantId[0], len);
        attendantIds.push_back(attendantId);
    }
}