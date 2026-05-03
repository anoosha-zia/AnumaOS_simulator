#include "Notepad.h"
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
