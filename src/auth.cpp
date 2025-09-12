#include "user.h"
#include <fstream>
#include <iostream>
#include <sstream>

// define the global users vector here
std::vector<User> users;

// ---- USERS FILE I/O ----
const std::string USERS_FILE = "users.txt";

void saveUsers() {
    std::ofstream out(USERS_FILE);
    if (!out.is_open()) return;
    for (auto &u : users) {
        out << u.serialize() << "\n";
    }
    out.close();
}

void loadUsers() {
    users.clear();
    std::ifstream in(USERS_FILE);
    if (!in.is_open()) return;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        users.push_back(User::deserialize(line));
    }
    in.close();
}

// ensure a hardcoded admin exists (admin is not removed)
void ensureAdmin() {
    bool found = false;
    for (auto &u : users) if (u.role == "Admin") { found = true; break; }
    if (!found) {
        users.push_back(User("admin", "admin123", "Admin", "", "Administrator"));
        saveUsers();
    }
}

// call this at program start
void seedUsers() {
    loadUsers();
    ensureAdmin();
}

// returns pointer to user in users vector, or nullptr
User* login(const std::string &id, const std::string &pass) {
    for (auto &u : users) {
        if (u.id == id && u.password == pass) return &u;
    }
    return nullptr;
}

// registers a new student (returns pointer or nullptr if id exists)
User* registerStudent(const std::string &name, const std::string &uid, const std::string &pass, const std::string &dept) {
    for (auto &u : users) if (u.id == uid) return nullptr; // id exists
    users.push_back(User(uid, pass, "Student", dept, name));
    saveUsers();
    return &users.back();
}

// admin creates faculty
bool createFaculty(const std::string &fid, const std::string &pass, const std::string &dept, const std::string &name) {
    for (auto &u : users) if (u.id == fid) return false; // already exists
    users.push_back(User(fid, pass, "Faculty", dept, name));
    saveUsers();
    return true;
}
