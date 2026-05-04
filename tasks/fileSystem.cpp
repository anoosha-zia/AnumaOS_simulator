#include "fileSystem.h"
#include <fstream>
#include <iostream>

using namespace std;

/*
    createFile:
    Creates an empty file on simulated HDD
*/
bool FileSystem::createFile(string name) {

    ofstream file(name);

    if (file.is_open()) {
        cout << "[FS] File created: " << name << endl;
        file.close();
        return true;
    }

    cout << "[FS] Failed to create file\n";
    return false;
}

/*
    writeFile:
    Writes data into file (overwrites)
*/
bool FileSystem::writeFile(string name, string data) {

    ofstream file(name);

    if (file.is_open()) {
        file << data;
        file.close();
        cout << "[FS] Data written to: " << name << endl;
        return true;
    }

    cout << "[FS] Write failed\n";
    return false;
}

/*
    readFile:
    Reads file content
*/
string FileSystem::readFile(string name) {

    ifstream file(name);
    string data, line;

    if (file.is_open()) {

        while (getline(file, line)) {
            data += line + "\n";
        }

        file.close();
        return data;
    }

    return "[FS] File not found";
}

/*
    deleteFile:
    Deletes file from disk
*/
bool FileSystem::deleteFile(string name) {

    if (remove(name.c_str()) == 0) {
        cout << "[FS] File deleted: " << name << endl;
        return true;
    }

    cout << "[FS] Delete failed\n";
    return false;
}

/*
    fileExists:
    Checks file existence
*/
bool FileSystem::fileExists(string name) {

    ifstream file(name);
    return file.good();
}
