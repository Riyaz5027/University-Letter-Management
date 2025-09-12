#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
public:
    std::string id;       // unique login id
    std::string password; // plain for now (we'll keep hashing optional later)
    std::string role;     // "Admin", "Faculty", "Student"
    std::string dept;     // e.g., "CSE", "ME" (faculty & student)
    std::string name;     // full name

    User() {}
    User(const std::string& uid, const std::string& pass, const std::string& r,
         const std::string& d = "", const std::string& nm = "")
        : id(uid), password(pass), role(r), dept(d), name(nm) {}

    // serialize user to a single-line string for file storage:
    std::string serialize() const {
        // id|password|role|dept|name
        return id + "|" + password + "|" + role + "|" + dept + "|" + name;
    }

    // parse a serialized user line
    static User deserialize(const std::string &line) {
        size_t pos = 0;
        std::string parts[5];
        int i = 0;
        size_t start = 0;
        for (i = 0; i < 4; ++i) {
            pos = line.find('|', start);
            if (pos == std::string::npos) break;
            parts[i] = line.substr(start, pos - start);
            start = pos + 1;
        }
        // last part = rest of line
        parts[4] = line.substr(start);
        return User(parts[0], parts[1], parts[2], parts[3], parts[4]);
    }
};

// declare the global users vector (defined in auth.cpp)
extern std::vector<User> users;

#endif // USER_H
