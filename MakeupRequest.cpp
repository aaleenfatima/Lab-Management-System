#include "MakeupRequest.h"
#include <fstream>

MakeupRequest::MakeupRequest(const std::string& reqId, const std::string& secId,
    const std::string& instId, const std::string& reason,
    const DateTime& reqDate, const DateTime& prefDate)
    : requestId(reqId), sectionId(secId), instructorId(instId), reason(reason),
    requestedDate(reqDate), preferredDate(prefDate), status("PENDING") {
}

void MakeupRequest::approve(const DateTime& scheduledDt, const std::string& approvedBy) {
    status = "APPROVED";
    scheduledDate = scheduledDt;
    scheduledBy = approvedBy;
}

void MakeupRequest::reject(const std::string& rejectedBy) {
    status = "REJECTED";
    scheduledBy = rejectedBy;
}

void MakeupRequest::serialize(std::ofstream& out) const {
    if (!out.good()) return;

    // Serialize string fields
    size_t len = requestId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(requestId.c_str(), len);

    len = sectionId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(sectionId.c_str(), len);

    len = instructorId.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(instructorId.c_str(), len);

    len = reason.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(reason.c_str(), len);

    len = status.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(status.c_str(), len);

    len = scheduledBy.length();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    out.write(scheduledBy.c_str(), len);

    // Serialize DateTime objects
    requestedDate.serialize(out);
    preferredDate.serialize(out);
    scheduledDate.serialize(out);
}

void MakeupRequest::deserialize(std::ifstream& in) {
    if (!in.good()) return;

    size_t len;

    // Deserialize string fields
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    requestId.resize(len);
    in.read(&requestId[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    sectionId.resize(len);
    in.read(&sectionId[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    instructorId.resize(len);
    in.read(&instructorId[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    reason.resize(len);
    in.read(&reason[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    status.resize(len);
    in.read(&status[0], len);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    scheduledBy.resize(len);
    in.read(&scheduledBy[0], len);

    // Deserialize DateTime objects
    requestedDate.deserialize(in);
    preferredDate.deserialize(in);
    scheduledDate.deserialize(in);
}