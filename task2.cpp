// task2.cpp : Defines the entry point for the application.
//


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isUserRegistered(const string& username) {
    ifstream infile(username + ".txt");
    return infile.good();
}

void registerUser() {
    string username, password;

    cout << "Enter a username: ";
    cin >> username;

    if (isUserRegistered(username)) {
        cout << "User already registered. Try logging in.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    ofstream outfile(username + ".txt");
    outfile << username << endl;
    outfile << password << endl;
    outfile.close();

    cout << "Registration successful!\n";
}

bool loginUser() {
    string username, password, fileUsername, filePassword;

    cout << "Enter your username: ";
    cin >> username;

    if (!isUserRegistered(username)) {
        cout << "User not registered. Please register first.\n";
        return false;
    }

    cout << "Enter your password: ";
    cin >> password;

    ifstream infile(username + ".txt");
    getline(infile, fileUsername);
    getline(infile, filePassword);

    infile.close();

    if (username == fileUsername && password == filePassword) {
        cout << "Login successful!\n";
        return true;
    }
    else {
        cout << "Invalid username or password.\n";
        return false;
    }
}

int main() {
    int choice;

    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        registerUser();
    }
    else if (choice == 2) {
        loginUser();
    }
    else {
        cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}
