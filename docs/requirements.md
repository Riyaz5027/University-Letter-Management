# University Letter Management System

## Overview
This project is a console-based University Letter/Issue Management System.  
It allows Students, Faculty, and Admins to manage academic and administrative issues in a structured way.

### Roles:
- **Admin**: Can create Faculty accounts, ensure the system has at least one admin user.
- **Faculty (HOD/Professor)**: Can view issues from their department and update status.
- **Student**: Can register, log in, and raise/view their issues.

---

## Features Implemented
- Login and authentication (with persistence in `users.txt`).
- Hardcoded Admin is always available (`id: admin`, `pass: admin123`).
- Student registration (saved to `users.txt`).
- Faculty creation by Admin.
- Issue creation by Students (saved to `issues.txt`).
- View issues based on role:
  - Students → can only view their own issues.
  - Faculty → can view issues from their department or assigned to them.
  - Admin → has global access.
- File persistence (data is stored in text files for reloading on restart).

---

## Requirements
- C++17 or later
- g++ compiler
- Git (for version control)
- OS: Works on Windows/Linux/Mac (tested with Windows PowerShell and Ubuntu).

---

## How to Build
```bash
g++ src/main.cpp src/auth.cpp -o main
```

## How to run
- You can use the Editor's run button
- Just type ./main if you are linux/mac
- main.exe for windows