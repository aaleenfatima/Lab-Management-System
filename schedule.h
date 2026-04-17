#pragma once

#include "datetime.h"
#include <string>
#include <fstream>  // Add this include
#include <iostream>
using namespace std;
enum class DayOfWeek { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

class Schedule {
private:
    DayOfWeek day;
    DateTime startTime;
    DateTime endTime;
    string semester;

public:
    Schedule(DayOfWeek d, const DateTime& start, const DateTime& end, const string& sem);

    // Getters
    DayOfWeek getDay() const { return day; }
    DateTime getStartTime() const { return startTime; }
    DateTime getEndTime() const { return endTime; }
    string getSemester() const { return semester; }

    double getExpectedHours() const;
    bool isScheduledOn(const DateTime& date) const;

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};

