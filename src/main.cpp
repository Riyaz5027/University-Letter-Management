#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "user.h"
#include "issue.h"

// functions from auth.cpp
void seedUsers();
User* login(const std::string &id, const std::string &pass);
User* registerStudent(const std::string &name, const std::string &uid, const std::string &pass, const std::string &dept);
bool createFaculty(const std::string &fid, const std::string &pass, const std::string &dept, const std::string &name);

// globals for issues
std::vector<Issue> issues;
int issueCounter = 1;
const std::string ISSUES_FILE = "issues.txt";

// issue persistence
void saveIssues() {
    std::ofstream out(ISSUES_FILE);
    if (!out.is_open()) return;
    for (auto &iss : issues) out << iss.serialize() << "\n";
    out.close();
}

void loadIssues() {
    issues.clear();
    std::ifstream in(ISSUES_FILE);
    if (!in.is_open()) { issueCounter = 1; return; }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        issues.push_back(Issue::deserialize(line));
    }
    in.close();
    if (!issues.empty()) issueCounter = issues.back().issueId + 1;
}

// forward declarations of menus
void studentMenu(User* student);
void facultyMenu(User* faculty);
void adminMenu(User* admin);

// top-level register/login menu
int main() {
    seedUsers();
    loadIssues();

    while (true) {
        std::cout << "\n=== University Letter Management ===\n";
        std::cout << "1. Register (Student)\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose: ";
        int choice; std::cin >> choice;
        if (choice == 1) {
            std::cin.ignore();
            std::string name, uid, pass, dept;
            std::cout << "Full name: "; std::getline(std::cin, name);
            std::cout << "University ID: "; std::getline(std::cin, uid);
            std::cout << "Password: "; std::getline(std::cin, pass);
            std::cout << "Department (e.g. CSE): "; std::getline(std::cin, dept);
            User* u = registerStudent(name, uid, pass, dept);
            if (u) std::cout << "Registered! You can now login with ID: " << uid << "\n";
            else std::cout << "ID already exists. Try another.\n";
        }
        else if (choice == 2) {
            std::string id, pass;
            std::cout << "Login ID: "; std::cin >> id;
            std::cout << "Password: "; std::cin >> pass;
            User* me = login(id, pass);
            if (!me) { std::cout << "Invalid credentials.\n"; continue; }
            std::cout << "Welcome " << me->name << " (" << me->role << ")\n";
            if (me->role == "Student") studentMenu(me);
            else if (me->role == "Faculty") facultyMenu(me);
            else if (me->role == "Admin") adminMenu(me);
        }
        else break;
    }

    std::cout << "Goodbye.\n";
    return 0;
}

// ---------- Menus ----------

void studentMenu(User* student) {
    while (true) {
        std::cout << "\n--- Student Menu ---\n";
        std::cout << "1. Submit Issue\n2. View My Issues\n3. Logout\nChoose: ";
        int ch; std::cin >> ch;
        if (ch == 1) {
            std::cin.ignore();
            std::string title, desc;
            std::cout << "Title: "; std::getline(std::cin, title);
            std::cout << "Description: "; std::getline(std::cin, desc);
            std::string dept = student->dept;
            if (dept.empty()) {
                std::cout << "Department: "; std::getline(std::cin, dept);
            }
            Issue it(issueCounter++, student->id, title, desc, dept);
            issues.push_back(it);
            saveIssues();
            std::cout << "[OK] Issue submitted (ID=" << it.issueId << ", dept=" << dept << ")\n";
        }
        else if (ch == 2) {
            std::cout << "\n--- Your Issues ---\n";
            bool any = false;
            for (auto &iss : issues) {
                if (iss.studentId == student->id) {
                    any = true;
                    std::cout << iss.issueId << " | " << iss.title << " | " << iss.status;
                    if (!iss.assignedTo.empty()) std::cout << " | AssignedTo: " << iss.assignedTo;
                    std::cout << "\n";
                }
            }
            if (!any) std::cout << "No issues found.\n";
        }
        else break;
    }
}

void facultyMenu(User* faculty) {
    while (true) {
        std::cout << "\n--- Faculty Menu (dept=" << faculty->dept << ") ---\n";
        std::cout << "1. View Dept / Assigned Issues\n2. Claim Issue\n3. Update Issue Status\n4. Logout\nChoose: ";
        int ch; std::cin >> ch;
        if (ch == 1) {
            bool any = false;
            for (auto &iss : issues) {
                if (iss.dept == faculty->dept || iss.assignedTo == faculty->id) {
                    any = true;
                    std::cout << iss.issueId << " | " << iss.studentId << " | " << iss.title
                              << " | " << iss.status << " | AssignedTo: " << (iss.assignedTo.empty() ? "none" : iss.assignedTo) << "\n";
                }
            }
            if (!any) std::cout << "No issues for your dept/assignment.\n";
        }
        else if (ch == 2) {
            int id; std::cout << "Issue ID to claim: "; std::cin >> id;
            bool found = false;
            for (auto &iss : issues) {
                if (iss.issueId == id && iss.dept == faculty->dept) {
                    iss.assignToFaculty(faculty->id);
                    saveIssues();
                    std::cout << "Claimed issue " << id << "\n";
                    found = true; break;
                }
            }
            if (!found) std::cout << "Issue not found or not in your dept.\n";
        }
        else if (ch == 3) {
            int id; std::cout << "Issue ID to update: "; std::cin >> id;
            std::cin.ignore();
            std::string newStatus; std::cout << "New status: "; std::getline(std::cin, newStatus);
            bool found = false;
            for (auto &iss : issues) {
                if (iss.issueId == id && (iss.assignedTo == faculty->id || iss.dept == faculty->dept)) {
                    iss.updateStatus(newStatus);
                    saveIssues();
                    std::cout << "Status updated.\n";
                    found = true; break;
                }
            }
            if (!found) std::cout << "Issue not found or not authorized.\n";
        }
        else break;
    }
}

void adminMenu(User* admin) {
    while (true) {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. View Users\n2. Create Faculty\n3. System Info\n4. Logout\nChoose: ";
        int ch; std::cin >> ch;
        if (ch == 1) {
            for (auto &u : users) {
                std::cout << u.id << " | " << u.role << " | " << u.dept << " | " << u.name << "\n";
            }
        }
        else if (ch == 2) {
            std::cin.ignore();
            std::string fid, pass, dept, name;
            std::cout << "Faculty ID: "; std::getline(std::cin, fid);
            std::cout << "Password: "; std::getline(std::cin, pass);
            std::cout << "Dept: "; std::getline(std::cin, dept);
            std::cout << "Full name: "; std::getline(std::cin, name);
            if (createFaculty(fid, pass, dept, name)) std::cout << "Faculty created.\n";
            else std::cout << "ID exists.\n";
        }
        else if (ch == 3) {
            std::cout << "System has " << users.size() << " users and " << issues.size() << " issues.\n";
        }
        else break;
    }
}
