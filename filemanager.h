#pragma once

#include "lab.h"
#include "section.h"
#include "instructor.h"
#include "ta.h"
#include "venue.h"
#include "timesheet.h"
#include "building.h"
#include "attendant.h"
#include "academicofficer.h"
#include "hod.h"
#include "MakeupRequest.h"
#include <vector>
#include <fstream>
#include<iostream>
using namespace std;

class FileManager {
private:
    static const string LABS_FILE;
    static const string SECTIONS_FILE;
    static const string INSTRUCTORS_FILE;
    static const string TAS_FILE;
    static const string VENUES_FILE;
    static const string TIMESHEETS_FILE;
    static const string BUILDINGS_FILE;
    static const string ATTENDANTS_FILE;
    static const string ACADEMIC_OFFICERS_FILE;
    static const string HODS_FILE;
    static const string MAKEUP_REQUESTS_FILE;

public:
    // Save methods
    static void saveLabs(const vector<Lab>& labs);
    static void saveSections(const vector<Section>& sections);
    static void saveInstructors(const vector<Instructor>& instructors);
    static void saveTAs(const vector<TA>& tas);
    static void saveVenues(const vector<Venue>& venues);
    static void saveTimesheets(const vector<Timesheet>& timesheets);
    static void saveBuildings(const vector<Building>& buildings);
    static void saveAttendants(const vector<Attendant>& attendants);
    static void saveAcademicOfficers(const vector<AcademicOfficer>& officers);
    static void saveHODs(const vector<HOD>& hods);
    static void saveMakeupRequests(const vector<MakeupRequest>& requests);

    // Load methods
    static vector<Lab> loadLabs();
    static vector<Section> loadSections();
    static vector<Instructor> loadInstructors();
    static vector<TA> loadTAs();
    static vector<Venue> loadVenues();
    static vector<Timesheet> loadTimesheets();
    static vector<Building> loadBuildings();
    static vector<Attendant> loadAttendants();
    static vector<AcademicOfficer> loadAcademicOfficers();
    static vector<HOD> loadHODs();
    static vector<MakeupRequest> loadMakeupRequests();

};
