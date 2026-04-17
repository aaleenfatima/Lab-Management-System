#pragma once


#include "datetime.h"
#include <string>
#include <fstream>  // Add this include
#include <iostream>
using namespace std;
class Timesheet {
private:
    DateTime date;
    DateTime actualStart;
    DateTime actualEnd;
    bool isMakeup;
    string attendantId;
    string sectionId;

public:
    Timesheet(const DateTime& d, const DateTime& start, const DateTime& end,
        bool makeup, const string& attendant, const string& section);

    // Getters
    DateTime getDate() const { return date; }
    DateTime getActualStart() const { return actualStart; }
    DateTime getActualEnd() const { return actualEnd; }
    bool getIsMakeup() const { return isMakeup; }
    string getAttendantId() const { return attendantId; }
    string getSectionId() const { return sectionId; }

    double calculateContactHours() const;
    bool isLeave() const; // No timesheet entry or 0 hours

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};

