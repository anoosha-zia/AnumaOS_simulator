#include "clock.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

Clock::Clock() {}

void Clock::start() {

    while (true) {

        time_t now = time(0);
        currentTime = std::string(ctime(&now));

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

std::string Clock::getTime() {
    return currentTime;
}
