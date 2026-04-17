#include "filemanager.h"
#include <iostream>
using namespace std;
// Define static constants
const string FileManager::LABS_FILE = "labs.dat";
const string FileManager::SECTIONS_FILE = "sections.dat";
const string FileManager::INSTRUCTORS_FILE = "instructors.dat";
const string FileManager::TAS_FILE = "tas.dat";
const string FileManager::VENUES_FILE = "venues.dat";
const string FileManager::TIMESHEETS_FILE = "timesheets.dat";
const string FileManager::BUILDINGS_FILE = "buildings.dat";
const string FileManager::ATTENDANTS_FILE = "attendants.dat";
const string FileManager::ACADEMIC_OFFICERS_FILE = "academic_officers.dat";
const string FileManager::HODS_FILE = "hods.dat";
const string FileManager::MAKEUP_REQUESTS_FILE = "makeup_requests.dat";


// Save implementations
void FileManager::saveLabs(const vector<Lab>& labs) {
    ofstream out(LABS_FILE, ios::binary);
    if (out) {
        size_t size = labs.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& lab : labs) {
            lab.serialize(out);
        }
    }
}

void FileManager::saveSections(const vector<Section>& sections) {
    ofstream out(SECTIONS_FILE, ios::binary);
    if (out) {
        size_t size = sections.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& section : sections) {
            section.serialize(out);
        }
    }
}

void FileManager::saveInstructors(const vector<Instructor>& instructors) {
    ofstream out(INSTRUCTORS_FILE, ios::binary);
    if (out) {
        size_t size = instructors.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& instructor : instructors) {
            instructor.serialize(out);
        }
    }
}

void FileManager::saveTAs(const vector<TA>& tas) {
    ofstream out(TAS_FILE, ios::binary);
    if (out) {
        size_t size = tas.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& ta : tas) {
            ta.serialize(out);
        }
    }
}

void FileManager::saveVenues(const vector<Venue>& venues) {
    ofstream out(VENUES_FILE, ios::binary);
    if (out) {
        size_t size = venues.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& venue : venues) {
            venue.serialize(out);
        }
    }
}

void FileManager::saveTimesheets(const vector<Timesheet>& timesheets) {
    ofstream out(TIMESHEETS_FILE, ios::binary);
    if (out) {
        size_t size = timesheets.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& timesheet : timesheets) {
            timesheet.serialize(out);
        }
    }
}

void FileManager::saveBuildings(const vector<Building>& buildings) {
    ofstream out(BUILDINGS_FILE, ios::binary);
    if (out) {
        size_t size = buildings.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& building : buildings) {
            building.serialize(out);
        }
    }
}

void FileManager::saveAttendants(const vector<Attendant>& attendants) {
    ofstream out(ATTENDANTS_FILE, ios::binary);
    if (out) {
        size_t size = attendants.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& attendant : attendants) {
            attendant.serialize(out);
        }
    }
}

void FileManager::saveAcademicOfficers(const vector<AcademicOfficer>& officers) {
    ofstream out(ACADEMIC_OFFICERS_FILE, ios::binary);
    if (out) {
        size_t size = officers.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& officer : officers) {
            officer.serialize(out);
        }
    }
}

void FileManager::saveHODs(const vector<HOD>& hods) {
    ofstream out(HODS_FILE, ios::binary);
    if (out) {
        size_t size = hods.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& hod : hods) {
            hod.serialize(out);
        }
    }
}

// Load implementations
vector<Lab> FileManager::loadLabs() {
    vector<Lab> labs;
    ifstream in(LABS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Lab lab("", "", "", 0);
            lab.deserialize(in);
            labs.push_back(lab);
        }
    }
    return labs;
}

vector<Section> FileManager::loadSections() {
    vector<Section> sections;
    ifstream in(SECTIONS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Schedule tempSchedule(DayOfWeek::MONDAY, DateTime(), DateTime(), "");
            Section section("", "", "", "", {}, "", tempSchedule);
            section.deserialize(in);
            sections.push_back(section);
        }
    }
    return sections;
}

vector<Instructor> FileManager::loadInstructors() {
    vector<Instructor> instructors;
    ifstream in(INSTRUCTORS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Instructor instructor("", "", "", "");
            instructor.deserialize(in);
            instructors.push_back(instructor);
        }
    }
    return instructors;
}

vector<TA> FileManager::loadTAs() {
    vector<TA> tas;
    ifstream in(TAS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            TA ta("", "", "", false);
            ta.deserialize(in);
            tas.push_back(ta);
        }
    }
    return tas;
}

vector<Venue> FileManager::loadVenues() {
    vector<Venue> venues;
    ifstream in(VENUES_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Venue venue("", "", 0, "");
            venue.deserialize(in);
            venues.push_back(venue);
        }
    }
    return venues;
}

vector<Timesheet> FileManager::loadTimesheets() {
    vector<Timesheet> timesheets;
    ifstream in(TIMESHEETS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Timesheet timesheet(DateTime(), DateTime(), DateTime(), false, "", "");
            timesheet.deserialize(in);
            timesheets.push_back(timesheet);
        }
    }
    return timesheets;
}

vector<Building> FileManager::loadBuildings() {
    vector<Building> buildings;
    ifstream in(BUILDINGS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Building building("", "", "");
            building.deserialize(in);
            buildings.push_back(building);
        }
    }
    return buildings;
}

vector<Attendant> FileManager::loadAttendants() {
    vector<Attendant> attendants;
    ifstream in(ATTENDANTS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            Attendant attendant("", "", "");
            attendant.deserialize(in);
            attendants.push_back(attendant);
        }
    }
    return attendants;
}

vector<AcademicOfficer> FileManager::loadAcademicOfficers() {
    vector<AcademicOfficer> officers;
    ifstream in(ACADEMIC_OFFICERS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            AcademicOfficer officer("", "", "");
            officer.deserialize(in);
            officers.push_back(officer);
        }
    }
    return officers;
}

vector<HOD> FileManager::loadHODs() {
    vector<HOD> hods;
    ifstream in(HODS_FILE, ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            HOD hod("", "", "");
            hod.deserialize(in);
            hods.push_back(hod);
        }
    }
    return hods;
}


void FileManager::saveMakeupRequests(const std::vector<MakeupRequest>& requests) {
    std::ofstream out(MAKEUP_REQUESTS_FILE, std::ios::binary);
    if (out) {
        size_t size = requests.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& request : requests) {
            request.serialize(out);
        }
    }
}

std::vector<MakeupRequest> FileManager::loadMakeupRequests() {
    std::vector<MakeupRequest> requests;
    std::ifstream in(MAKEUP_REQUESTS_FILE, std::ios::binary);
    if (in) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        for (size_t i = 0; i < size; ++i) {
            MakeupRequest request("", "", "", "", DateTime(), DateTime());
            request.deserialize(in);
            requests.push_back(request);
        }
    }
    return requests;
}