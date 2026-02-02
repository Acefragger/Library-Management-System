#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. USER ENTITY
class User {
public:
    string name, userID;
    User(string n, string id) : name(n), userID(id) {}
};

// 2. BOOK ENTITY
class Book {
private:
    string title, author, isbn, borrowerID;
    bool isAvailable;

public:
    Book(string t, string a, string i, bool avail = true, string bID = "None") 
        : title(t), author(a), isbn(i), isAvailable(avail), borrowerID(bID) {}

    string getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool checkAvailable() const { return isAvailable; }
    string getBorrower() const { return borrowerID; }
    
    void setAvailable(bool status, string bID = "None") { 
        isAvailable = status; 
        borrowerID = bID;
    }
};

// 3. LIBRARY CONTROLLER
class Library {
private:
    vector<Book> books;
    const string dbFile = "library_db.txt";

public:
    void loadData() {
        ifstream inFile(dbFile);
        if (!inFile) return;
        string line, t, a, i, s, bID;
        while (getline(inFile, line)) {
            stringstream ss(line);
            getline(ss, t, '|'); getline(ss, a, '|'); 
            getline(ss, i, '|'); getline(ss, s, '|'); getline(ss, bID, '|');
            books.push_back(Book(t, a, i, s == "1", bID));
        }
        inFile.close();
    }

    void saveData() {
        ofstream outFile(dbFile);
        for (const auto& b : books) {
            outFile << b.getTitle() << "|" << b.getAuthor() << "|" 
                    << b.getISBN() << "|" << b.checkAvailable() << "|" 
                    << b.getBorrower() << "\n";
        }
        outFile.close();
    }

    void addBook(Book b) {
        books.push_back(b);
        saveData();
    }

    // NEW: Functionality to remove books
    bool removeBook(string targetIsbn) {
        for (int i = 0; i < (int)books.size(); i++) {
            if (books[i].getISBN() == targetIsbn) {
                books.erase(books.begin() + i);
                saveData();
                return true;
            }
        }
        return false;
    }

    Book* search(string key) {
        for (int i = 0; i < (int)books.size(); i++) {
            if (books[i].getISBN() == key || books[i].getTitle() == key) {
                return &books[i];
            }
        }
        return 0;
    }
};

// 4. MAIN INTERFACE
int main() {
    srand(time(0));
    Library lib;
    lib.loadData();
    
    string currentUID = "None";
    cout << "--- Library Management System ---\n";
    cout << "1. New User (Register)\n2. Existing User (Login)\nChoice: ";
    int userType; cin >> userType; cin.ignore();

    if (userType == 1) {
        string name;
        cout << "Enter Name: "; getline(cin, name);
        currentUID = to_string(rand() % 9000 + 1000);
        cout << "Welcome " << name << "! Your generated UID is: " << currentUID << "\n";
    } else {
        cout << "Enter your UID: "; getline(cin, currentUID);
    }

    int choice;
    while (true) {
        cout << "\n[User: " << currentUID << "]\n";
        cout << "1. Add Book\n2. Remove Book\n3. Search & Borrow\n4. Return Book\n5. Exit\nChoice: ";
        if (!(cin >> choice)) break;
        cin.ignore();

        switch (choice) {
            case 1: { // ADD
                string t, a, i;
                cout << "Title: "; getline(cin, t);
                cout << "Author: "; getline(cin, a);
                cout << "ISBN: "; getline(cin, i);
                lib.addBook(Book(t, a, i));
                break;
            }
            case 2: { // REMOVE
                string i;
                cout << "Enter ISBN to remove: "; getline(cin, i);
                if (lib.removeBook(i)) cout << "Book removed.\n";
                else cout << "Book not found.\n";
                break;
            }
            case 3: { // SEARCH & BORROW
                string key;
                cout << "Search (Title/ISBN): "; getline(cin, key);
                Book* b = lib.search(key);
                if (b) {
                    cout << "Found: " << b->getTitle() << " [" << (b->checkAvailable() ? "Available" : "Borrowed by " + b->getBorrower()) << "]\n";
                    if (b->checkAvailable()) {
                        cout << "Borrow? (y/n): ";
                        char ans; cin >> ans;
                        if (ans == 'y') { b->setAvailable(false, currentUID); lib.saveData(); }
                    }
                } else cout << "Not found!\n";
                break;
            }
            case 4: { // RETURN
                string key;
                cout << "Return ISBN: "; getline(cin, key);
                Book* b = lib.search(key);
                if (b && !b->checkAvailable()) {
                    b->setAvailable(true, "None");
                    lib.saveData();
                    cout << "Returned successfully.\n";
                } else cout << "Invalid return.\n";
                break;
            }
            case 5: return 0;
        }
    }
}
