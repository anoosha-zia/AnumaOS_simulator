#include "process.h"
#include<iostream>
using namespace std;
Process::Process() {
    pid = 0;
    burstTime = 0;
    remainingTime = 0;
    state=READY
}

Process::Process(int id, int bt) {
    pid = id;
    burstTime = bt;
    remainingTime = bt;
}

int Process::getPID() {
    return pid;
}

int Process::getBurstTime() {
    return burstTime;
}

int Process::getRemainingTime() {
    return remainingTime;
}

void Process::execute(int time) {
    state = RUNNING;

    if (remainingTime > time)
        remainingTime -= time;
    else
        remainingTime = 0;

    if (remainingTime == 0)
        state = TERMINATED;
    else
        state = READY;
}
int Process::getPriority() {
    return priority;
}

void Process::setPriority(int p) {
    priority = p;
}
void Process::setState(State s) {
    state = s;
}

Process::State Process::getState() {
    return state;
}
