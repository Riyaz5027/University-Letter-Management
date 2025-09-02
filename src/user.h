#pragma once
#include <string>
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
