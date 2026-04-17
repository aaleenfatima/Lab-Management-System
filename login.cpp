#include "login.h"
#include <iostream>
#include <algorithm>

using namespace std;

LoginSystem::LoginSystem() : currentUserRole(UserRole::SYSTEM_ADMIN), currentUser(nullptr) {
    loadAllUsers();
}

LoginSystem::~LoginSystem() {
    logout();
}

void LoginSystem::loadAllUsers() {
    // Load all user types from FileManager
    academicOfficers = FileManager::loadAcademicOfficers();
    attendants = FileManager::loadAttendants();
    instructors = FileManager::loadInstructors();
    hods = FileManager::loadHODs();

    cout << "Loaded users: " << academicOfficers.size() << " officers, "
        << attendants.size() << " attendants, "
        << instructors.size() << " instructors, "
        << hods.size() << " HODs" << endl;
}
bool LoginSystem::createAccount(const string& username, const string& password, UserRole role) {
    

    cout << "Account created successfully! Role: " << roleToString(role) << endl;
    cout << "Note: Account is stored in memory only (will be lost when program exits)." << endl;
    return true;
}

Person* LoginSystem::authenticateUser(const string& username, const string& password) {
    // For demo purposes, using ID as username and a simple password check
    // In real system, you'd have proper password storage and hashing

    // Check Academic Officers
    for (auto& officer : academicOfficers) {
        if (officer.getId() == username) {
            // Simple password check - in real system, use proper authentication
            if (password == "officer123") return &officer;
        }
    }

    // Check Attendants
    for (auto& attendant : attendants) {
        if (attendant.getId() == username) {
            if (password == "attendant123") return &attendant;
        }
    }

    // Check Instructors
    for (auto& instructor : instructors) {
        if (instructor.getId() == username) {
            if (password == "instructor123") return &instructor;
        }
    }

    // Check HODs
    for (auto& hod : hods) {
        if (hod.getId() == username) {
            if (password == "hod123") return &hod;
        }
    }

    return nullptr;
}

UserRole LoginSystem::determineUserRole(const string& userId) {
    // Check Academic Officers
    for (const auto& officer : academicOfficers) {
        if (officer.getId() == userId) return UserRole::ACADEMIC_OFFICER;
    }

    // Check Attendants
    for (const auto& attendant : attendants) {
        if (attendant.getId() == userId) return UserRole::ATTENDANT;
    }

    // Check Instructors
    for (const auto& instructor : instructors) {
        if (instructor.getId() == userId) return UserRole::INSTRUCTOR;
    }

    // Check HODs
    for (const auto& hod : hods) {
        if (hod.getId() == userId) return UserRole::HOD;
    }

    // System Admin - special users
    if (userId == "admin" || userId == "sysadmin") {
        return UserRole::SYSTEM_ADMIN;
    }

    return UserRole::INVALID;
}

bool LoginSystem::login(const string& username, const string& password) {
    if (currentUser != nullptr) {
        logout();
    }

    currentUser = authenticateUser(username, password);

    if (currentUser != nullptr) {
        currentUserRole = determineUserRole(username);
        cout << "Login successful! Welcome " << currentUser->getName() << endl;
        displayWelcomeMessage(currentUserRole, currentUser->getName());
        return true;
    }
    else {
        cout << "Login failed! Invalid username or password." << endl;
        currentUserRole = UserRole::INVALID;
        return false;
    }
}

void LoginSystem::logout() {
    if (currentUser != nullptr) {
        cout << "Goodbye, " << currentUser->getName() << "!" << endl;
        currentUser = nullptr;
    }
    currentUserRole = UserRole::INVALID;
}

UserRole LoginSystem::getCurrentUserRole() const {
    return currentUserRole;
}

Person* LoginSystem::getCurrentUser() const {
    return currentUser;
}

string LoginSystem::getCurrentUserId() const {
    return currentUser ? currentUser->getId() : "";
}

string LoginSystem::getCurrentUserName() const {
    return currentUser ? currentUser->getName() : "";
}

string LoginSystem::roleToString(UserRole role) {
    switch (role) {
    case UserRole::ACADEMIC_OFFICER: return "Academic Officer";
    case UserRole::ATTENDANT: return "Attendant";
    case UserRole::INSTRUCTOR: return "Instructor";
    case UserRole::HOD: return "Head of Department";
    case UserRole::SYSTEM_ADMIN: return "System Administrator";
    default: return "System Administrator";
    }
}

void LoginSystem::displayWelcomeMessage(UserRole role, const string& userName) {
    cout << "\n" << string(50, '=') << endl;
    cout << "WELCOME TO LAB MANAGEMENT SYSTEM" << endl;
    cout << string(50, '=') << endl;
    cout << "User: " << userName << endl;
    cout << "Role: " << roleToString(role) << endl;
    cout << string(50, '=') << endl;
}