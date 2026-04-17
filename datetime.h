/**
 * @file datetime.h
 * @brief DateTime class for managing dates and times with validation
 * @details Provides comprehensive date/time handling with validation rules
 *          specific to lab scheduling (weekday-only, reasonable future dates)
 */

#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <fstream>

 /**
  * @class DateValidator
  * @brief Handles date validation logic extracted from DateTime
  */
class DateValidator {
public:
    /**
     * @brief Validates year is within acceptable range
     * @param year Year to validate
     * @return true if year is between 2000 and 2100 (inclusive)
     */
    static bool isValidYear(int year);

    /**
     * @brief Validates month is within calendar range
     * @param month Month to validate
     * @return true if month is between 1 and 12 (inclusive)
     */
    static bool isValidMonth(int month);

    /**
     * @brief Determines if year is a leap year
     * @param year Year to check
     * @return true if year is divisible by 4, except centuries unless divisible by 400
     */
    static bool isLeapYear(int year);

    /**
     * @brief Validates day is appropriate for the current month
     * @param year Year for leap year calculation
     * @param month Month to validate day against
     * @param day Day to validate
     * @return true if day is within valid range for the month
     */
    static bool isValidDayForMonth(int year, int month, int day);

    /**
     * @brief Checks if date falls on Saturday or Sunday
     * @param year Year to check
     * @param month Month to check
     * @param day Day to check
     * @return true if date is Saturday or Sunday
     */
    static bool isWeekend(int year, int month, int day);

    /**
     * @brief Checks if date is too far in the future (more than 2 years)
     * @param year Year to check
     * @param month Month to check
     * @param day Day to check
     * @return true if date is more than 2 years from current date
     */
    static bool isTooFarFuture(int year, int month, int day);

    /**
     * @brief Checks if date is in the past
     * @param year Year to check
     * @param month Month to check
     * @param day Day to check
     * @return true if date is before current system date
     */
    static bool isPast(int year, int month, int day);

    /**
     * @brief Comprehensive validation for lab scheduling
     * @param year Year to validate
     * @param month Month to validate
     * @param day Day to validate
     * @return true if date passes all scheduling requirements
     */
    static bool isWithinReasonableSchedule(int year, int month, int day);

    /**
     * @brief Generates user-friendly error message for validation failures
     * @param year Year to validate
     * @param month Month to validate
     * @param day Day to validate
     * @param hour Hour to validate (optional, for time validation)
     * @param minute Minute to validate (optional, for time validation)
     * @return String describing validation failure or success
     */
    static std::string getValidationMessage(int year, int month, int day,
        int hour = 0, int minute = 0);
};

/**
 * @class DateTime
 * @brief Represents a date and time with validation capabilities
 *
 * Stores date (year, month, day) and time (hour, minute) components.
 * Provides validation for lab scheduling context using DateValidator helper.
 */
class DateTime {
private:
    int year;   // Valid range: 2000-2100
    int month;  // Valid range: 1-12
    int day;    // Valid range: 1-31 (depending on month)
    int hour;   // Valid range: 0-23
    int minute; // Valid range: 0-59

public:
    /**
     * @brief Constructs DateTime with specified date and time
     * @param y Year (2000-2100 for valid scheduling)
     * @param m Month (1-12)
     * @param d Day (1-31, depending on month)
     * @param h Hour (0-23), defaults to 0
     * @param min Minute (0-59), defaults to 0
     */
    DateTime(int y, int m, int d, int h = 0, int min = 0);

    /**
     * @brief Constructs DateTime with current system date and time
     */
    DateTime();

    // Getters
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }

    // Validation methods - now simplified using DateValidator

    /**
     * @brief Validates date components (year, month, day)
     * @return true if date is valid according to calendar rules
     */
    bool isValidDate() const {
        return DateValidator::isValidYear(year) &&
            DateValidator::isValidMonth(month) &&
            DateValidator::isValidDayForMonth(year, month, day);
    }

    /**
     * @brief Validates time components (hour, minute)
     * @return true if hour is 0-23 and minute is 0-59
     */
    bool isValidTime() const {
        return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
    }

    /**
     * @brief Validates both date and time components
     * @return true if both date and time are valid
     */
    bool isValidDateTime() const {
        return isValidDate() && isValidTime();
    }

    /**
     * @brief Checks if this datetime is in the past
     * @return true if datetime is before current system time
     */
    bool isPast() const {
        return DateValidator::isPast(year, month, day) ||
            (DateValidator::isPast(year, month, day) && !isValidTime());
    }

    /**
     * @brief Checks if datetime is too far in the future
     * @return true if datetime is more than 2 years from now
     */
    bool isTooFarFuture() const {
        return DateValidator::isTooFarFuture(year, month, day);
    }

    /**
     * @brief Checks if date falls on a weekend
     * @return true if date is Saturday or Sunday
     */
    bool isWeekend() const {
        return DateValidator::isWeekend(year, month, day);
    }

    /**
     * @brief Comprehensive check for reasonable scheduling
     * @return true if date is valid, not past, not too far future, and not weekend
     */
    bool isWithinReasonableSchedule() const {
        return DateValidator::isWithinReasonableSchedule(year, month, day) && isValidTime();
    }

    /**
     * @brief Gets human-readable validation error message
     * @return String describing why datetime is invalid, or success message
     */
    std::string getValidationMessage() const {
        return DateValidator::getValidationMessage(year, month, day, hour, minute);
    }

    // Utility functions (unchanged as they're not validation-related)
    std::string toString() const;
    std::string toTimeString() const;
    std::string toFullString() const;
    bool isSameDay(const DateTime& other) const;
    double calculateHoursDifference(const DateTime& end) const;

    // Serialization
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};

#endif