#pragma once
#ifndef USER_H
#define USER_H
#include <string>
#include <vector>

using namespace std;

class User {
public:
    string id;
    string password;
    string role;

    User(string i, string p, string r) {
        id = i;
        password = p;
        role = r;
    }
};

extern std::vector<User> users;

#endif
