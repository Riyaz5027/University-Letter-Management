# 🎓 University Letter Management System

A **console-based C++ application** to manage student issues and letter submissions in a university environment.  
This project reduces the need for students to physically visit multiple departments for issue resolution and provides a structured way for faculty and admin to manage requests.

---

## 🚀 Overview

In most universities, students face challenges when resolving issues like grade corrections, administrative approvals, or departmental letters.  
Traditionally, they must:

- Visit different offices manually  
- Wait in queues  
- Collect multiple approvals  

This project simplifies that process by providing:  

- **Students** → register, log in, and submit issues to departments.  
- **Faculty/HOD** → review and update issue status for their department.  
- **Admin** → manage users (faculty accounts) and monitor the system.  

Data persistence is implemented via file storage (`users.txt`, `issues.txt`) so that user accounts and issues are not lost when the program exits.

---

## 🔎 Problem

In universities, resolving student issues (like approvals, timetable corrections, or administrative requests) is still largely **paper-based** and inefficient.  
Some challenges we observed:

- Students wait for hours to get signatures or guidance.  
- Multiple visits across departments for stamps and approvals.  
- Heavy reliance on paper proofs (risk of loss or duplication).  
- No guarantee issues are resolved on time (letters may remain pending).  
- Faculty often busy in meetings → delays in addressing urgent problems.  
- No **issue tracking system** for students or staff.  

This leads to **wasted time**, **inefficient workflows**, and **frustration** for both students and faculty.  

---

## 💡 Solution

The **University Letter Management System** streamlines this process by moving it online:  

- **Students** → register, log in, and submit issues to specific departments.  
- **Faculty/HOD** → view issues for their department, suggest solutions, and update status.  
- **Admin** → manage faculty accounts and monitor the system.  

### ✅ Benefits
- No need to roam across departments physically.  
- Real-time status tracking for issues.  
- Workload distribution among faculty.  
- Faster, organized resolution of problems.  
- Eliminates paper dependency.  

---



## ✨ Features

- **Role-based access**
  - **Admin** (hardcoded) → can create Faculty accounts.  
  - **Faculty** → view and update issues of their department.  
  - **Students** → register, log in, submit issues, and view status.

- **Authentication**
  - Login system with ID & password.  
  - Ensures only valid users can access the system.

- **Issue Management**
  - Students submit new issues (title + description + department).  
  - Each issue gets a unique ID.  
  - Faculty can assign themselves to issues and update status.  
  - Students can track only *their own* issues.

- **Persistence**
  - Users stored in `users.txt`.  
  - Issues stored in `issues.txt`.  
  - Automatically loads on program start and saves on exit.

- **Scalable Design**
  - Code is modular and structured with **OOP principles** (classes `User`, `Issue`).  
  - Easily extendable (multi-department routing, encryption, DB support).

---

## 🛠️ Tech Stack

- **Language:** C++17  
- **Data Structures:** `vector`, `unordered_map` (for fast user/issue lookups)  
- **Concepts Used:** Encapsulation, Inheritance (roles), File I/O, Pointers, Role-based routing  

---

## 📂 Project Structure
```
University-Letter-Management/
├── src/
│   ├── main.cpp        # Main program & menus
│   ├── auth.cpp        # Authentication, persistence, user registration
│   ├── user.h          # User class definition
│   ├── issue.h         # Issue class definition
├── users.txt           # Saved users
├── issues.txt          # Saved issues
├── README.md           # Project documentation
├── LICENSE             # MIT License
└── .gitignore
```



---
## ⚡ Setup & Usage

### Requirements
- g++ (C++11 or later)  
- Git (if cloning)  
- Terminal / PowerShell  

### Installation

```bash
# Clone the repo
git clone https://github.com/Riyaz5027/University-Letter-Management.git
cd University-Letter-Management

# Compile
g++ src/main.cpp src/auth.cpp -o main

# Run (Linux/Mac)
./main

# Run (Windows)
main.exe

```

## 🎮 Example Workflow

### 👩‍🎓 Student
1. **Register:** Enter name, ID, password, and department.
2. **Log In:** Access the system as a student.
3. **Submit Issue:** Provide title, description, and select department.
4. **Track Issues:** View submitted issues and monitor their status.

### 👨‍🏫 Faculty
1. **Log In:** Access the system as faculty.
2. **View Issues:** See issues assigned to their department.
3. **Manage Issues:** Assign themselves to issues and update status.

### 👨‍💼 Admin
1. **Log In:** Use default credentials (`id=admin`, `password=admin123`).
2. **Create Faculty Accounts:** Ensure at least one admin and faculty exist.
3. **System Oversight:** Monitor and manage users and overall system health.

---

## 🧭 Planned Enhancements

- **Password Hashing:** Secure user credentials.
- **Multi-Department Issues:** Allow students to submit issues to multiple departments.
- **Detailed Issue States:** Support for Pending, In Review, Resolved, and Rejected statuses.
- **Database Integration:** Transition from file-based storage to SQLite/MySQL.
- **User Interface:** Develop GUI or web-based frontend.

---

## 📜 License

[Licensed under the MIT License](https://opensource.org/licenses/MIT). See [`LICENSE`](LICENSE) for details.

---

## 🤝 Contribution

Contributions are welcome!  
To contribute:
1. Fork the repository.
2. Create a new branch (`feature/your-feature`).
3. Commit your changes.
4. Push and open a Pull Request.

---

## 👨‍💻 Developed by

[**Riyaz5027**](https://github.com/Riyaz5027)

---



