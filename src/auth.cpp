#include <iostream>
#include <vector>
#include "user.h"
extern std::vector<User> users;

using namespace std;

vector<User> users;

// Add some sample users
void seedUsers() {
    users.push_back(User("admin", "admin123", "Admin"));
    users.push_back(User("student1", "pass1", "Student"));
    users.push_back(User("hod1", "hodpass", "Faculty"));
}

User* login(string id, string pass) {
    for (auto &u : users) {
        if (u.id == id && u.password == pass) {
            return &u;
        }
    }
    return nullptr;
}
