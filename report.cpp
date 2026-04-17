#include "Report.h"
#include <iostream>
#include <fstream>
#include <iomanip>

// Base Report constructor implementation
Report::Report(const std::string& id, const std::string& type)
    : reportId(id), reportType(type) {
    generatedDate = DateTime(); // Current date/time
}

// WeeklyScheduleReport Implementation
WeeklyScheduleReport::WeeklyScheduleReport(const std::string& id, const DateTime& start)
    : Report(id, "Weekly Schedule Report"), weekStart(start) {
}

void WeeklyScheduleReport::generate() {
    std::cout << "Generating Weekly Schedule Report..." << std::endl;
}

void WeeklyScheduleReport::display() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "WEEKLY SCHEDULE REPORT" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Report ID: " << reportId << std::endl;
    std::cout << "Generated: " << generatedDate.toFullString() << std::endl;
    std::cout << "Week Starting: " << weekStart.toString() << std::endl;
    std::cout << "Total Sections: " << sections.size() << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    if (sections.empty()) {
        std::cout << "No sections scheduled for this week." << std::endl;
    }
    else {
        // Table header
        std::cout << std::left
            << std::setw(12) << "Section ID"
            << std::setw(20) << "Section Name"
            << std::setw(10) << "Lab ID"
            << std::setw(15) << "Day"
            << std::setw(12) << "Start Time"
            << std::setw(12) << "End Time"
            << std::setw(10) << "Duration"
            << std::setw(15) << "Instructor"
            << std::setw(10) << "Venue"
            << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (const auto& section : sections) {
            Schedule sched = section.getSchedule();
            double duration = sched.getExpectedHours();

            // Convert DayOfWeek to string
            std::string dayStr;
            switch (sched.getDay()) {
            case DayOfWeek::MONDAY: dayStr = "Monday"; break;
            case DayOfWeek::TUESDAY: dayStr = "Tuesday"; break;
            case DayOfWeek::WEDNESDAY: dayStr = "Wednesday"; break;
            case DayOfWeek::THURSDAY: dayStr = "Thursday"; break;
            case DayOfWeek::FRIDAY: dayStr = "Friday"; break;
            case DayOfWeek::SATURDAY: dayStr = "Saturday"; break;
            case DayOfWeek::SUNDAY: dayStr = "Sunday"; break;
            }

            std::cout << std::left
                << std::setw(12) << section.getSectionId()
                << std::setw(20) << (section.getSectionName().length() > 18 ?
                    section.getSectionName().substr(0, 17) + "." :
                    section.getSectionName())
                << std::setw(10) << section.getLabId()
                << std::setw(15) << dayStr
                << std::setw(12) << sched.getStartTime().toTimeString()
                << std::setw(12) << sched.getEndTime().toTimeString()
                << std::setw(10) << std::fixed << std::setprecision(1) << duration << "h"
                << std::setw(15) << (section.getInstructorId().length() > 13 ?
                    section.getInstructorId().substr(0, 12) + "." :
                    section.getInstructorId())
                << std::setw(10) << section.getVenueId()
                << std::endl;
        }
    }
    std::cout << std::string(80, '=') << std::endl;
}

void WeeklyScheduleReport::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (out) {
        out << "WEEKLY SCHEDULE REPORT\n";
        out << "=====================\n";
        out << "Report ID: " << reportId << "\n";
        out << "Generated: " << generatedDate.toFullString() << "\n";
        out << "Week Starting: " << weekStart.toString() << "\n";
        out << "Total Sections: " << sections.size() << "\n\n";

        if (sections.empty()) {
            out << "No sections scheduled for this week.\n";
        }
        else {
            out << "SCHEDULE DETAILS:\n";
            out << "-----------------------------------------------------------------------------------------------------------\n";
            out << "Section ID   Section Name        Lab ID   Day   Start Time  End Time  Duration  Instructor    Venue\n";
            out << "-----------------------------------------------------------------------------------------------------------\n";

            for (const auto& section : sections) {
                Schedule sched = section.getSchedule();
                double duration = sched.getExpectedHours();

                std::string dayStr;
                switch (sched.getDay()) {
                case DayOfWeek::MONDAY: dayStr = "Monday"; break;
                case DayOfWeek::TUESDAY: dayStr = "Tuesday"; break;
                case DayOfWeek::WEDNESDAY: dayStr = "Wednesday"; break;
                case DayOfWeek::THURSDAY: dayStr = "Thursday"; break;
                case DayOfWeek::FRIDAY: dayStr = "Friday"; break;
                case DayOfWeek::SATURDAY: dayStr = "Saturday"; break;
                case DayOfWeek::SUNDAY: dayStr = "Sunday"; break;
                }

                out << std::left
                    << std::setw(12) << section.getSectionId()
                    << std::setw(19) << (section.getSectionName().length() > 17 ?
                        section.getSectionName().substr(0, 16) + "." :
                        section.getSectionName())
                    << std::setw(9) << section.getLabId()
                    << std::setw(12) << dayStr
                    << std::setw(11) << sched.getStartTime().toTimeString()
                    << std::setw(10) << sched.getEndTime().toTimeString()
                    << std::setw(9) << std::fixed << std::setprecision(1) << duration << "h"
                    << std::setw(14) << section.getInstructorId()
                    << std::setw(10) << section.getVenueId()
                    << "\n";
            }
        }
        out << "\n=== END OF REPORT ===";
    }
}

// WeeklyTimesheetReport Implementation
WeeklyTimesheetReport::WeeklyTimesheetReport(const std::string& id, int week)
    : Report(id, "Weekly Timesheet Report"), weekNumber(week), totalHours(0) {
}

void WeeklyTimesheetReport::generate() {
    std::cout << "Generating Weekly Timesheet Report for week " << weekNumber << "..." << std::endl;
    totalHours = 0;
    for (const auto& ts : timesheets) {
        totalHours += ts.calculateContactHours();
    }
}

void WeeklyTimesheetReport::display() const {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "WEEKLY TIMESHEET REPORT - WEEK " << weekNumber << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "Report ID: " << reportId << std::endl;
    std::cout << "Generated: " << generatedDate.toFullString() << std::endl;
    std::cout << "Total Hours: " << std::fixed << std::setprecision(2) << totalHours << std::endl;
    std::cout << "Timesheets Count: " << timesheets.size() << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    if (timesheets.empty()) {
        std::cout << "No timesheet entries for this week." << std::endl;
    }
    else {
        std::cout << std::left
            << std::setw(12) << "Section ID"
            << std::setw(12) << "Date"
            << std::setw(12) << "Start Time"
            << std::setw(12) << "End Time"
            << std::setw(10) << "Hours"
            << std::setw(10) << "Makeup"
            << std::setw(15) << "Attendant"
            << std::endl;
        std::cout << std::string(70, '-') << std::endl;

        for (const auto& ts : timesheets) {
            double hours = ts.calculateContactHours();
            std::cout << std::left
                << std::setw(12) << ts.getSectionId()
                << std::setw(12) << ts.getDate().toString()
                << std::setw(12) << ts.getActualStart().toTimeString()
                << std::setw(12) << ts.getActualEnd().toTimeString()
                << std::setw(10) << std::fixed << std::setprecision(2) << hours
                << std::setw(10) << (ts.getIsMakeup() ? "Yes" : "No")
                << std::setw(15) << ts.getAttendantId()
                << std::endl;
        }
    }
    std::cout << std::string(70, '=') << std::endl;
}

void WeeklyTimesheetReport::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (out) {
        out << "WEEKLY TIMESHEET REPORT - WEEK " << weekNumber << "\n";
        out << "================================\n";
        out << "Report ID: " << reportId << "\n";
        out << "Generated: " << generatedDate.toFullString() << "\n";
        out << "Total Hours: " << std::fixed << std::setprecision(2) << totalHours << "\n";
        out << "Timesheets Count: " << timesheets.size() << "\n\n";

        if (timesheets.empty()) {
            out << "No timesheet entries for this week.\n";
        }
        else {
            out << "TIMESHEET DETAILS:\n";
            out << "------------------------------------------------------------\n";
            out << "Section ID   Date        Start Time  End Time    Hours  Makeup  Attendant\n";
            out << "------------------------------------------------------------\n";

            for (const auto& ts : timesheets) {
                double hours = ts.calculateContactHours();
                out << std::left
                    << std::setw(12) << ts.getSectionId()
                    << std::setw(12) << ts.getDate().toString()
                    << std::setw(11) << ts.getActualStart().toTimeString()
                    << std::setw(11) << ts.getActualEnd().toTimeString()
                    << std::setw(7) << std::fixed << std::setprecision(2) << hours
                    << std::setw(8) << (ts.getIsMakeup() ? "Yes" : "No")
                    << std::setw(15) << ts.getAttendantId()
                    << "\n";
            }
        }
        out << "\n=== END OF REPORT ===";
    }
}

// SemesterReport Implementation
SemesterReport::SemesterReport(const std::string& id, const std::string& labId)
    : Report(id, "Semester Report"), labId(labId), totalContactHours(0), totalLeaves(0) {
}

void SemesterReport::generate() {
    std::cout << "Generating Semester Report for lab " << labId << "..." << std::endl;
    totalContactHours = 0;
    totalLeaves = 0;

    for (const auto& ts : timesheets) {
        double hours = ts.calculateContactHours();
        totalContactHours += hours;
        if (hours == 0) {
            totalLeaves++;
        }
    }
}

void SemesterReport::display() const {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "SEMESTER REPORT - LAB " << labId << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Report ID: " << reportId << std::endl;
    std::cout << "Generated: " << generatedDate.toFullString() << std::endl;
    std::cout << "Total Contact Hours: " << std::fixed << std::setprecision(2) << totalContactHours << std::endl;
    std::cout << "Total Leaves: " << totalLeaves << std::endl;
    std::cout << "Sessions Count: " << timesheets.size() << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    if (timesheets.empty()) {
        std::cout << "No sessions recorded for this lab." << std::endl;
    }
    else {
        std::cout << std::left
            << std::setw(12) << "Date"
            << std::setw(12) << "Start Time"
            << std::setw(12) << "End Time"
            << std::setw(10) << "Hours"
            << std::setw(10) << "Makeup"
            << std::endl;
        std::cout << std::string(60, '-') << std::endl;

        for (const auto& ts : timesheets) {
            double hours = ts.calculateContactHours();
            std::cout << std::left
                << std::setw(12) << ts.getDate().toString()
                << std::setw(12) << ts.getActualStart().toTimeString()
                << std::setw(12) << ts.getActualEnd().toTimeString()
                << std::setw(10) << std::fixed << std::setprecision(2) << hours
                << std::setw(10) << (ts.getIsMakeup() ? "Yes" : "No")
                << std::endl;
        }
    }
    std::cout << std::string(60, '=') << std::endl;
}

void SemesterReport::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (out) {
        out << "SEMESTER REPORT - LAB " << labId << "\n";
        out << "========================\n";
        out << "Report ID: " << reportId << "\n";
        out << "Generated: " << generatedDate.toFullString() << "\n";
        out << "Total Contact Hours: " << std::fixed << std::setprecision(2) << totalContactHours << "\n";
        out << "Total Leaves: " << totalLeaves << "\n";
        out << "Sessions Count: " << timesheets.size() << "\n\n";

        if (timesheets.empty()) {
            out << "No sessions recorded for this lab.\n";
        }
        else {
            out << "SESSION DETAILS:\n";
            out << "--------------------------------------------\n";
            out << "Date        Start Time  End Time    Hours  Makeup\n";
            out << "--------------------------------------------\n";

            for (const auto& ts : timesheets) {
                double hours = ts.calculateContactHours();
                out << std::left
                    << std::setw(12) << ts.getDate().toString()
                    << std::setw(11) << ts.getActualStart().toTimeString()
                    << std::setw(11) << ts.getActualEnd().toTimeString()
                    << std::setw(7) << std::fixed << std::setprecision(2) << hours
                    << std::setw(8) << (ts.getIsMakeup() ? "Yes" : "No")
                    << "\n";
            }
        }
        out << "\n=== END OF REPORT ===";
    }
}

// LabSemesterTimesheetReport Implementation
LabSemesterTimesheetReport::LabSemesterTimesheetReport(const std::string& id, const std::string& labId)
    : Report(id, "Lab Semester Timesheet Report"), labId(labId), totalContactHours(0),
    totalSessions(0), makeupSessions(0), leaveSessions(0) {
}

void LabSemesterTimesheetReport::generate() {
    std::cout << "Generating Semester Timesheet Report for lab " << labId << "..." << std::endl;
    totalContactHours = 0;
    totalSessions = timesheets.size();
    makeupSessions = 0;
    leaveSessions = 0;

    for (const auto& ts : timesheets) {
        double hours = ts.calculateContactHours();
        totalContactHours += hours;
        if (ts.getIsMakeup()) {
            makeupSessions++;
        }
        if (hours == 0) {
            leaveSessions++;
        }
    }
}

void LabSemesterTimesheetReport::display() const {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "LAB SEMESTER TIMESHEET REPORT - " << labId << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Report ID: " << reportId << std::endl;
    std::cout << "Generated: " << generatedDate.toFullString() << std::endl;
    std::cout << "Lab ID: " << labId << std::endl;
    std::cout << "Total Sections: " << labSections.size() << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    // Summary Statistics
    std::cout << "SUMMARY STATISTICS:" << std::endl;
    std::cout << "Total Sessions: " << totalSessions << std::endl;
    std::cout << "Total Contact Hours: " << std::fixed << std::setprecision(2) << totalContactHours << std::endl;
    std::cout << "Makeup Sessions: " << makeupSessions << std::endl;
    std::cout << "Leave Sessions: " << leaveSessions << std::endl;
    std::cout << "Attendance Rate: " << std::fixed << std::setprecision(1)
        << ((totalSessions - leaveSessions) * 100.0 / totalSessions) << "%" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    if (timesheets.empty()) {
        std::cout << "No timesheet entries for this lab." << std::endl;
    }
    else {
        // Detailed timesheet for each section
        for (const auto& section : labSections) {
            std::cout << "\nSECTION: " << section.getSectionName() << " (" << section.getSectionId() << ")" << std::endl;
            std::cout << "Scheduled: ";
            switch (section.getSchedule().getDay()) {
            case DayOfWeek::MONDAY: std::cout << "Monday"; break;
            case DayOfWeek::TUESDAY: std::cout << "Tuesday"; break;
            case DayOfWeek::WEDNESDAY: std::cout << "Wednesday"; break;
            case DayOfWeek::THURSDAY: std::cout << "Thursday"; break;
            case DayOfWeek::FRIDAY: std::cout << "Friday"; break;
            case DayOfWeek::SATURDAY: std::cout << "Saturday"; break;
            case DayOfWeek::SUNDAY: std::cout << "Sunday"; break;
            }
            std::cout << " " << section.getSchedule().getStartTime().toTimeString() << " - "
                << section.getSchedule().getEndTime().toTimeString() << std::endl;

            std::cout << std::string(60, '-') << std::endl;
            std::cout << std::left
                << std::setw(12) << "Date"
                << std::setw(12) << "Actual Start"
                << std::setw(12) << "Actual End"
                << std::setw(10) << "Hours"
                << std::setw(10) << "Scheduled"
                << std::setw(10) << "Diff"
                << std::setw(10) << "Makeup"
                << std::setw(15) << "Attendant"
                << std::endl;
            std::cout << std::string(60, '-') << std::endl;

            double sectionTotalHours = 0;
            int sectionSessions = 0;

            for (const auto& ts : timesheets) {
                if (ts.getSectionId() == section.getSectionId()) {
                    double actualHours = ts.calculateContactHours();
                    double scheduledHours = section.getSchedule().getExpectedHours();
                    double difference = actualHours - scheduledHours;

                    std::cout << std::left
                        << std::setw(12) << ts.getDate().toString()
                        << std::setw(12) << ts.getActualStart().toTimeString()
                        << std::setw(12) << ts.getActualEnd().toTimeString()
                        << std::setw(10) << std::fixed << std::setprecision(2) << actualHours
                        << std::setw(10) << std::fixed << std::setprecision(2) << scheduledHours
                        << std::setw(10) << std::fixed << std::setprecision(2) << difference
                        << std::setw(10) << (ts.getIsMakeup() ? "Yes" : "No")
                        << std::setw(15) << ts.getAttendantId()
                        << std::endl;

                    sectionTotalHours += actualHours;
                    sectionSessions++;
                }
            }

            if (sectionSessions > 0) {
                std::cout << std::string(60, '-') << std::endl;
                std::cout << "Section Total: " << sectionSessions << " sessions, "
                    << std::fixed << std::setprecision(2) << sectionTotalHours << " hours" << std::endl;
            }
            else {
                std::cout << "No timesheet entries for this section." << std::endl;
            }
        }
    }
    std::cout << std::string(80, '=') << std::endl;
}

void LabSemesterTimesheetReport::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (out) {
        out << "LAB SEMESTER TIMESHEET REPORT - " << labId << "\n";
        out << "===================================\n";
        out << "Report ID: " << reportId << "\n";
        out << "Generated: " << generatedDate.toFullString() << "\n";
        out << "Lab ID: " << labId << "\n";
        out << "Total Sections: " << labSections.size() << "\n\n";

        out << "SUMMARY STATISTICS:\n";
        out << "Total Sessions: " << totalSessions << "\n";
        out << "Total Contact Hours: " << std::fixed << std::setprecision(2) << totalContactHours << "\n";
        out << "Makeup Sessions: " << makeupSessions << "\n";
        out << "Leave Sessions: " << leaveSessions << "\n";
        out << "Attendance Rate: " << std::fixed << std::setprecision(1)
            << ((totalSessions - leaveSessions) * 100.0 / totalSessions) << "%\n\n";

        if (!timesheets.empty()) {
            for (const auto& section : labSections) {
                out << "SECTION: " << section.getSectionName() << " (" << section.getSectionId() << ")\n";
                out << "Scheduled: ";
                switch (section.getSchedule().getDay()) {
                case DayOfWeek::MONDAY: out << "Monday"; break;
                case DayOfWeek::TUESDAY: out << "Tuesday"; break;
                case DayOfWeek::WEDNESDAY: out << "Wednesday"; break;
                case DayOfWeek::THURSDAY: out << "Thursday"; break;
                case DayOfWeek::FRIDAY: out << "Friday"; break;
                case DayOfWeek::SATURDAY: out << "Saturday"; break;
                case DayOfWeek::SUNDAY: out << "Sunday"; break;
                }
                out << " " << section.getSchedule().getStartTime().toTimeString() << " - "
                    << section.getSchedule().getEndTime().toTimeString() << "\n";

                out << "----------------------------------------------------------------------\n";
                out << "Date        Actual Start Actual End Hours     Scheduled Diff     Makeup  Attendant\n";
                out << "----------------------------------------------------------------------\n";

                double sectionTotalHours = 0;
                int sectionSessions = 0;

                for (const auto& ts : timesheets) {
                    if (ts.getSectionId() == section.getSectionId()) {
                        double actualHours = ts.calculateContactHours();
                        double scheduledHours = section.getSchedule().getExpectedHours();
                        double difference = actualHours - scheduledHours;

                        out << std::left
                            << std::setw(12) << ts.getDate().toString()
                            << std::setw(12) << ts.getActualStart().toTimeString()
                            << std::setw(12) << ts.getActualEnd().toTimeString()
                            << std::setw(9) << std::fixed << std::setprecision(2) << actualHours
                            << std::setw(10) << std::fixed << std::setprecision(2) << scheduledHours
                            << std::setw(8) << std::fixed << std::setprecision(2) << difference
                            << std::setw(8) << (ts.getIsMakeup() ? "Yes" : "No")
                            << std::setw(15) << ts.getAttendantId()
                            << "\n";

                        sectionTotalHours += actualHours;
                        sectionSessions++;
                    }
                }

                if (sectionSessions > 0) {
                    out << "Section Total: " << sectionSessions << " sessions, "
                        << std::fixed << std::setprecision(2) << sectionTotalHours << " hours\n\n";
                }
                else {
                    out << "No timesheet entries for this section.\n\n";
                }
            }
        }
        out << "=== END OF REPORT ===";
    }
}