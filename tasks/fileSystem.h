#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
using namespace std;

class FileSystem {

public:

    bool createFile(string name);
    bool writeFile(string name, string data);
    string readFile(string name);
    bool deleteFile(string name);
    bool fileExists(string name);

};

#endif
