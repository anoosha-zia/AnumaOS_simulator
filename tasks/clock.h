#ifndef CLOCK_H
#define CLOCK_H
#include<mutex>
#include <string>

class Clock {

private:
    std::string currentTime;   
    std::mutex m;
public:
    Clock();
    void start();
    std::string getTime();     
};

#endif
