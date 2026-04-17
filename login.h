#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>
#include "person.h"
#include "academicofficer.h"
#include "attendant.h"
#include "instructor.h"
#include "hod.h"
#include "filemanager.h"

enum class UserRole {
    ACADEMIC_OFFICER,
    ATTENDANT,
    INSTRUCTOR,
    HOD,
    SYSTEM_ADMIN,
    INVALID
};

class LoginSystem {
private:
    std::vector<AcademicOfficer> academicOfficers;
    std::vector<Attendant> attendants;
    std::vector<Instructor> instructors;
    std::vector<HOD> hods;

    UserRole currentUserRole;
    Person* currentUser;

    void loadAllUsers();
    Person* authenticateUser(const std::string& username, const std::string& password);
    UserRole determineUserRole(const std::string& userId);

public:
    LoginSystem();
    ~LoginSystem();

    bool login(const std::string& username, const std::string& password);
    bool createAccount(const string& username, const string& password, UserRole role);
    void logout();
    UserRole getCurrentUserRole() const;
    Person* getCurrentUser() const;
    std::string getCurrentUserId() const;
    std::string getCurrentUserName() const;

    // Utility functions
    static std::string roleToString(UserRole role);
    static void displayWelcomeMessage(UserRole role, const std::string& userName);
};

#endif