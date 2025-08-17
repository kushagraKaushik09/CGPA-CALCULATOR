#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional> // For std::hash
using namespace std;

const string DATABASE_FILE = "users.txt";

// Simple hash function (for demo purposes only)
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// Load all users from file into a map
unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream infile(DATABASE_FILE);
    string username, hashedPassword;

    while (infile >> username >> hashedPassword) {
        users[username] = hashedPassword;
    }

    infile.close();
    return users;
}

void registerUser() {
    string username, password;

    cout << "=== Register ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers();

    if (users.find(username) != users.end()) {
        cout << "Error: Username already exists.\n";
        return;
    }

    string hashed = hashPassword(password);
    ofstream outfile(DATABASE_FILE, ios::app); // append mode
    if (outfile.is_open()) {
        outfile << username << " " << hashed << "\n";
        outfile.close();
        cout << "Registration successful!\n";
    } else {
        cout << "Error: Could not open file.\n";
    }
}

void loginUser() {
    string username, password;

    cout << "=== Login ===\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    unordered_map<string, string> users = loadUsers();
    string hashed = hashPassword(password);

    if (users.find(username) != users.end() && users[username] == hashed) {
        cout << "Login successful. Welcome, " << username << "!\n";
    } else {
        cout << "Error: Invalid username or password.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
