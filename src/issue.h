// issue.h
#pragma once
#include <string>
using namespace std;

class Issue {
public:
    int issueId;
    string studentId;
    string title;
    string description;
    string status;

    Issue(int id, string sId, string t, string d) {
        issueId = id;
        studentId = sId;
        title = t;
        description = d;
        status = "Pending";
    }

    void updateStatus(string newStatus) {
        status = newStatus;
    }
};
