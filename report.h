#pragma once

#include "section.h"
#include "timesheet.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Base Report constructor implementation
class Report {
protected:
    string reportId;
    DateTime generatedDate;
    string reportType;

public:
    Report(const string& id, const string& type);
    virtual ~Report() = default;

    virtual void generate() = 0;
    virtual void display() const = 0;
    virtual void saveToFile(const string& filename) const = 0;
};

class WeeklyScheduleReport : public Report {
private:
    vector<Section> sections;
    DateTime weekStart;

public:
    WeeklyScheduleReport(const string& id, const DateTime& start);
    void setSections(const vector<Section>& secs) { sections = secs; }

    void generate() override;
    void display() const override;
    void saveToFile(const string& filename) const override;
};

class WeeklyTimesheetReport : public Report {
private:
    vector<Timesheet> timesheets;
    int weekNumber;
    double totalHours;

public:
    WeeklyTimesheetReport(const string& id, int week);
    void setTimesheets(const vector<Timesheet>& sheets) { timesheets = sheets; }

    void generate() override;
    void display() const override;
    void saveToFile(const string& filename) const override;
};

class SemesterReport : public Report {
private:
    string labId;
    vector<Timesheet> timesheets;
    double totalContactHours;
    int totalLeaves;

public:
    SemesterReport(const string& id, const string& labId);
    void setTimesheets(const vector<Timesheet>& sheets) { timesheets = sheets; }

    void generate() override;
    void display() const override;
    void saveToFile(const string& filename) const override;
};

class LabSemesterTimesheetReport : public Report {
private:
    std::string labId;
    std::vector<Timesheet> timesheets;
    std::vector<Section> labSections;
    double totalContactHours;
    int totalSessions;
    int makeupSessions;
    int leaveSessions;

public:
    LabSemesterTimesheetReport(const std::string& id, const std::string& labId);
    void setTimesheets(const std::vector<Timesheet>& sheets) { timesheets = sheets; }
    void setLabSections(const std::vector<Section>& sections) { labSections = sections; }

    void generate() override;
    void display() const override;
    void saveToFile(const std::string& filename) const override;
};