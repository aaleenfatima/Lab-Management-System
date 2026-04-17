#ifndef MAKEUPREQUEST_H
#define MAKEUPREQUEST_H

#include "datetime.h"
#include <string>
#include <fstream>

class MakeupRequest {
private:
    std::string requestId;
    std::string sectionId;
    std::string instructorId;
    std::string reason;
    DateTime requestedDate;
    DateTime preferredDate;
    std::string status; // "PENDING", "APPROVED", "REJECTED"
    DateTime scheduledDate; // Only when approved
    std::string scheduledBy; // Academic officer who approved

public:
    MakeupRequest(const std::string& reqId, const std::string& secId,
        const std::string& instId, const std::string& reason,
        const DateTime& reqDate, const DateTime& prefDate);

    // Getters
    std::string getRequestId() const { return requestId; }
    std::string getSectionId() const { return sectionId; }
    std::string getInstructorId() const { return instructorId; }
    std::string getReason() const { return reason; }
    DateTime getRequestedDate() const { return requestedDate; }
    DateTime getPreferredDate() const { return preferredDate; }
    std::string getStatus() const { return status; }
    DateTime getScheduledDate() const { return scheduledDate; }
    std::string getScheduledBy() const { return scheduledBy; }

    // Setters for approval
    void approve(const DateTime& scheduledDate, const std::string& approvedBy);
    void reject(const std::string& rejectedBy);

    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};

#endif
