#include <iostream>
#include "user.h"
using namespace std;

// Declare functions
void seedUsers();
User* login(string id, string pass);

int main() {
    seedUsers();

    string id, pass;
    cout << "Login ID: ";
    cin >> id;
    cout << "Password: ";
    cin >> pass;

    User* loggedIn = login(id, pass);

    if (loggedIn == nullptr) {
        cout << "Invalid credentials!" << endl;
        return 0;
    }

    cout << "Welcome, " << loggedIn->id << " (" << loggedIn->role << ")" << endl;

    if (loggedIn->role == "Admin") {
        cout << "Admin Menu (to be built)" << endl;
    } else if (loggedIn->role == "Student") {
        cout << "Student Menu (to be built)" << endl;
    } else if (loggedIn->role == "Faculty") {
        cout << "Faculty Menu (to be built)" << endl;
    }
}
