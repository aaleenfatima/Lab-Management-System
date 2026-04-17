#include "schedule.h"
#include <fstream>
#include <iostream>
using namespace std;

Schedule::Schedule(DayOfWeek d, const DateTime& start, const DateTime& end, const string& sem)
    : day(d), startTime(start), endTime(end), semester(sem) {
}

double Schedule::getExpectedHours() const {
    return endTime.calculateHoursDifference(startTime);
}

bool Schedule::isScheduledOn(const DateTime& date) const {
    // This is a simplified implementation
    // In a real system, you'd need to check if the date falls within the semester
    // and matches the scheduled day of week
    return true; // Placeholder implementation
}

void Schedule::serialize(ofstream& out) const {
    if (!out.is_open() || !out.good()) {
        cerr << "Error: Cannot serialize Schedule - output stream is not good" << endl;
        return;
    }

    try {
        // Serialize day (convert enum to int for storage)
        int dayInt = static_cast<int>(day);
        out.write(reinterpret_cast<const char*>(&dayInt), sizeof(dayInt));

        // Serialize startTime
        startTime.serialize(out);

        // Serialize endTime
        endTime.serialize(out);

        // Serialize semester
        size_t len = semester.length();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(semester.c_str(), len);

        // Check if write was successful
        if (out.fail()) {
            throw runtime_error("Failed to write Schedule data");
        }
    }
    catch (const exception& e) {
        cerr << "Schedule serialization error: " << e.what() << endl;
    }
}

void Schedule::deserialize(ifstream& in) {
    if (!in.is_open() || !in.good()) {
        cerr << "Error: Cannot deserialize Schedule - input stream is not good" << endl;
        return;
    }

    try {
        // Deserialize day (read as int and convert back to enum)
        int dayInt;
        in.read(reinterpret_cast<char*>(&dayInt), sizeof(dayInt));
        day = static_cast<DayOfWeek>(dayInt);

        // Deserialize startTime
        startTime.deserialize(in);

        // Deserialize endTime
        endTime.deserialize(in);

        // Deserialize semester
        size_t len;
        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (in.good()) {
            semester.resize(len);
            in.read(&semester[0], len);
        }

        // Check if read was successful
        if (in.fail()) {
            throw runtime_error("Failed to read Schedule data");
        }
    }
    catch (const exception& e) {
        cerr << "Schedule deserialization error: " << e.what() << endl;
    }
}