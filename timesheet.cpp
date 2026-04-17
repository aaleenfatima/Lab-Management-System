#include "timesheet.h"
#include <fstream>
#include <iostream>
using namespace std;
Timesheet::Timesheet(const DateTime& d, const DateTime& start, const DateTime& end,
    bool makeup, const string& attendant, const string& section)
    : date(d), actualStart(start), actualEnd(end),
    isMakeup(makeup), attendantId(attendant), sectionId(section) {
}

double Timesheet::calculateContactHours() const {
    return actualEnd.calculateHoursDifference(actualStart);
}

bool Timesheet::isLeave() const {
    return calculateContactHours() == 0;
}

void Timesheet::serialize(ofstream& out) const {
    if (!out.is_open() || !out.good()) {
        cerr << "Error: Cannot serialize Timesheet - output stream is not good" << endl;
        return;
    }

    try {
        // Serialize date
        date.serialize(out);

        // Serialize actualStart
        actualStart.serialize(out);

        // Serialize actualEnd
        actualEnd.serialize(out);

        // Serialize isMakeup
        out.write(reinterpret_cast<const char*>(&isMakeup), sizeof(isMakeup));

        // Serialize attendantId
        size_t len = attendantId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(attendantId.c_str(), len);

        // Serialize sectionId
        len = sectionId.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(sectionId.c_str(), len);

        // Check if write was successful
        if (out.fail()) {
            throw std::runtime_error("Failed to write Timesheet data");
        }
    }
    catch (const exception& e) {
        cerr << "Timesheet serialization error: " << e.what() << endl;
    }
}

void Timesheet::deserialize(ifstream& in) {
    if (!in.is_open() || !in.good()) {
        cerr << "Error: Cannot deserialize Timesheet - input stream is not good" << endl;
        return;
    }

    try {
        // Deserialize date
        date.deserialize(in);

        // Deserialize actualStart
        actualStart.deserialize(in);

        // Deserialize actualEnd
        actualEnd.deserialize(in);

        // Deserialize isMakeup
        in.read(reinterpret_cast<char*>(&isMakeup), sizeof(isMakeup));

        // Deserialize attendantId
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            attendantId.resize(len);
            in.read(&attendantId[0], len);
        }

        // Deserialize sectionId
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            sectionId.resize(len);
            in.read(&sectionId[0], len);
        }

        // Check if read was successful
        if (in.fail()) {
            throw runtime_error("Failed to read Timesheet data");
        }
    }
    catch (const exception& e) {
        cerr << "Timesheet deserialization error: " << e.what() << endl;
    }
}