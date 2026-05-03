#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

class Scheduler {
private:
    Process processes[10];
    int count;

public:
    Scheduler();

    void addProcess(Process p);
    void runFCFS();
    void runRoundRobin(int quantum);
    void runPriorityScheduling();
};

#endif
