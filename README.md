#Lab Management System

📖 Overview

The Lab Management System is a C++ application for managing academic labs, instructors, teaching assistants (TAs), venues, attendants, and scheduling. It provides role-based functionality for Academic Officers, Instructors, Attendants, Heads of Department (HODs), and System Administrators. The system also supports login management, report generation, and makeup lab requests.

✨ Features

Login System

User authentication with role-based access.

Account creation (currently supports HOD accounts).

Role-based menus and permissions.

Academic Officer Functions

Add labs, instructors, TAs, venues, sections, buildings, and attendants.

Assign instructors, TAs, and attendants to sections/buildings.

View, approve, or reject makeup lab requests.

Instructor Functions

Request makeup labs.

Attendant Functions

Fill timesheets for lab sessions.

HOD Functions

Generate weekly schedule reports.

Generate weekly timesheet reports.

Generate semester reports.

Generate lab semester timesheet reports.

System Administration

Add Academic Officers and HODs.

Reports

Weekly schedule report.

Weekly timesheet report.

Semester report.

Lab semester timesheet report.

🛡️ Input Validation

Date and time inputs are validated to ensure correctness.

Prevents scheduling on weekends.

Restricts lab duration to a maximum of 8 hours.

Ensures future dates are within a reasonable range (up to 2 years).

📂 File Structure

File Type

Purpose

.cpp / .h

Source code for system components (Lab, Instructor, TA, Venue, Section, Schedule, Timesheet, Reports, etc.)

.sln / .vcxproj

Visual Studio solution and project files

.dat

Dataset files (excluded from version control)

cccc_report/

Generated reports (excluded from version control)

🚀 Usage

Compile the project using Visual Studio or a C++ compiler.

Run the executable.

Login with credentials or create a new HOD account.

Navigate through role-based menus to perform actions:

Academic Officers: manage labs, staff, and requests.

Instructors: request makeup labs.

Attendants: fill timesheets.

HODs: generate reports.

System Admins: manage officers and HODs.

🔄 Example Workflow

Academic Officer adds a new lab, instructor, TA, and venue.

Instructor requests a makeup lab.

Academic Officer reviews and approves/rejects the request.

Attendant fills timesheets for lab sessions.

HOD generates weekly and semester reports.

⚠️ Notes

Ensure .dat dataset files and generated reports are excluded from version control using .gitignore.

Only source code and essential project files should be committed to GitHub.

🔮 Future Enhancements

Extend account creation to support multiple roles.

Improve error handling and user feedback.

Add persistent storage for user accounts and system data.

