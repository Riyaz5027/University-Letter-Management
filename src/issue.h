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

    Issue(int id, string sid, string t, string d) {
        issueId = id;
        studentId = sid;
        title = t;
        description = d;
        status = "Pending";
    }
};
