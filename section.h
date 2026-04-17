#pragma once

#include "schedule.h"
#include "instructor.h"
#include "ta.h"
#include "venue.h"
#include "timesheet.h"
#include <vector>
#include <iostream>
using namespace std;

class Section {
private:
    string sectionId;
    string sectionName;
    string labId;
    string instructorId;
    vector<string> taIds;
    string venueId;
    Schedule schedule;

public:
    Section(const string& id, const string& name, const string& labId,
        const string& instructorId, const vector<string>& taIds,
        const string& venueId, const Schedule& sched);

    // Getters
    string getSectionId() const { return sectionId; }
    string getSectionName() const { return sectionName; }
    string getLabId() const { return labId; }
    string getInstructorId() const { return instructorId; }
    vector<string> getTaIds() const { return taIds; }
    string getVenueId() const { return venueId; }
    Schedule getSchedule() const { return schedule; }

    void addTA(const string& taId);
    void removeTA(const string& taId);

    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};