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
        cout << "Admin Menu (to be built)" << endl;
    }
    else if (loggedIn->role == "Faculty")
    {
        cout << "Faculty Menu (to be built)" << endl;
    }

    else if (loggedIn->role == "Student")
    {
        studentMenu(loggedIn);
    }
}
