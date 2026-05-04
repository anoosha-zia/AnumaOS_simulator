#ifndef CLOCK_H
#define CLOCK_H

#include <string>

class Clock {

private:
    std::string currentTime;   

public:
    Clock();
    void start();
    std::string getTime();     
};

#endif
