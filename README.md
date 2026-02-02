**Online Library Management System (BSD 122)**

A robust, console-based Library Management System built with C++ using Object-Oriented Programming (OOP) principles. This project covers the full Software Development Life Cycle (SDLC) by implementing data persistence, user account management, and inventory control.

**🚀 Quick Start**

**_Prerequisites_**

A C++ compiler (GCC/MinGW) supporting C++11 or higher.

Ensure library_db.txt is located in the same directory as the executable.

How to Run

Open main.cpp in your preferred IDE (e.g., Dev-C++, VS Code).

Ensure the -std=c++11 flag is enabled in your compiler settings.

Build and Run the project.

**🛠️ Key Features**

Automated User Management: Automated 4-digit UID generation for new users and session-based login for existing members.

Full Inventory Lifecycle: Functionality to add new titles and remove existing books by ISBN.

Multi-Criteria Search: Efficient searching logic that handles both Title and ISBN queries.

Borrowing & Returning: Real-time state management of book availability linked to specific User UIDs.

Persistent Flat-File Backend: Data is serialized to library_db.txt using pipe-delimiters to ensure zero data loss between sessions.

**🏛️ OOP Design Choices**

This system adheres to core Software Engineering principles:

Encapsulation: Data members (Title, ISBN, Status) are kept private within the Book class, accessible only through public getters and setters to maintain data integrity.

Modularity: The system is partitioned into the Entity Layer (Book/User), Controller Layer (Library logic), and Interface Layer (CLI Menu).

Data Association: Books are logically linked to Users via borrowerID strings, simulating a relational database structure.

**📊 Testing & Verification**

A robust suite of Positive and Negative test cases was conducted to validate the system.

**Test Highlights:**

Positive: Verified successful registration, book addition, and the borrow/return cycle.

Negative: Verified that the system prevents borrowing unavailable books and handles invalid ISBN searches gracefully.

Detailed results can be found in the accompanying Testing_Log.xlsx file.

**📁 Repository Structure**

_main.cpp_: Core source code containing all class definitions and logic.

_library_db.txt_: The persistent database file for book records.

_System_Documentation.pdf_: Formal documentation.

_Test_Document.xlsx_: Detailed spreadsheet of all conducted test cases.

👤 **[Paul Kathuri]** BSD 122: Object-Oriented Programming 1

Assignment 1
