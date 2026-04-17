#include "labmanagementsystem.h"
#include <iostream>
using namespace std;

// Concrete Service Implementations
class LabServiceImpl : public ILabService {
private:
    vector<Lab> labs;
public:
    void addLab(const Lab& lab) override { labs.push_back(lab); }

    Lab* findLab(const string& labId) override {
        for (auto& lab : labs) {
            if (lab.getLabId() == labId) return &lab;
        }
        return nullptr;
    }

    const vector<Lab>& getAllLabs() const override { return labs; }
    void loadLabs(const vector<Lab>& loadedLabs) override { labs = loadedLabs; }
    vector<Lab> getLabsForSave() const override { return labs; }
};

class SectionServiceImpl : public ISectionService {
private:
    vector<Section> sections;
public:
    void addSection(const Section& section) override { sections.push_back(section); }

    Section* findSection(const string& sectionId) override {
        for (auto& section : sections) {
            if (section.getSectionId() == sectionId) return &section;
        }
        return nullptr;
    }

    void assignInstructor(const string& sectionId, const string& instructorId) override {
        if (findSection(sectionId)) {
            cout << "Instructor " << instructorId << " assigned to section " << sectionId << endl;
        }
    }

    void assignTA(const string& sectionId, const string& taId) override {
        Section* section = findSection(sectionId);
        if (section) {
            section->addTA(taId);
            cout << "TA " << taId << " assigned to section " << sectionId << endl;
        }
    }

    const vector<Section>& getAllSections() const override { return sections; }
    void loadSections(const vector<Section>& loadedSections) override { sections = loadedSections; }
    vector<Section> getSectionsForSave() const override { return sections; }

    vector<Section> getSectionsByLab(const string& labId) const override {
        vector<Section> result;
        for (const auto& section : sections) {
            if (section.getLabId() == labId) result.push_back(section);
        }
        return result;
    }
};

class ReportServiceImpl : public IReportService {
public:
    Report* generateWeeklyScheduleReport(const DateTime& weekStart,
        const vector<Section>& sections) override {
        auto* report = new WeeklyScheduleReport("WSR_" + to_string(time(0)), weekStart);
        report->setSections(sections);
        report->generate();
        return report;
    }

    Report* generateWeeklyTimesheetReport(int weekNumber,
        const vector<Timesheet>& timesheets) override {
        auto* report = new WeeklyTimesheetReport("WTR_" + to_string(time(0)), weekNumber);
        report->setTimesheets(timesheets);
        report->generate();
        return report;
    }

    Report* generateSemesterReport(const string& labId,
        const vector<Section>& sections,
        const vector<Timesheet>& timesheets) override {
        auto* report = new SemesterReport("SR_" + to_string(time(0)), labId);
        vector<Timesheet> labTimesheets;

        for (const auto& section : sections) {
            if (section.getLabId() == labId) {
                for (const auto& ts : timesheets) {
                    if (ts.getSectionId() == section.getSectionId()) {
                        labTimesheets.push_back(ts);
                    }
                }
            }
        }

        report->setTimesheets(labTimesheets);
        report->generate();
        return report;
    }

    Report* generateLabSemesterTimesheetReport(const string& labId,
        const vector<Section>& sections,
        const vector<Timesheet>& timesheets) override {
        auto* report = new LabSemesterTimesheetReport("LSTR_" + to_string(time(0)), labId);
        vector<Timesheet> labTimesheets;
        vector<Section> labSections;

        for (const auto& section : sections) {
            if (section.getLabId() == labId) {
                labSections.push_back(section);
                for (const auto& ts : timesheets) {
                    if (ts.getSectionId() == section.getSectionId()) {
                        labTimesheets.push_back(ts);
                    }
                }
            }
        }

        report->setTimesheets(labTimesheets);
        report->setLabSections(labSections);
        report->generate();
        return report;
    }
};

class MakeupRequestServiceImpl : public IMakeupRequestService {
private:
    vector<MakeupRequest> makeupRequests;
public:
    void submitRequest(const string& sectionId, const string& instructorId,
        const string& reason, const DateTime& preferredDate) override {
        string requestId = "REQ_" + to_string(time(0));
        MakeupRequest request(requestId, sectionId, instructorId, reason, DateTime(), preferredDate);
        makeupRequests.push_back(request);
        cout << "Makeup request submitted successfully! Request ID: " << requestId << endl;
    }

    vector<MakeupRequest> getPendingRequests() const override {
        vector<MakeupRequest> pending;
        for (const auto& request : makeupRequests) {
            if (request.getStatus() == "PENDING") pending.push_back(request);
        }
        return pending;
    }

    bool approveRequest(const string& requestId, const DateTime& scheduledDate,
        const string& approvedBy, vector<Timesheet>& timesheets) override {
        MakeupRequest* request = findRequest(requestId);
        if (request && request->getStatus() == "PENDING") {
            request->approve(scheduledDate, approvedBy);
            Timesheet makeupTimesheet(scheduledDate, scheduledDate, scheduledDate,
                true, "SYSTEM", request->getSectionId());
            timesheets.push_back(makeupTimesheet);
            return true;
        }
        return false;
    }

    bool rejectRequest(const string& requestId, const string& rejectedBy) override {
        MakeupRequest* request = findRequest(requestId);
        if (request && request->getStatus() == "PENDING") {
            request->reject(rejectedBy);
            return true;
        }
        return false;
    }

    MakeupRequest* findRequest(const string& requestId) override {
        for (auto& request : makeupRequests) {
            if (request.getRequestId() == requestId) return &request;
        }
        return nullptr;
    }

    void loadRequests(const vector<MakeupRequest>& requests) override {
        makeupRequests = requests;
    }

    vector<MakeupRequest> getRequestsForSave() const override {
        return makeupRequests;
    }
}; 

class UserServiceImpl : public IUserService {
private:
    vector<Instructor> instructors;
    vector<TA> tas;
    vector<Attendant> attendants;
    vector<AcademicOfficer> academicOfficers;
    vector<HOD> hods;
    vector<Building> buildings;
    vector<Venue> venues;

public:
    void addInstructor(const Instructor& instructor) override { instructors.push_back(instructor); }
    void addTA(const TA& ta) override { tas.push_back(ta); }
    void addAttendant(const Attendant& attendant) override { attendants.push_back(attendant); }
    void addAcademicOfficer(const AcademicOfficer& officer) override { academicOfficers.push_back(officer); }
    void addHOD(const HOD& hod) override { hods.push_back(hod); }
    void addBuilding(const Building& building) override { buildings.push_back(building); }
    void addVenue(const Venue& venue) override { venues.push_back(venue); }

    Instructor* findInstructor(const string& instructorId) override {
        for (auto& instructor : instructors) {
            if (instructor.getId() == instructorId) return &instructor;
        }
        return nullptr;
    }

    TA* findTA(const string& taId) override {
        for (auto& ta : tas) {
            if (ta.getId() == taId) return &ta;
        }
        return nullptr;
    }

    Attendant* findAttendant(const string& attendantId) override {
        for (auto& attendant : attendants) {
            if (attendant.getId() == attendantId) return &attendant;
        }
        return nullptr;
    }

    Building* findBuilding(const string& buildingId) override {
        for (auto& building : buildings) {
            if (building.getBuildingId() == buildingId) return &building;
        }
        return nullptr;
    }

    void assignAttendantToBuilding(const string& buildingId, const string& attendantId) override {
        Building* building = findBuilding(buildingId);
        if (building) {
            building->addAttendant(attendantId);
            cout << "Attendant " << attendantId << " assigned to building " << buildingId << endl;
        }
    }

    void loadUsers(const vector<Instructor>& loadedInstructors,
        const vector<TA>& loadedTAs,
        const vector<Attendant>& loadedAttendants,
        const vector<AcademicOfficer>& loadedOfficers,
        const vector<HOD>& loadedHODs,
        const vector<Building>& loadedBuildings,
        const vector<Venue>& loadedVenues) override {
        instructors = loadedInstructors;
        tas = loadedTAs;
        attendants = loadedAttendants;
        academicOfficers = loadedOfficers;
        hods = loadedHODs;
        buildings = loadedBuildings;
        venues = loadedVenues;
    }

    void getUsersForSave(vector<Instructor>& outInstructors,
        vector<TA>& outTAs,
        vector<Attendant>& outAttendants,
        vector<AcademicOfficer>& outOfficers,
        vector<HOD>& outHODs,
        vector<Building>& outBuildings,
        vector<Venue>& outVenues) const override {
        outInstructors = instructors;
        outTAs = tas;
        outAttendants = attendants;
        outOfficers = academicOfficers;
        outHODs = hods;
        outBuildings = buildings;
        outVenues = venues;
    }
};

class TimesheetServiceImpl : public ITimesheetService {
private:
    vector<Timesheet> timesheets;
public:
    void fillTimesheet(const Timesheet& timesheet) override {
        timesheets.push_back(timesheet);
    }

    void updateTimesheet(const string& sectionId, const DateTime& date,
        const DateTime& newStart, const DateTime& newEnd) override {
        for (auto& ts : timesheets) {
            if (ts.getSectionId() == sectionId && ts.getDate().isSameDay(date)) {
                Timesheet updated(date, newStart, newEnd, ts.getIsMakeup(),
                    ts.getAttendantId(), sectionId);
                ts = updated;
                cout << "Timesheet updated for section " << sectionId << " on " << date.toString() << endl;
                return;
            }
        }
        cout << "Timesheet not found for section " << sectionId << " on " << date.toString() << endl;
    }

    const vector<Timesheet>& getAllTimesheets() const override { return timesheets; }
    void loadTimesheets(const vector<Timesheet>& loadedTimesheets) override { timesheets = loadedTimesheets; }
    vector<Timesheet> getTimesheetsForSave() const override { return timesheets; }
};

// Service Factory Implementation
unique_ptr<ILabService> ServiceFactory::createLabService() {
    return make_unique<LabServiceImpl>();
}

unique_ptr<ISectionService> ServiceFactory::createSectionService() {
    return make_unique<SectionServiceImpl>();
}

unique_ptr<IReportService> ServiceFactory::createReportService() {
    return make_unique<ReportServiceImpl>();
}

unique_ptr<IMakeupRequestService> ServiceFactory::createMakeupRequestService() {
    return make_unique<MakeupRequestServiceImpl>();
}

unique_ptr<IUserService> ServiceFactory::createUserService() {
    return make_unique<UserServiceImpl>();
}

unique_ptr<ITimesheetService> ServiceFactory::createTimesheetService() {
    return make_unique<TimesheetServiceImpl>();
}

// DataManager Implementation
DataManager::DataManager() {
    labService = ServiceFactory::createLabService();
    sectionService = ServiceFactory::createSectionService();
    timesheetService = ServiceFactory::createTimesheetService();
    userService = ServiceFactory::createUserService();
    makeupRequestService = ServiceFactory::createMakeupRequestService();
}

void DataManager::loadAllData() {
    labService->loadLabs(FileManager::loadLabs());
    sectionService->loadSections(FileManager::loadSections());
    makeupRequestService->loadRequests(FileManager::loadMakeupRequests());
    timesheetService->loadTimesheets(FileManager::loadTimesheets());
    userService->loadUsers(
        FileManager::loadInstructors(),
        FileManager::loadTAs(),
        FileManager::loadAttendants(),
        FileManager::loadAcademicOfficers(),
        FileManager::loadHODs(),
        FileManager::loadBuildings(),
        FileManager::loadVenues()
    );
}

void DataManager::saveAllData() {
    FileManager::saveLabs(labService->getLabsForSave());
    FileManager::saveSections(sectionService->getSectionsForSave());
    FileManager::saveMakeupRequests(makeupRequestService->getRequestsForSave());
    FileManager::saveTimesheets(timesheetService->getTimesheetsForSave());

    vector<Instructor> instructors;
    vector<TA> tas;
    vector<Attendant> attendants;
    vector<AcademicOfficer> officers;
    vector<HOD> hods;
    vector<Building> buildings;
    vector<Venue> venues;

    userService->getUsersForSave(instructors, tas, attendants, officers, hods, buildings, venues);

    FileManager::saveInstructors(instructors);
    FileManager::saveTAs(tas);
    FileManager::saveAttendants(attendants);
    FileManager::saveAcademicOfficers(officers);
    FileManager::saveHODs(hods);
    FileManager::saveBuildings(buildings);
    FileManager::saveVenues(venues);
}

// ReportManager Implementation
ReportManager::ReportManager(DataManager* dm) : dataManager(dm) {
    reportService = ServiceFactory::createReportService();
}

Report* ReportManager::generateWeeklyScheduleReport(const DateTime& weekStart) {
    return reportService->generateWeeklyScheduleReport(weekStart,
        dataManager->getSectionService()->getAllSections());
}

Report* ReportManager::generateWeeklyTimesheetReport(int weekNumber) {
    return reportService->generateWeeklyTimesheetReport(weekNumber,
        dataManager->getTimesheetService()->getAllTimesheets());
}

Report* ReportManager::generateSemesterReport(const string& labId) {
    return reportService->generateSemesterReport(labId,
        dataManager->getSectionService()->getAllSections(),
        dataManager->getTimesheetService()->getAllTimesheets());
}

Report* ReportManager::generateLabSemesterTimesheetReport(const string& labId) {
    return reportService->generateLabSemesterTimesheetReport(labId,
        dataManager->getSectionService()->getAllSections(),
        dataManager->getTimesheetService()->getAllTimesheets());
}

// RequestManager Implementation
RequestManager::RequestManager(DataManager* dm) : dataManager(dm) {}

void RequestManager::submitMakeupRequest(const string& sectionId, const string& instructorId,
    const string& reason, const DateTime& preferredDate) {
    dataManager->getMakeupRequestService()->submitRequest(sectionId, instructorId, reason, preferredDate);
}

vector<MakeupRequest> RequestManager::getPendingMakeupRequests() const {
    return dataManager->getMakeupRequestService()->getPendingRequests();
}

bool RequestManager::approveMakeupRequest(const string& requestId, const DateTime& scheduledDate,
    const string& approvedBy) {
    return dataManager->getMakeupRequestService()->approveRequest(requestId, scheduledDate, approvedBy,
        const_cast<vector<Timesheet>&>(dataManager->getTimesheetService()->getAllTimesheets()));
}

bool RequestManager::rejectMakeupRequest(const string& requestId, const string& rejectedBy) {
    return dataManager->getMakeupRequestService()->rejectRequest(requestId, rejectedBy);
}

MakeupRequest* RequestManager::findMakeupRequest(const string& requestId) {
    return dataManager->getMakeupRequestService()->findRequest(requestId);
}

// AssignmentManager Implementation
AssignmentManager::AssignmentManager(DataManager* dm) : dataManager(dm) {}

void AssignmentManager::assignInstructorToSection(const string& sectionId, const string& instructorId) {
    dataManager->getSectionService()->assignInstructor(sectionId, instructorId);
}

void AssignmentManager::assignTAToSection(const string& sectionId, const string& taId) {
    dataManager->getSectionService()->assignTA(sectionId, taId);
}

void AssignmentManager::assignAttendantToBuilding(const string& buildingId, const string& attendantId) {
    dataManager->getUserService()->assignAttendantToBuilding(buildingId, attendantId);
}

// LabManagementSystem Implementation
LabManagementSystem::LabManagementSystem() {
    dataManager = make_unique<DataManager>();
    reportManager = make_unique<ReportManager>(dataManager.get());
    requestManager = make_unique<RequestManager>(dataManager.get());
    assignmentManager = make_unique<AssignmentManager>(dataManager.get());
}

void LabManagementSystem::loadAllData() {
    dataManager->loadAllData();
}

void LabManagementSystem::saveAllData() {
    dataManager->saveAllData();
}

void LabManagementSystem::addLab(const Lab& lab) {
    dataManager->getLabService()->addLab(lab);
}

void LabManagementSystem::addSection(const Section& section) {
    dataManager->getSectionService()->addSection(section);
}

void LabManagementSystem::addInstructor(const Instructor& instructor) {
    dataManager->getUserService()->addInstructor(instructor);
}

void LabManagementSystem::addTA(const TA& ta) {
    dataManager->getUserService()->addTA(ta);
}

void LabManagementSystem::addVenue(const Venue& venue) {
    dataManager->getUserService()->addVenue(venue);
}

void LabManagementSystem::addBuilding(const Building& building) {
    dataManager->getUserService()->addBuilding(building);
}

void LabManagementSystem::addAttendant(const Attendant& attendant) {
    dataManager->getUserService()->addAttendant(attendant);
}

void LabManagementSystem::addAcademicOfficer(const AcademicOfficer& officer) {
    dataManager->getUserService()->addAcademicOfficer(officer);
}

void LabManagementSystem::addHOD(const HOD& hod) {
    dataManager->getUserService()->addHOD(hod);
}

void LabManagementSystem::assignInstructorToSection(const string& sectionId, const string& instructorId) {
    assignmentManager->assignInstructorToSection(sectionId, instructorId);
}

void LabManagementSystem::assignTAToSection(const string& sectionId, const string& taId) {
    assignmentManager->assignTAToSection(sectionId, taId);
}

void LabManagementSystem::assignAttendantToBuilding(const string& buildingId, const string& attendantId) {
    assignmentManager->assignAttendantToBuilding(buildingId, attendantId);
}

void LabManagementSystem::fillTimesheet(const Timesheet& timesheet) {
    dataManager->getTimesheetService()->fillTimesheet(timesheet);
}

void LabManagementSystem::updateTimesheet(const string& sectionId, const DateTime& date,
    const DateTime& newStart, const DateTime& newEnd) {
    dataManager->getTimesheetService()->updateTimesheet(sectionId, date, newStart, newEnd);
}

Report* LabManagementSystem::generateWeeklyScheduleReport(const DateTime& weekStart) {
    return reportManager->generateWeeklyScheduleReport(weekStart);
}

Report* LabManagementSystem::generateWeeklyTimesheetReport(int weekNumber) {
    return reportManager->generateWeeklyTimesheetReport(weekNumber);
}

Report* LabManagementSystem::generateSemesterReport(const string& labId) {
    return reportManager->generateSemesterReport(labId);
}

Report* LabManagementSystem::generateLabSemesterTimesheetReport(const string& labId) {
    return reportManager->generateLabSemesterTimesheetReport(labId);
}

void LabManagementSystem::submitMakeupRequest(const string& sectionId, const string& instructorId,
    const string& reason, const DateTime& preferredDate) {
    requestManager->submitMakeupRequest(sectionId, instructorId, reason, preferredDate);
}

vector<MakeupRequest> LabManagementSystem::getPendingMakeupRequests() const {
    return requestManager->getPendingMakeupRequests();
}

bool LabManagementSystem::approveMakeupRequest(const string& requestId, const DateTime& scheduledDate,
    const string& approvedBy) {
    return requestManager->approveMakeupRequest(requestId, scheduledDate, approvedBy);
}

bool LabManagementSystem::rejectMakeupRequest(const string& requestId, const string& rejectedBy) {
    return requestManager->rejectMakeupRequest(requestId, rejectedBy);
}

Section* LabManagementSystem::findSection(const string& sectionId) {
    return dataManager->getSectionService()->findSection(sectionId);
}

Lab* LabManagementSystem::findLab(const string& labId) {
    return dataManager->getLabService()->findLab(labId);
}

Instructor* LabManagementSystem::findInstructor(const string& instructorId) {
    return dataManager->getUserService()->findInstructor(instructorId);
}

TA* LabManagementSystem::findTA(const string& taId) {
    return dataManager->getUserService()->findTA(taId);
}

Building* LabManagementSystem::findBuilding(const string& buildingId) {
    return dataManager->getUserService()->findBuilding(buildingId);
}

Attendant* LabManagementSystem::findAttendant(const string& attendantId) {
    return dataManager->getUserService()->findAttendant(attendantId);
}

MakeupRequest* LabManagementSystem::findMakeupRequest(const string& requestId) {
    return requestManager->findMakeupRequest(requestId);
}

const vector<Section>& LabManagementSystem::getSections() const {
    return dataManager->getSectionService()->getAllSections();
}

const vector<Timesheet>& LabManagementSystem::getTimesheets() const {
    return dataManager->getTimesheetService()->getAllTimesheets();
}
void LabManagementSystem::scheduleMakeupLab(const string& sectionId, const Schedule& schedule) {
    Section* section = findSection(sectionId);
    if (section) {
        cout << "Makeup lab scheduled for section: " << sectionId << endl;
        cout << "Day: " << static_cast<int>(schedule.getDay()) << endl;
        cout << "Time: " << schedule.getStartTime().toTimeString() << " - "
            << schedule.getEndTime().toTimeString() << endl;
    }
    else {
        cout << "Section not found: " << sectionId << endl;
    }
}