#pragma once

#include "lab.h"
#include "section.h"
#include "instructor.h"
#include "ta.h"
#include "venue.h"
#include "timesheet.h"
#include "report.h"
#include "building.h"
#include "attendant.h"
#include "academicofficer.h"
#include "hod.h"
#include "filemanager.h"
#include "MakeupRequest.h"
#include <vector>
#include <iostream>
#include <memory>
using namespace std;

// Base Service Interface
class IService {
public:
    virtual ~IService() = default;
};

// Specialized Service Interfaces (reduced CBO by inheritance)
class ILabService : public IService {
public:
    virtual void addLab(const Lab& lab) = 0;
    virtual Lab* findLab(const string& labId) = 0;
    virtual const vector<Lab>& getAllLabs() const = 0;
    virtual void loadLabs(const vector<Lab>& labs) = 0;
    virtual vector<Lab> getLabsForSave() const = 0;
};

class ISectionService : public IService {
public:
    virtual void addSection(const Section& section) = 0;
    virtual Section* findSection(const string& sectionId) = 0;
    virtual void assignInstructor(const string& sectionId, const string& instructorId) = 0;
    virtual void assignTA(const string& sectionId, const string& taId) = 0;
    virtual const vector<Section>& getAllSections() const = 0;
    virtual void loadSections(const vector<Section>& sections) = 0;
    virtual vector<Section> getSectionsForSave() const = 0;
    virtual vector<Section> getSectionsByLab(const string& labId) const = 0;
};

class IReportService : public IService {
public:
    virtual Report* generateWeeklyScheduleReport(const DateTime& weekStart,
        const vector<Section>& sections) = 0;
    virtual Report* generateWeeklyTimesheetReport(int weekNumber,
        const vector<Timesheet>& timesheets) = 0;
    virtual Report* generateSemesterReport(const string& labId,
        const vector<Section>& sections,
        const vector<Timesheet>& timesheets) = 0;
    virtual Report* generateLabSemesterTimesheetReport(const string& labId,
        const vector<Section>& sections,
        const vector<Timesheet>& timesheets) = 0;
};

class IMakeupRequestService : public IService {
public:
    virtual void submitRequest(const string& sectionId, const string& instructorId,
        const string& reason, const DateTime& preferredDate) = 0;
    virtual vector<MakeupRequest> getPendingRequests() const = 0;
    virtual bool approveRequest(const string& requestId, const DateTime& scheduledDate,
        const string& approvedBy, vector<Timesheet>& timesheets) = 0;
    virtual bool rejectRequest(const string& requestId, const string& rejectedBy) = 0;
    virtual MakeupRequest* findRequest(const string& requestId) = 0;
    virtual void loadRequests(const vector<MakeupRequest>& requests) = 0;
    virtual vector<MakeupRequest> getRequestsForSave() const = 0;

};

class IUserService : public IService {
public:
    virtual void addInstructor(const Instructor& instructor) = 0;
    virtual void addTA(const TA& ta) = 0;
    virtual void addAttendant(const Attendant& attendant) = 0;
    virtual void addAcademicOfficer(const AcademicOfficer& officer) = 0;
    virtual void addHOD(const HOD& hod) = 0;
    virtual Instructor* findInstructor(const string& instructorId) = 0;
    virtual TA* findTA(const string& taId) = 0;
    virtual Attendant* findAttendant(const string& attendantId) = 0;
    virtual Building* findBuilding(const string& buildingId) = 0;
    virtual void addBuilding(const Building& building) = 0;
    virtual void addVenue(const Venue& venue) = 0;
    virtual void assignAttendantToBuilding(const string& buildingId, const string& attendantId) = 0;
    virtual void loadUsers(const vector<Instructor>& instructors,
        const vector<TA>& tas,
        const vector<Attendant>& attendants,
        const vector<AcademicOfficer>& officers,
        const vector<HOD>& hods,
        const vector<Building>& buildings,
        const vector<Venue>& venues) = 0;
    virtual void getUsersForSave(vector<Instructor>& instructors,
        vector<TA>& tas,
        vector<Attendant>& attendants,
        vector<AcademicOfficer>& officers,
        vector<HOD>& hods,
        vector<Building>& buildings,
        vector<Venue>& venues) const = 0;
};

class ITimesheetService : public IService {
public:
    virtual void fillTimesheet(const Timesheet& timesheet) = 0;
    virtual void updateTimesheet(const string& sectionId, const DateTime& date,
        const DateTime& newStart, const DateTime& newEnd) = 0;
    virtual const vector<Timesheet>& getAllTimesheets() const = 0;
    virtual void loadTimesheets(const vector<Timesheet>& timesheets) = 0;
    virtual vector<Timesheet> getTimesheetsForSave() const = 0;
};

// Service Factory (reduces coupling)
class ServiceFactory {
public:
    static unique_ptr<ILabService> createLabService();
    static unique_ptr<ISectionService> createSectionService();
    static unique_ptr<IReportService> createReportService();
    static unique_ptr<IMakeupRequestService> createMakeupRequestService();
    static unique_ptr<IUserService> createUserService();
    static unique_ptr<ITimesheetService> createTimesheetService();
};

// Data Manager (reduces LCOM)
class DataManager {
private:
    unique_ptr<ILabService> labService;
    unique_ptr<ISectionService> sectionService;
    unique_ptr<ITimesheetService> timesheetService;
    unique_ptr<IUserService> userService;
    unique_ptr<IMakeupRequestService> makeupRequestService;

public:
    DataManager();
    void loadAllData();
    void saveAllData();

    ILabService* getLabService() { return labService.get(); }
    ISectionService* getSectionService() { return sectionService.get(); }
    ITimesheetService* getTimesheetService() { return timesheetService.get(); }
    IUserService* getUserService() { return userService.get(); }
    IMakeupRequestService* getMakeupRequestService() { return makeupRequestService.get(); }
};

// Report Manager (reduces WMC)
class ReportManager {
private:
    unique_ptr<IReportService> reportService;
    DataManager* dataManager;

public:
    ReportManager(DataManager* dm);
    Report* generateWeeklyScheduleReport(const DateTime& weekStart);
    Report* generateWeeklyTimesheetReport(int weekNumber);
    Report* generateSemesterReport(const string& labId);
    Report* generateLabSemesterTimesheetReport(const string& labId);
};

// Request Manager (reduces WMC)
class RequestManager {
private:
    DataManager* dataManager;

public:
    RequestManager(DataManager* dm);
    void submitMakeupRequest(const string& sectionId, const string& instructorId,
        const string& reason, const DateTime& preferredDate);
    vector<MakeupRequest> getPendingMakeupRequests() const;
    bool approveMakeupRequest(const string& requestId, const DateTime& scheduledDate,
        const string& approvedBy);
    bool rejectMakeupRequest(const string& requestId, const string& rejectedBy);
    MakeupRequest* findMakeupRequest(const string& requestId);
};

// Assignment Manager (reduces WMC)
class AssignmentManager {
private:
    DataManager* dataManager;

public:
    AssignmentManager(DataManager* dm);
    void assignInstructorToSection(const string& sectionId, const string& instructorId);
    void assignTAToSection(const string& sectionId, const string& taId);
    void assignAttendantToBuilding(const string& buildingId, const string& attendantId);
};

// Main System (reduced complexity)
class LabManagementSystem {
private:
    unique_ptr<DataManager> dataManager;
    unique_ptr<ReportManager> reportManager;
    unique_ptr<RequestManager> requestManager;
    unique_ptr<AssignmentManager> assignmentManager;

public:
    LabManagementSystem();
    ~LabManagementSystem() = default;

    // Data management
    void loadAllData();
    void saveAllData();

    // Entity additions (delegated)
    void addLab(const Lab& lab);
    void addSection(const Section& section);
    void addInstructor(const Instructor& instructor);
    void addTA(const TA& ta);
    void addVenue(const Venue& venue);
    void addBuilding(const Building& building);
    void addAttendant(const Attendant& attendant);
    void addAcademicOfficer(const AcademicOfficer& officer);
    void addHOD(const HOD& hod);

    // Assignment functions (delegated)
    void assignInstructorToSection(const string& sectionId, const string& instructorId);
    void assignTAToSection(const string& sectionId, const string& taId);
    void assignAttendantToBuilding(const string& buildingId, const string& attendantId);

    // Timesheet functions
    void fillTimesheet(const Timesheet& timesheet);
    void updateTimesheet(const string& sectionId, const DateTime& date,
        const DateTime& newStart, const DateTime& newEnd);

    // Report functions (delegated)
    Report* generateWeeklyScheduleReport(const DateTime& weekStart);
    Report* generateWeeklyTimesheetReport(int weekNumber);
    Report* generateSemesterReport(const string& labId);
    Report* generateLabSemesterTimesheetReport(const string& labId);

    // Makeup Request functions (delegated)
    void submitMakeupRequest(const string& sectionId, const string& instructorId,
        const string& reason, const DateTime& preferredDate);
    vector<MakeupRequest> getPendingMakeupRequests() const;
    bool approveMakeupRequest(const string& requestId, const DateTime& scheduledDate,
        const string& approvedBy);
    bool rejectMakeupRequest(const string& requestId, const string& rejectedBy);
    // In the LabManagementSystem class, add this method:
    void scheduleMakeupLab(const string& sectionId, const Schedule& schedule);

    // Utility methods
    Section* findSection(const string& sectionId);
    Lab* findLab(const string& labId);
    Instructor* findInstructor(const string& instructorId);
    TA* findTA(const string& taId);
    Building* findBuilding(const string& buildingId);
    Attendant* findAttendant(const string& attendantId);
    MakeupRequest* findMakeupRequest(const string& requestId);

    // Getters
    const vector<Section>& getSections() const;
    const vector<Timesheet>& getTimesheets() const;

};