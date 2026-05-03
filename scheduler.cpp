#include <iostream>
#include "scheduler.h"
using namespace std;

Scheduler::Scheduler() {
    count = 0;
}

void Scheduler::addProcess(Process p) {
    processes[count++] = p;
}

void Scheduler::runFCFS() {
    cout << "Running FCFS Scheduling:\n";

    for (int i = 0; i < count; i++) {
        cout << "Process " << processes[i].getPID() << " executing...\n";

        while (processes[i].getRemainingTime() > 0) {
            processes[i].execute(1);
        }
        cout << "Process " << processes[i].getPID() << " finished.\n";
    }
}
void Scheduler::runRoundRobin(int quantum) {
    cout << "\nRunning Round Robin Scheduling:\n";

    bool done = false;

    while (!done) {
        done = true;

        for (int i = 0; i < count; i++) {
            if (processes[i].getRemainingTime() > 0) {
                done = false;

                cout << "Process " << processes[i].getPID()
                     << " executing for " << quantum << " units\n";

                processes[i].execute(quantum);

                if (processes[i].getRemainingTime() == 0) {
                    cout << "Process " << processes[i].getPID() << " finished\n";
                }
            }
        }
    }
}
void Scheduler::runPriorityScheduling() {
    cout << "\nPriority Scheduling:\n";

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (processes[j].getPriority() < processes[i].getPriority()) {
                swap(processes[i], processes[j]);
            }
        }
    }

    for (int i = 0; i < count; i++) {
        cout << "Process " << processes[i].getPID() << " running\n";

        while (processes[i].getRemainingTime() > 0) {
            processes[i].execute(1);
        }
    }
}
