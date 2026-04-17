#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include <iomanip>
#include "labmanagementsystem.h"
#include "login.h"
using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int getIntInput(const string& prompt) {
    int input;
    cout << prompt;
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter a number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return input;
}

bool getBoolInput(const string& prompt) {
    char input;
    cout << prompt << " (y/n): ";
    cin >> input;
    clearInputBuffer();
    return (input == 'y' || input == 'Y');
}
DateTime getValidatedDateTimeInput(const string& prompt, bool includeTime = true) {
    DateTime dt;
    bool valid = false;

    while (!valid) {
        cout << prompt << endl;
        int year = getIntInput("Enter year (2000-2100): ");
        int month = getIntInput("Enter month (1-12): ");
        int day = getIntInput("Enter day: ");

        int hour = 0, minute = 0;
        if (includeTime) {
            hour = getIntInput("Enter hour (0-23): ");
            minute = getIntInput("Enter minute (0-59): ");
        }

        dt = DateTime(year, month, day, hour, minute);

        if (dt.isWithinReasonableSchedule()) {
            valid = true;
        }
        else {
            cout << "ERROR: " << dt.getValidationMessage() << endl;
            cout << "Please try again.\n" << endl;
        }
    }

    return dt;
}

// For getting only end time on the same day as start time
DateTime getValidatedEndTimeInput(const DateTime& startTime, const string& prompt) {
    DateTime endTime;
    bool valid = false;

    while (!valid) {
        cout << prompt << endl;
        int hour = getIntInput("Enter end hour (0-23): ");
        int minute = getIntInput("Enter end minute (0-59): ");

        // Use the same date as start time, only change the time
        endTime = DateTime(startTime.getYear(), startTime.getMonth(), startTime.getDay(), hour, minute);

        // Validate the time
        if (!endTime.isValidTime()) {
            cout << "ERROR: Invalid end time. Hour must be 0-23, minute must be 0-59." << endl;
        }
        else if (startTime.calculateHoursDifference(endTime) <= 0) {
            cout << "ERROR: End time must be after start time." << endl;
        }
        else if (startTime.calculateHoursDifference(endTime) > 8) {
            cout << "ERROR: Lab duration cannot exceed 8 hours." << endl;
        }
        else {
            valid = true;
        }

        if (!valid) {
            cout << "Please try again.\n" << endl;
        }
    }

    return endTime;
}

DateTime getValidatedFutureDateInput(const string& prompt) {
    DateTime dt;
    bool valid = false;

    while (!valid) {
        cout << prompt << endl;
        int year = getIntInput("Enter year (2000-2100): ");
        int month = getIntInput("Enter month (1-12): ");
        int day = getIntInput("Enter day: ");

        dt = DateTime(year, month, day, 0, 0);

        if (!dt.isValidDate()) {
            cout << "ERROR: Invalid date. Please check the values." << endl;
        }
        else if (dt.isPast()) {
            cout << "ERROR: Cannot use past date. Please choose a future date." << endl;
        }
        else if (dt.isTooFarFuture()) {
            cout << "ERROR: Date is too far in the future (max 2 years)." << endl;
        }
        else if (dt.isWeekend()) {
            cout << "ERROR: Cannot schedule on weekends." << endl;
        }
        else {
            valid = true;
        }

        if (!valid) {
            cout << "Please try again.\n" << endl;
        }
    }

    return dt;
}
void addLabInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New Lab ---" << endl;
    string id = getStringInput("Enter Lab ID: ");
    string name = getStringInput("Enter Lab Name: ");
    string courseCode = getStringInput("Enter Course Code: ");
    int creditHours = getIntInput("Enter Credit Hours: ");

    Lab lab(id, name, courseCode, creditHours);
    system.addLab(lab);
    cout << "Lab added successfully!" << endl;
}

void addInstructorInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New Instructor ---" << endl;
    string id = getStringInput("Enter Instructor ID: ");
    string name = getStringInput("Enter Instructor Name: ");
    string email = getStringInput("Enter Email: ");
    string department = getStringInput("Enter Department: ");

    Instructor instructor(id, name, email, department);
    system.addInstructor(instructor);
    cout << "Instructor added successfully!" << endl;
}

void addTAInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New TA ---" << endl;
    string id = getStringInput("Enter TA ID: ");
    string name = getStringInput("Enter TA Name: ");
    string email = getStringInput("Enter Email: ");
    bool isGraduate = getBoolInput("Is Graduate TA?");

    TA ta(id, name, email, isGraduate);
    system.addTA(ta);
    cout << "TA added successfully!" << endl;
}

void addVenueInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New Venue ---" << endl;
    string id = getStringInput("Enter Venue ID: ");
    string roomNumber = getStringInput("Enter Room Number: ");
    int capacity = getIntInput("Enter Capacity: ");
    string buildingId = getStringInput("Enter Building ID: ");

    Venue venue(id, roomNumber, capacity, buildingId);
    system.addVenue(venue);
    cout << "Venue added successfully!" << endl;
}

DayOfWeek getDayOfWeekInput() {
    cout << "\nSelect Day of Week:" << endl;
    cout << "1. Monday" << endl;
    cout << "2. Tuesday" << endl;
    cout << "3. Wednesday" << endl;
    cout << "4. Thursday" << endl;
    cout << "5. Friday" << endl;
    cout << "6. Saturday" << endl;
    cout << "7. Sunday" << endl;

    int choice = getIntInput("Enter choice (1-7): ");
    while (choice < 1 || choice > 7) {
        cout << "Invalid choice. Please enter 1-7: ";
        choice = getIntInput("Enter choice (1-7): ");
    }

    return static_cast<DayOfWeek>(choice - 1);
}

DateTime getDateTimeInput(const string& prompt, bool includeTime = true) {
    cout << prompt << endl;
    int year = getIntInput("Enter year: ");
    int month = getIntInput("Enter month: ");
    int day = getIntInput("Enter day: ");

    int hour = 0, minute = 0;
    if (includeTime) {
        hour = getIntInput("Enter hour (0-23): ");
        minute = getIntInput("Enter minute (0-59): ");
    }

    return DateTime(year, month, day, hour, minute);
}

void addSectionInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New Section ---" << endl;
    string sectionId = getStringInput("Enter Section ID: ");
    string sectionName = getStringInput("Enter Section Name: ");
    string labId = getStringInput("Enter Lab ID: ");
    string instructorId = getStringInput("Enter Instructor ID: ");
    string venueId = getStringInput("Enter Venue ID: ");

    // Get TA IDs
    vector<string> taIds;
    cout << "Enter TA IDs (enter 'done' when finished):" << endl;
    while (true) {
        string taId = getStringInput("TA ID: ");
        if (taId == "done" || taId == "DONE") break;
        taIds.push_back(taId);
    }

    // Get schedule
    cout << "\n--- Schedule Information ---" << endl;
    DayOfWeek day = getDayOfWeekInput();
    DateTime startTime = getValidatedDateTimeInput("Enter Start Time:", true);
    // Get only end time (same day as start time)
    DateTime endTime = getValidatedEndTimeInput(startTime, "Enter End Time:");
    string semester = getStringInput("Enter Semester: ");

    Schedule schedule(day, startTime, endTime, semester);
    Section section(sectionId, sectionName, labId, instructorId, taIds, venueId, schedule);
    system.addSection(section);
    cout << "Section added successfully!" << endl;
}

void fillTimesheetInteractive(LabManagementSystem& system) {
    cout << "\n--- Fill Timesheet ---" << endl;
    string sectionId = getStringInput("Enter Section ID: ");

    // First, find the section to show scheduled info
    Section* section = system.findSection(sectionId);
    if (!section) {
        cout << "ERROR: Section not found!" << endl;
        return;
    }

    // Display scheduled information for reference
    Schedule scheduled = section->getSchedule();
    cout << "\n--- SCHEDULED INFORMATION ---" << endl;
    cout << "Section: " << section->getSectionName() << endl;
    cout << "Scheduled Day: ";
    switch (scheduled.getDay()) {
    case DayOfWeek::MONDAY: cout << "Monday"; break;
    case DayOfWeek::TUESDAY: cout << "Tuesday"; break;
    case DayOfWeek::WEDNESDAY: cout << "Wednesday"; break;
    case DayOfWeek::THURSDAY: cout << "Thursday"; break;
    case DayOfWeek::FRIDAY: cout << "Friday"; break;
    case DayOfWeek::SATURDAY: cout << "Saturday"; break;
    case DayOfWeek::SUNDAY: cout << "Sunday"; break;
    }
    cout << endl;
    cout << "Scheduled Time: " << scheduled.getStartTime().toTimeString() << " - "
        << scheduled.getEndTime().toTimeString() << endl;
    cout << "Expected Duration: " << scheduled.getExpectedHours() << " hours" << endl;

    DateTime date = getValidatedFutureDateInput("\nEnter Actual Date of Lab:");

    cout << "\n--- ACTUAL TIMINGS ---" << endl;
    cout << "Enter ACTUAL start time (when lab actually started):" << endl;
    int startHour = getIntInput("Enter actual start hour (0-23): ");
    int startMinute = getIntInput("Enter actual start minute (0-59): ");
    DateTime actualStart(date.getYear(), date.getMonth(), date.getDay(), startHour, startMinute);

    cout << "\nEnter ACTUAL end time (when lab actually ended):" << endl;
    DateTime actualEnd = getValidatedEndTimeInput(actualStart, "Enter actual end time:");

    // Calculate and show comparison
    double scheduledHours = scheduled.getExpectedHours();
    double actualHours = actualStart.calculateHoursDifference(actualEnd);

    cout << "\n--- COMPARISON ---" << endl;
    cout << "Scheduled: " << scheduledHours << " hours" << endl;
    cout << "Actual: " << actualHours << " hours" << endl;
    cout << "Difference: " << (actualHours - scheduledHours) << " hours" << endl;

    bool isMakeup = getBoolInput("Is this a makeup lab?");
    string attendantId = getStringInput("Enter Attendant ID: ");

    Timesheet timesheet(date, actualStart, actualEnd, isMakeup, attendantId, sectionId);
    system.fillTimesheet(timesheet);
    cout << "Timesheet filled successfully!" << endl;
}

void requestMakeupLabInteractive(LabManagementSystem& system) {
    cout << "\n--- Request Makeup Lab ---" << endl;
    string sectionId = getStringInput("Enter Section ID: ");
    string instructorId = getStringInput("Enter Your Instructor ID: ");
    string reason = getStringInput("Enter Reason for Makeup: ");
    DateTime preferredDate = getValidatedDateTimeInput("Enter Preferred Date:", true);

    system.submitMakeupRequest(sectionId, instructorId, reason, preferredDate);
    cout << "Makeup lab request submitted successfully!" << endl;
}

void viewPendingMakeupRequests(LabManagementSystem& system) {
    cout << "\n--- Pending Makeup Requests ---" << endl;
    vector<MakeupRequest> pending = system.getPendingMakeupRequests();

    if (pending.empty()) {
        cout << "No pending makeup requests." << endl;
        return;
    }

    cout << "\n" << string(80, '=') << endl;
    cout << "PENDING MAKEUP REQUESTS" << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(12) << "Request ID"
        << setw(12) << "Section ID"
        << setw(15) << "Instructor ID"
        << setw(20) << "Preferred Date"
        << setw(30) << "Reason"
        << endl;
    cout << string(80, '-') << endl;

    for (const auto& request : pending) {
        cout << left << setw(12) << request.getRequestId()
            << setw(12) << request.getSectionId()
            << setw(15) << request.getInstructorId()
            << setw(20) << request.getPreferredDate().toFullString()
            << setw(30) << (request.getReason().length() > 28 ?
                request.getReason().substr(0, 27) + "." : request.getReason())
            << endl;
    }
    cout << string(80, '=') << endl;
}
// Source.cpp - Add these functions
void createAccountInteractive(LoginSystem& loginSystem) {
    cout << "\n--- Create New Account ---" << endl;

    string username = getStringInput("Enter username: ");
    string password = getStringInput("Enter password: ");

    // For now, only allow HOD account creation
    // You can extend this to allow other roles later
    UserRole role = UserRole::HOD;

    if (loginSystem.createAccount(username, password, role)) {
        cout << "HOD account created successfully!" << endl;
        cout << "You can now login with these credentials." << endl;
    }
    else {
        cout << "Failed to create account!" << endl;
    }
}
void displayCreateAccountScreen(LoginSystem& loginSystem) {
    cout << "\n" << string(40, '=') << endl;
    cout << "CREATE NEW ACCOUNT" << endl;
    cout << string(40, '=') << endl;

    createAccountInteractive(loginSystem);
}
// Update the displayLoginScreen function
void displayLoginScreen(LoginSystem& loginSystem) {
    int choice;

    do {
        cout << "\n" << string(40, '=') << endl;
        cout << "LAB MANAGEMENT SYSTEM" << endl;
        cout << string(40, '=') << endl;
        cout << "1. Login" << endl;
        cout << "2. Create New Account (HOD Only)" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose option: ";

        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            // Existing login logic
            int attempts = 0;
            const int MAX_ATTEMPTS = 3;

            while (attempts < MAX_ATTEMPTS) {
                string username = getStringInput("Username: ");
                string password = getStringInput("Password: ");

                if (loginSystem.login(username, password)) {
                    return; // Login successful
                }
                else {
                    attempts++;
                    cout << "Invalid credentials. Attempts remaining: " << (MAX_ATTEMPTS - attempts) << endl;
                }
            }

            cout << "Too many failed attempts. Returning to main menu." << endl;
            break;
        }
        case 2:
            displayCreateAccountScreen(loginSystem);
            return;
            break;
        case 3:
            cout << "Goodbye!" << endl;
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (true);
}



void approveMakeupRequestInteractive(LabManagementSystem& system) {
    cout << "\n--- Approve Makeup Request ---" << endl;
    viewPendingMakeupRequests(system);

    string requestId = getStringInput("Enter Request ID to approve: ");
    string officerId = getStringInput("Enter Your Officer ID: ");

    cout << "Enter scheduled details:" << endl;
    DateTime scheduledDate = getValidatedDateTimeInput("Enter Scheduled Date and Time:", true);

    if (system.approveMakeupRequest(requestId, scheduledDate, officerId)) {
        cout << "Makeup request approved and scheduled successfully!" << endl;
    }
    else {
        cout << "ERROR: Could not approve request. Request not found or already processed." << endl;
    }
}

void rejectMakeupRequestInteractive(LabManagementSystem& system) {
    cout << "\n--- Reject Makeup Request ---" << endl;
    viewPendingMakeupRequests(system);

    string requestId = getStringInput("Enter Request ID to reject: ");
    string officerId = getStringInput("Enter Your Officer ID: ");

    if (system.rejectMakeupRequest(requestId, officerId)) {
        cout << "Makeup request rejected successfully!" << endl;
    }
    else {
        cout << "ERROR: Could not reject request. Request not found or already processed." << endl;
    }
}

void generateWeeklyScheduleReportInteractive(LabManagementSystem& system) {
    cout << "\n--- Generate Weekly Schedule Report ---" << endl;
    DateTime weekStart = getValidatedFutureDateInput("Enter Week Start Date:");

    Report* report = system.generateWeeklyScheduleReport(weekStart); // Use Report*
    report->display();

    string filename = getStringInput("Enter filename to save report: ");
    report->saveToFile(filename);
    cout << "Report saved to " << filename << endl;
    delete report; // Don't forget to delete!
}

void generateWeeklyTimesheetReportInteractive(LabManagementSystem& system) {
    cout << "\n--- Generate Weekly Timesheet Report ---" << endl;
    int weekNumber = getIntInput("Enter Week Number: ");

    Report* report = system.generateWeeklyTimesheetReport(weekNumber); // Use Report*
    report->display();

    string filename = getStringInput("Enter filename to save report: ");
    report->saveToFile(filename);
    cout << "Report saved to " << filename << endl;
    delete report; // Don't forget to delete!
}

void generateSemesterReportInteractive(LabManagementSystem& system) {
    cout << "\n--- Generate Semester Report ---" << endl;
    string labId = getStringInput("Enter Lab ID: ");

    Report* report = system.generateSemesterReport(labId); // Use Report*
    report->display();

    string filename = getStringInput("Enter filename to save report: ");
    report->saveToFile(filename);
    cout << "Report saved to " << filename << endl;
    delete report; // Don't forget to delete!
}



void attendantMenu(LabManagementSystem& system) {
    int choice;
    do {
        cout << "\n--- Attendant Menu ---" << endl;
        cout << "1. Fill Timesheet" << endl;
        cout << "2. Back to Main Menu" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: fillTimesheetInteractive(system); break;
        case 2: cout << "Returning to main menu..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 2);
}

void instructorMenu(LabManagementSystem& system) {
    int choice;
    do {
        cout << "\n--- Instructor Menu ---" << endl;
        cout << "1. Request Makeup Lab" << endl;
        cout << "2. Back to Main Menu" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: requestMakeupLabInteractive(system); break;
        case 2: cout << "Returning to main menu..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 2);
}
void generateLabSemesterTimesheetReportInteractive(LabManagementSystem& system) {
    cout << "\n--- Generate Lab Semester Timesheet Report ---" << endl;
    string labId = getStringInput("Enter Lab ID: ");

    Report* report =system. generateLabSemesterTimesheetReport(labId);
    report->display();

    string filename = getStringInput("Enter filename to save report: ");
    report->saveToFile(filename);
    cout << "Report saved to " << filename << endl;
    delete report;
}
void hodMenu(LabManagementSystem& system) {
    int choice;
    do {
        cout << "\n--- HOD Menu ---" << endl;
        cout << "1. Generate Weekly Schedule Report" << endl;
        cout << "2. Generate Weekly Timesheet Report" << endl;
        cout << "3. Generate Semester Report" << endl;
        cout << "4. Generate Lab Semester Timesheet Report" << endl;  // ADD THIS
        cout << "5. Back to Main Menu" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: generateWeeklyScheduleReportInteractive(system); break;
        case 2: generateWeeklyTimesheetReportInteractive(system); break;
        case 3: generateSemesterReportInteractive(system); break;
        case 4: generateLabSemesterTimesheetReportInteractive(system); break;  // ADD THIS
        case 5: cout << "Returning to main menu..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
}

void addBuildingInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New Building ---" << endl;
    string id = getStringInput("Enter Building ID: ");
    string name = getStringInput("Enter Building Name: ");
    string location = getStringInput("Enter Location: ");

    Building building(id, name, location);
    system.addBuilding(building);
    cout << "Building added successfully!" << endl;
}

void addAttendantInteractive(LabManagementSystem& system) {
    cout << "\n--- Add New Attendant ---" << endl;
    string id = getStringInput("Enter Attendant ID: ");
    string name = getStringInput("Enter Attendant Name: ");
    string contact = getStringInput("Enter Contact: ");

    Attendant attendant(id, name, contact);
    system.addAttendant(attendant);
    cout << "Attendant added successfully!" << endl;
}

void addAcademicOfficerInteractive(LabManagementSystem& system) {
    cout << "\n--- Add Academic Officer ---" << endl;
    string id = getStringInput("Enter Officer ID: ");
    string name = getStringInput("Enter Name: ");
    string email = getStringInput("Enter Email: ");

    AcademicOfficer officer(id, name, email);
    system.addAcademicOfficer(officer);
    cout << "Academic Officer added successfully!" << endl;
}

void addHODInteractive(LabManagementSystem& system) {
    cout << "\n--- Add HOD ---" << endl;
    string id = getStringInput("Enter HOD ID: ");
    string name = getStringInput("Enter Name: ");
    string email = getStringInput("Enter Email: ");

    HOD hod(id, name, email);
    system.addHOD(hod);
    cout << "HOD added successfully!" << endl;
}

void assignInstructorInteractive(LabManagementSystem& system) {
    cout << "\n--- Assign Instructor to Section ---" << endl;
    string sectionId = getStringInput("Enter Section ID: ");
    string instructorId = getStringInput("Enter Instructor ID: ");

    system.assignInstructorToSection(sectionId, instructorId);
    cout << "Instructor assigned to section successfully!" << endl;
}

void assignTAInteractive(LabManagementSystem& system) {
    cout << "\n--- Assign TA to Section ---" << endl;
    string sectionId = getStringInput("Enter Section ID: ");
    string taId = getStringInput("Enter TA ID: ");

    system.assignTAToSection(sectionId, taId);
    cout << "TA assigned to section successfully!" << endl;
}

void assignAttendantInteractive(LabManagementSystem& system) {
    cout << "\n--- Assign Attendant to Building ---" << endl;
    string buildingId = getStringInput("Enter Building ID: ");
    string attendantId = getStringInput("Enter Attendant ID: ");

    system.assignAttendantToBuilding(buildingId, attendantId);
    cout << "Attendant assigned to building successfully!" << endl;
}

void scheduleMakeupLabInteractive(LabManagementSystem& system) {
    cout << "\n--- Schedule Makeup Lab ---" << endl;
    string sectionId = getStringInput("Enter Section ID: ");

    DayOfWeek day = getDayOfWeekInput();
    // Get start date and time
    DateTime startTime = getValidatedDateTimeInput("Enter Start Date and Time:", true);

    // Get only end time (same day)
    DateTime endTime = getValidatedEndTimeInput(startTime, "Enter End Time:");
    string semester = getStringInput("Enter Semester: ");

    Schedule schedule(day, startTime, endTime, semester);
    system.scheduleMakeupLab(sectionId, schedule);
    cout << "Makeup lab scheduled successfully!" << endl;
}

void academicOfficerMenu(LabManagementSystem& system) {
    int choice;
    do {
        cout << "\n--- Academic Officer Menu ---" << endl;
        cout << "1. Add Lab" << endl;
        cout << "2. Add Instructor" << endl;
        cout << "3. Add TA" << endl;
        cout << "4. Add Venue" << endl;
        cout << "5. Add Section" << endl;
        cout << "6. Add Building" << endl;
        cout << "7. Add Attendant" << endl;
        cout << "8. Assign Instructor to Section" << endl;
        cout << "9. Assign TA to Section" << endl;
        cout << "10. Assign Attendant to Building" << endl;
        cout << "11. View Pending Makeup Requests" << endl;      // NEW
        cout << "12. Approve Makeup Request" << endl;           // NEW
        cout << "13. Reject Makeup Request" << endl;            // NEW
        cout << "14. Back to Main Menu" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addLabInteractive(system); break;
        case 2: addInstructorInteractive(system); break;
        case 3: addTAInteractive(system); break;
        case 4: addVenueInteractive(system); break;
        case 5: addSectionInteractive(system); break;
        case 6: addBuildingInteractive(system); break;
        case 7: addAttendantInteractive(system); break;
        case 8: assignInstructorInteractive(system); break;
        case 9: assignTAInteractive(system); break;
        case 10: assignAttendantInteractive(system); break;
        case 11: viewPendingMakeupRequests(system); break;     // NEW
        case 12: approveMakeupRequestInteractive(system); break; // NEW
        case 13: rejectMakeupRequestInteractive(system); break;  // NEW
        case 14: cout << "Returning to main menu..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 14);
}

// Add system administration menu
void systemAdminMenu(LabManagementSystem& system) {
    int choice;
    do {
        cout << "\n--- System Administration ---" << endl;
        cout << "1. Add Academic Officer" << endl;
        cout << "2. Add HOD" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Choice: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: addAcademicOfficerInteractive(system); break;
        case 2: addHODInteractive(system); break;
        case 3: cout << "Returning to main menu..." << endl; break;
        default: cout << "Invalid choice!" << endl;
        }
    } while (choice != 3);
}

// Update main menu
void displayMenu() {
    cout << "\n=== Labs Management System ===" << endl;
    cout << "1. Academic Officer Functions" << endl;
    cout << "2. Attendant Functions" << endl;
    cout << "3. Instructor Functions" << endl;
    cout << "4. HOD Functions" << endl;
    cout << "5. System Administration" << endl;
    cout << "6. Save All Data" << endl;
    cout << "7. Exit" << endl;
    cout << "Choose option: ";
}

int main() {
    LabManagementSystem system;
    LoginSystem loginSystem;

    // Display login screen
    displayLoginScreen(loginSystem);

    system.loadAllData();

    int mainChoice;
    do {
        // Display role-based menu
        UserRole currentRole = loginSystem.getCurrentUserRole();
        string userName = loginSystem.getCurrentUserName();

        cout << "\n=== Labs Management System ===" << endl;
        cout << "Logged in as: " << userName << " (" << LoginSystem::roleToString(currentRole) << ")" << endl;
        cout << string(40, '-') << endl;

        // Role-based menu options
        switch (currentRole) {
        case UserRole::ACADEMIC_OFFICER:
            cout << "1. Academic Officer Functions" << endl;
            cout << "6. Save All Data" << endl;
            cout << "7. Logout" << endl;
            cout << "8. Exit" << endl;
            break;

        case UserRole::ATTENDANT:
            cout << "2. Attendant Functions" << endl;
            cout << "6. Save All Data" << endl;
            cout << "7. Logout" << endl;
            cout << "8. Exit" << endl;
            break;

        case UserRole::INSTRUCTOR:
            cout << "3. Instructor Functions" << endl;
            cout << "6. Save All Data" << endl;
            cout << "7. Logout" << endl;
            cout << "8. Exit" << endl;
            break;

        case UserRole::HOD:
            cout << "4. HOD Functions" << endl;
            cout << "6. Save All Data" << endl;
            cout << "7. Logout" << endl;
            cout << "8. Exit" << endl;
            break;

        case UserRole::SYSTEM_ADMIN:
            cout << "1. Academic Officer Functions" << endl;
            cout << "2. Attendant Functions" << endl;
            cout << "3. Instructor Functions" << endl;
            cout << "4. HOD Functions" << endl;
            cout << "5. System Administration" << endl;
            cout << "6. Save All Data" << endl;
            cout << "7. Logout" << endl;
            cout << "8. Exit" << endl;
            break;

        default:
            cout << "Invalid role detected!" << endl;
            break;
        }

        cout << "Choose option: ";
        cin >> mainChoice;
        clearInputBuffer();

        // Role-based menu handling
        switch (currentRole) {
        case UserRole::ACADEMIC_OFFICER:
            switch (mainChoice) {
            case 1: academicOfficerMenu(system); break;
            case 6: system.saveAllData(); cout << "Data saved!" << endl; break;
            case 7: loginSystem.logout(); displayLoginScreen(loginSystem); break;
            case 8: system.saveAllData(); cout << "Goodbye!" << endl; return 0;
            default: cout << "Invalid choice!" << endl;
            }
            break;

        case UserRole::ATTENDANT:
            switch (mainChoice) {
            case 2: attendantMenu(system); break;
            case 6: system.saveAllData(); cout << "Data saved!" << endl; break;
            case 7: loginSystem.logout(); displayLoginScreen(loginSystem); break;
            case 8: system.saveAllData(); cout << "Goodbye!" << endl; return 0;
            default: cout << "Invalid choice!" << endl;
            }
            break;

        case UserRole::INSTRUCTOR:
            switch (mainChoice) {
            case 3: instructorMenu(system); break;
            case 6: system.saveAllData(); cout << "Data saved!" << endl; break;
            case 7: loginSystem.logout(); displayLoginScreen(loginSystem); break;
            case 8: system.saveAllData(); cout << "Goodbye!" << endl; return 0;
            default: cout << "Invalid choice!" << endl;
            }
            break;

        case UserRole::HOD:
            switch (mainChoice) {
            case 4: hodMenu(system); break;
            case 6: system.saveAllData(); cout << "Data saved!" << endl; break;
            case 7: loginSystem.logout(); displayLoginScreen(loginSystem); break;
            case 8: system.saveAllData(); cout << "Goodbye!" << endl; return 0;
            default: cout << "Invalid choice!" << endl;
            }
            break;

        case UserRole::SYSTEM_ADMIN:
            switch (mainChoice) {
            case 1: academicOfficerMenu(system); break;
            case 2: attendantMenu(system); break;
            case 3: instructorMenu(system); break;
            case 4: hodMenu(system); break;
            case 5: systemAdminMenu(system); break;
            case 6: system.saveAllData(); cout << "Data saved!" << endl; break;
            case 7: loginSystem.logout(); displayLoginScreen(loginSystem); break;
            case 8: system.saveAllData(); cout << "Goodbye!" << endl; return 0;
            default: cout << "Invalid choice!" << endl;
            }
            break;
        }

    } while (true); // Infinite loop until exit

    return 0;
}