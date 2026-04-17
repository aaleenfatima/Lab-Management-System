

#include "datetime.h"
#include <iostream>
#include <ctime>
#include <sstream>
using namespace std;

// ============================================================================
// DateValidator Implementation
// ============================================================================

bool DateValidator::isValidYear(int year) {
    return year >= 2000 && year <= 2100;
}

bool DateValidator::isValidMonth(int month) {
    return month >= 1 && month <= 12;
}

bool DateValidator::isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

bool DateValidator::isValidDayForMonth(int year, int month, int day) {
    // Basic range check
    if (day < 1 || day > 31) return false;

    // February special handling (28 or 29 days)
    if (month == 2) {
        int maxDays = isLeapYear(year) ? 29 : 28;
        return day <= maxDays;
    }

    // Months with 30 days: April(4), June(6), September(9), November(11)
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }

    // All other months have 31 days
    return true;
}

bool DateValidator::isWeekend(int year, int month, int day) {
    // Create tm structure for date calculation
    tm timeinfo = {};
    timeinfo.tm_year = year - 1900;  // tm_year is years since 1900
    timeinfo.tm_mon = month - 1;      // tm_mon is 0-based (0=Jan)
    timeinfo.tm_mday = day;

    // Normalize the date and calculate day of week
    mktime(&timeinfo);
    int dayOfWeek = timeinfo.tm_wday; // 0=Sunday, 6=Saturday

    // Check if Saturday or Sunday
    return (dayOfWeek == 0 || dayOfWeek == 6);
}

bool DateValidator::isTooFarFuture(int year, int month, int day) {
    // Get current date
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    int currentYear = now.tm_year + 1900;
    int currentMonth = now.tm_mon + 1;
    int currentDay = now.tm_mday;

    // More than 2 years ahead
    if (year > currentYear + 2) return true;

    // Exactly 2 years ahead - check month
    if (year == currentYear + 2) {
        if (month > currentMonth) return true;
        if (month == currentMonth && day > currentDay) return true;
    }

    return false;
}

bool DateValidator::isPast(int year, int month, int day) {
    // Get current date
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    int currentYear = now.tm_year + 1900;
    int currentMonth = now.tm_mon + 1;
    int currentDay = now.tm_mday;

    // Compare year
    if (year < currentYear) return true;
    if (year > currentYear) return false;

    // Years equal, compare month
    if (month < currentMonth) return true;
    if (month > currentMonth) return false;

    // Months equal, compare day
    if (day < currentDay) return true;

    // Equal or future date
    return false;
}

bool DateValidator::isWithinReasonableSchedule(int year, int month, int day) {
    return !isPast(year, month, day) &&
        !isTooFarFuture(year, month, day) &&
        !isWeekend(year, month, day);
}

string DateValidator::getValidationMessage(int year, int month, int day,
    int hour, int minute) {
    // Check date validity first
    if (!isValidYear(year) || !isValidMonth(month) || !isValidDayForMonth(year, month, day)) {
        return "Invalid date. Please check year, month, and day values.";
    }

    // Check time validity
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return "Invalid time. Hour must be 0-23, minute must be 0-59.";
    }

    // Check if in the past
    if (isPast(year, month, day)) {
        return "Cannot schedule in the past. Please choose a future date/time.";
    }

    // Check if too far in future
    if (isTooFarFuture(year, month, day)) {
        return "Cannot schedule more than 2 years in advance.";
    }

    // Check if weekend
    if (isWeekend(year, month, day)) {
        return "Cannot schedule on weekends (Saturday or Sunday).";
    }

    // All validations passed
    return "Valid date/time for scheduling.";
}

// ============================================================================
// DateTime Implementation 
// ============================================================================

DateTime::DateTime(int y, int m, int d, int h, int min)
    : year(y), month(m), day(d), hour(h), minute(min) {
}

DateTime::DateTime() {
    // Get current time from system
    time_t t = time(0);
    tm now;
    localtime_s(&now, &t);

    // Extract date components
    year = now.tm_year + 1900;
    month = now.tm_mon + 1;
    day = now.tm_mday;
    hour = now.tm_hour;
    minute = now.tm_min;
}

// Utility Methods (unchanged, as they're not validation-related)
string DateTime::toString() const {
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
    return string(buffer);
}

string DateTime::toTimeString() const {
    char buffer[6];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
    return string(buffer);
}

string DateTime::toFullString() const {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d",
        year, month, day, hour, minute);
    return string(buffer);
}

bool DateTime::isSameDay(const DateTime& other) const {
    return year == other.year &&
        month == other.month &&
        day == other.day;
}

double DateTime::calculateHoursDifference(const DateTime& end) const {
    int startMinutes = hour * 60 + minute;
    int endMinutes = end.hour * 60 + end.minute;
    double hours = (endMinutes - startMinutes) / 60.0;
    return abs(hours);
}

// Serialization Methods
void DateTime::serialize(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&year), sizeof(year));
    out.write(reinterpret_cast<const char*>(&month), sizeof(month));
    out.write(reinterpret_cast<const char*>(&day), sizeof(day));
    out.write(reinterpret_cast<const char*>(&hour), sizeof(hour));
    out.write(reinterpret_cast<const char*>(&minute), sizeof(minute));
}

void DateTime::deserialize(ifstream& in) {
    in.read(reinterpret_cast<char*>(&year), sizeof(year));
    in.read(reinterpret_cast<char*>(&month), sizeof(month));
    in.read(reinterpret_cast<char*>(&day), sizeof(day));
    in.read(reinterpret_cast<char*>(&hour), sizeof(hour));
    in.read(reinterpret_cast<char*>(&minute), sizeof(minute));
}