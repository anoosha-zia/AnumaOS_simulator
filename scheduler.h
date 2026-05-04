#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

class Scheduler {

private:
    Process highQueue[50];     // SYSTEM (FCFS)
    Process midQueue[50];      // USER (Round Robin)
    Process lowQueue[50];      // BACKGROUND (Priority)

    int highCount;
    int midCount;
    int lowCount;
    //interrupt helpers
    Process blockedQueue[50];
    int blockedCount = 0;

    // helper for swapping (priority scheduling)
    void swap(Process &a, Process &b);
    //Helper Scheduling algorithms
    void executeFCFS(Process arr[], int count);
void executeRoundRobin(Process arr[], int count, int quantum);
void executePriority(Process arr[], int count);
public:

    Scheduler();

    // process management
   void addProcess(Process p);
    // debugging
    void printQueue();
    //MLQ implementation
    void runMultilevelQueue(int quantum);
    //print queues
    void printQueues();
    //interrupts
    void blockProcess(int pid);
    void resumeProcess(int pid);
    void killProcess(int pid);
};

#endif
