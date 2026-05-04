#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <string>
#include "fileSystem.h"

using namespace std;

class Notepad {

private:
    FileSystem fs;
    string filename;

public:

    Notepad(string file);

    void write(string text);
    void append(string text);
    void autoSave(string text);
    void view();
    void start();

};

#endif
