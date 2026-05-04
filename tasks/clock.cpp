#include "clock.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include<mutex>
#include<string>
using namespace std;
Clock::Clock() {currentTime="";}

void Clock::start() {

    while (true) {

        time_t now = time(0);

        std::string tim = string(ctime(&now));

        m.lock();
        currentTime = tim;
        m.unlock();

        this_thread::sleep_for(chrono::seconds(1));
        
    }
}

std::string Clock::getTime() {
    return currentTime;
}
