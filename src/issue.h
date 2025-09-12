// issue.h
#pragma once
#include <string>
#include <sstream>
using namespace std;

class Issue {
public:
    int issueId;
    std::string studentId;
    std::string title;
    std::string description;
    std::string dept;        // department
    std::string status;      // Pending, In Progress, Resolved, Signed, ...
    std::string assignedTo;  // faculty id, empty if unassigned

    Issue() : issueId(0), status("Pending") {}
    Issue(int id, const std::string &sid, const std::string &t, const std::string &d, const std::string &department)
        : issueId(id), studentId(sid), title(t), description(d), dept(department), status("Pending"), assignedTo("") {}

    std::string serialize() const {
        // id|studentId|title|description|dept|status|assignedTo
        // replace newlines in text (rudimentary)
        std::string t = title;
        std::string desc = description;
        // (for simplicity we don't escape pipes; avoid using '|' in inputs)
        std::ostringstream oss;
        oss << issueId << "|" << studentId << "|" << t << "|" << desc << "|" << dept << "|" << status << "|" << assignedTo;
        return oss.str();
    }

    static Issue deserialize(const std::string &line) {
        Issue it;
        size_t start = 0, pos;
        std::string parts[7];
        int i = 0;
        for (i = 0; i < 6; ++i) {
            pos = line.find('|', start);
            if (pos == std::string::npos) break;
            parts[i] = line.substr(start, pos - start);
            start = pos + 1;
        }
        parts[6] = line.substr(start);
        it.issueId = std::stoi(parts[0]);
        it.studentId = parts[1];
        it.title = parts[2];
        it.description = parts[3];
        it.dept = parts[4];
        it.status = parts[5];
        it.assignedTo = parts[6];
        return it;
    }

    void assignToFaculty(const std::string &fid) {
        assignedTo = fid;
    }
    void updateStatus(const std::string &s) {
        status = s;
    }
};
