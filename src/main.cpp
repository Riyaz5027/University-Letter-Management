#include <iostream>
#include "user.h"
#include <vector>
#include "issue.h"

vector<Issue> issues;
int issueCounter = 1;

using namespace std;

// Declare functions
void seedUsers();
User *login(string id, string pass);

void adminMenu(User* admin);



void facultyMenu(User* faculty) {
    int choice;
    while (true) {
        cout << "\n--- Faculty Menu ---\n";
        cout << "1. View All Issues\n";
        cout << "2. Update Issue Status\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- All Issues ---\n";
            for (auto &iss : issues) {
                cout << "ID: " << iss.issueId 
                     << " | Student: " << iss.studentId
                     << " | Title: " << iss.title
                     << " | Status: " << iss.status << endl;
            }
        }
        else if (choice == 2) {
            int id;
            string newStatus;
            cout << "Enter Issue ID to update: ";
            cin >> id;
            cout << "Enter new status (In Progress / Resolved / Signed): ";
            cin.ignore();
            getline(cin, newStatus);

            bool found = false;
            for (auto &iss : issues) {
                if (iss.issueId == id) {
                    iss.updateStatus(newStatus);
                    cout << "✅ Status updated!\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "❌ Issue not found!\n";
        }
        else if (choice == 3) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
}

void studentMenu(User *student)
{
    int choice;
    while (true)
    {
        cout << "\n--- Student Menu ---\n";
        cout << "1. Submit Issue\n";
        cout << "2. View My Issues\n";
        cout << "3. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string title, desc;
            cout << "Enter issue title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter issue description: ";
            getline(cin, desc);

            Issue newIssue(issueCounter++, student->id, title, desc);
            issues.push_back(newIssue);

            cout << "✅ Issue submitted successfully with ID: " << newIssue.issueId << endl;
        }
        else if (choice == 2)
        {
            cout << "\n--- Your Issues ---\n";
            for (auto &iss : issues)
            {
                if (iss.studentId == student->id)
                {
                    cout << "ID: " << iss.issueId
                         << " | Title: " << iss.title
                         << " | Status: " << iss.status << endl;
                }
            }
        }
        else if (choice == 3)
        {
            cout << "Logging out...\n";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
}

void adminMenu(User* admin) {
    int choice;
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View All Users\n";
        cout << "2. Add User\n";
        cout<< "3. Show system Info\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- All Users ---\n";
            for (auto &u : users) {
                cout << "ID: " << u.id 
                     << " | Role: " << u.role << endl;
            }
        }
        else if (choice == 2) {
            string newId, newPass, newRole;
            cout << "Enter new user ID: ";
            cin >> newId;
            cout << "Enter password: ";
            cin >> newPass;
            cout << "Enter role (Admin / Faculty / Student): ";
            cin >> newRole;

            users.push_back(User(newId, newPass, newRole));
            cout << "✅ User added successfully!\n";
        }
        else if (choice == 3)
        {
            cout << "System running with " << users.size() << " users and " << issues.size() << " issues.\n";
        }
        else if (choice == 4) {
            cout << "Logging out...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
           
        }
    }
}


int main()
{
    seedUsers();

    string id, pass;
    cout << "Login ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    User *loggedIn = login(id, pass);

    if (loggedIn == nullptr)
    {
        cout << "Invalid credentials!" << endl;
        return 0;
    }

    cout << "Welcome, " << loggedIn->id << " (" << loggedIn->role << ")" << endl;

    if (loggedIn->role == "Admin")
    {
        adminMenu(loggedIn);
    }
    else if (loggedIn->role == "Faculty")
    {
         facultyMenu(loggedIn);
    }

    else if (loggedIn->role == "Student")
    {
        studentMenu(loggedIn);
    }
}
