#include "process.h"
#include <iostream>
#include "calculator.h"
#include "notepad.h"
using namespace std;

/*
    Default constructor:
    Initializes safe default process values.
*/
Process::Process() {
    pid = 0;
    hasExecuted=false;
    burstTime = 0;
    remainingTime = 0;

    priority = 1;

    ramRequired = 0;
    hddRequired = 0;

    state = READY;
    type = USER;
}

/*
    Parameterized constructor:
    Creates process with execution time.
*/
Process::Process(int id, int bt) {
    pid = id;
    burstTime = bt;
    remainingTime = bt;

    priority = 1;

    ramRequired = 0;
    hddRequired = 0;

    state = READY;
    type = USER;
}
bool Process::isExecuted() {
    return hasExecuted;
}

void Process::markExecuted() {
    hasExecuted = true;
}
/*
    execute:
    Simulates CPU execution for given time slice.
    This is used by Scheduler (Round Robin etc.)
*/
void Process::execute(int time) {

    state = RUNNING;

    if (remainingTime > time)
        remainingTime -= time;
    else
        remainingTime = 0;

    // If finished → terminate
    if (remainingTime == 0)
        state = TERMINATED;
    else
        state = READY;
}

/*
    printInfo:
    Debug function for OS logs
*/
void Process::printInfo() {
    cout << "PID: " << pid
         << " | Burst: " << burstTime
         << " | Remaining: " << remainingTime
         << " | Priority: " << priority
         << endl;
}

/*
    Getters
*/
int Process::getPID() { return pid; }
int Process::getBurstTime() { return burstTime; }
int Process::getRemainingTime() { return remainingTime; }
int Process::getPriority() { return priority; }

int Process::getRAM() { return ramRequired; }
int Process::getHDD() { return hddRequired; }

Process::State Process::getState() { return state; }
Process::Type Process::getType() { return type; }

/*
    Setters
*/
void Process::setPriority(int p) { priority = p; }
void Process::setState(State s) { state = s; }
void Process::setType(Type t) { type = t; }

void Process::setRAM(int r) { ramRequired = r; }
void Process::setHDD(int h) { hddRequired = h; }
void Process::block() {
    if (state != TERMINATED)
        state = BLOCKED;
}

void Process::unblock() {
    if (state == BLOCKED)
        state = READY;
}

void Process::kill() {
    state = TERMINATED;
    remainingTime = 0;
}
void Process::setTaskType(TaskType t) {
    taskType = t;
}

Process::TaskType Process::getTaskType() {
    return taskType;
}


void Process::executeTask() {

    if (taskType == CALCULATOR) {

        Calculator c;
        c.start();
    }

    else if (taskType == NOTEPAD) {

    Notepad np("file.txt");

    np.start();  
}

}
