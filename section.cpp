#include "section.h"
#include <fstream>
#include <iostream>
using namespace std;
Section::Section(const string& id, const string& name, const string& labId,
    const string& instructorId, const vector<string>& taIds,
    const string& venueId, const Schedule& sched)
    : sectionId(id), sectionName(name), labId(labId), instructorId(instructorId),
    taIds(taIds), venueId(venueId), schedule(sched) {
}

void Section::addTA(const string& taId) {
    // Manual search instead of std::find
    bool found = false;
    for (const auto& existingTaId : taIds) {
        if (existingTaId == taId) {
            found = true;
            break;
        }
    }
    if (!found) {
        taIds.push_back(taId);
    }
}

void Section::removeTA(const string& taId) {
    // Manual search and remove instead of std::find
    for (auto it = taIds.begin(); it != taIds.end(); ++it) {
        if (*it == taId) {
            taIds.erase(it);
            break;
        }
    }
}

void Section::serialize(ofstream& out) const {
    if (!out.is_open() || !out.good()) {
        cerr << "Error: Cannot serialize Section - output stream is not good" << endl;
        return;
    }

    try {
        // Serialize sectionId
        size_t len = sectionId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(sectionId.c_str(), len);

        // Serialize sectionName
        len = sectionName.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(sectionName.c_str(), len);

        // Serialize labId
        len = labId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(labId.c_str(), len);

        // Serialize instructorId
        len = instructorId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(instructorId.c_str(), len);

        // Serialize taIds vector
        size_t taCount = taIds.size();
        out.write(reinterpret_cast<const char*>(&taCount), sizeof(taCount));
        for (const auto& taId : taIds) {
            len = taId.length();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(taId.c_str(), len);
        }

        // Serialize venueId
        len = venueId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(venueId.c_str(), len);

        // Serialize schedule
        schedule.serialize(out);

        // Check if write was successful
        if (out.fail()) {
            throw runtime_error("Failed to write Section data");
        }
    }
    catch (const exception& e) {
        cerr << "Section serialization error: " << e.what() << endl;
    }
}

void Section::deserialize(ifstream& in) {
    if (!in.is_open() || !in.good()) {
        cerr << "Error: Cannot deserialize Section - input stream is not good" << endl;
        return;
    }

    try {
        size_t len;

        // Deserialize sectionId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            sectionId.resize(len);
            in.read(&sectionId[0], len);
        }

        // Deserialize sectionName
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            sectionName.resize(len);
            in.read(&sectionName[0], len);
        }

        // Deserialize labId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            labId.resize(len);
            in.read(&labId[0], len);
        }

        // Deserialize instructorId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            instructorId.resize(len);
            in.read(&instructorId[0], len);
        }

        // Deserialize taIds vector
        size_t taCount;
        in.read(reinterpret_cast<char*>(&taCount), sizeof(taCount));
        taIds.clear();
        for (size_t i = 0; i < taCount && in.good(); ++i) {
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::string taId;
            taId.resize(len);
            in.read(&taId[0], len);
            taIds.push_back(taId);
        }

        // Deserialize venueId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            venueId.resize(len);
            in.read(&venueId[0], len);
        }

        // Deserialize schedule
        schedule.deserialize(in);

        // Check if read was successful
        if (in.fail()) {
            throw runtime_error("Failed to read Section data");
        }
    }
    catch (const exception& e) {
        cerr << "Section deserialization error: " << e.what() << endl;
    }
}