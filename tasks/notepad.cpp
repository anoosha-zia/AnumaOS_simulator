#include "notepad.h"
#include <iostream>

using namespace std;

Notepad::Notepad(string file) {
    filename = file;
    fs.createFile(filename);
}

/*
    write:
    Overwrites file content
*/
void Notepad::write(string text) {
    fs.writeFile(filename, text);
}

/*
    append:
    Adds text to existing file
*/
void Notepad::append(string text) {

    string old = fs.readFile(filename);
    fs.writeFile(filename, old + text);
}

/*
    autoSave:
    Simulates auto-save feature
*/
void Notepad::autoSave(string text) {

    fs.writeFile(filename, text);
    cout << "[Notepad] Auto-Saved...\n";
}

/*
    view:
    Displays file content
*/
void Notepad::view() {

    cout << "\n--- NOTEPAD CONTENT ---\n";
    cout << fs.readFile(filename) << endl;
}
void Notepad::start() {

    int choice;
    string text;

    while (true) {

        cout << "\n--- NOTEPAD ---\n";
        cout << "1. Write\n2. Append\n3. View\n4. AutoSave\n5. Exit\n";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter text: ";
            getline(cin, text);
            write(text);
        }

        else if (choice == 2) {
            cout << "Enter text: ";
            getline(cin, text);
            append(text);
        }

        else if (choice == 3) {
            view();
        }

        else if (choice == 4) {
            cout << "Enter text: ";
            getline(cin, text);
            autoSave(text);
        }

        else {
            cout << "[Notepad] Exiting...\n";
            break;
        }
    }
}
