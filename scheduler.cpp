#include "scheduler.h"
#include <iostream>
using namespace std;

/*
    Constructor:
    Initializes all queues
*/
Scheduler::Scheduler() {

    highCount = 0;
    midCount = 0;
    lowCount = 0;
}

/*
    swap:
    Helper for priority sorting
*/
void Scheduler::swap(Process &a, Process &b) {
    Process temp = a;
    a = b;
    b = temp;
}

/*
    addProcess:
    Routes process into correct queue based on type
*/
void Scheduler::addProcess(Process p) {

    if (p.getType() == Process::SYSTEM) {

        if (highCount < 50) {
            highQueue[highCount++] = p;
            cout << "[Scheduler] Added to HIGH queue (SYSTEM)\n";
        }

    } 
    else if (p.getType() == Process::USER) {

        if (midCount < 50) {
            midQueue[midCount++] = p;
            cout << "[Scheduler] Added to MEDIUM queue (USER)\n";
        }

    } 
    else {

        if (lowCount < 50) {
            lowQueue[lowCount++] = p;
            cout << "[Scheduler] Added to LOW queue (BACKGROUND)\n";
        }
    }
}

/*
    ============================
    HIGH QUEUE → FCFS
    ============================
*/
void Scheduler::executeFCFS(Process arr[], int &count) {

    for (int i = 0; i < count; i++) {

        cout << "\nContext Switch → PID " << arr[i].getPID() << endl;

        arr[i].setState(Process::RUNNING);

        while (arr[i].getRemainingTime() > 0) {
            arr[i].execute(1);
        }

        arr[i].setState(Process::TERMINATED);

        cout << "PID " << arr[i].getPID() << " completed (HIGH queue)\n";
    }
}

/*
    ============================
    MEDIUM QUEUE → ROUND ROBIN
    ============================
*/
void Scheduler::executeRoundRobin(Process arr[], int &count, int quantum) {

    bool done = false;

    while (!done) {

        done = true;

        for (int i = 0; i < count; i++) {

            if (arr[i].getRemainingTime() > 0) {

                cout << "\nContext Switch → PID " << arr[i].getPID() << endl;

                arr[i].setState(Process::RUNNING);

                arr[i].execute(quantum);

                if (arr[i].getRemainingTime() > 0)
                    arr[i].setState(Process::READY);
                else
                    arr[i].setState(Process::TERMINATED);

                done = false;
            }
        }
    }
}

/*
    ============================
    LOW QUEUE → PRIORITY
    ============================
*/
void Scheduler::executePriority(Process arr[], int &count) {

    // sort by priority
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            if (arr[j].getPriority() > arr[j + 1].getPriority()) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    for (int i = 0; i < count; i++) {

        cout << "\nContext Switch → PID " << arr[i].getPID() << endl;

        arr[i].setState(Process::RUNNING);

        while (arr[i].getRemainingTime() > 0) {
            arr[i].execute(1);
        }

        arr[i].setState(Process::TERMINATED);

        cout << "PID " << arr[i].getPID() << " completed (LOW queue)\n";
    }
}

/*
    MAIN MLQ SCHEDULER
*/
void Scheduler::runMultilevelQueue(int quantum) {

    cout << "\n==============================\n";
    cout << " MULTILEVEL QUEUE STARTED\n";
    cout << "==============================\n";

    // 1. HIGH PRIORITY (SYSTEM)
    if (highCount > 0) {
        cout << "\n--- HIGH QUEUE (FCFS) ---\n";
        executeFCFS(highQueue, highCount);
    }

    // 2. MEDIUM PRIORITY (USER)
    if (midCount > 0) {
        cout << "\n--- MEDIUM QUEUE (ROUND ROBIN) ---\n";
        executeRoundRobin(midQueue, midCount, quantum);
    }

    // 3. LOW PRIORITY (BACKGROUND)
    if (lowCount > 0) {
        cout << "\n--- LOW QUEUE (PRIORITY) ---\n";
        executePriority(lowQueue, lowCount);
    }

    cout << "\n==============================\n";
    cout << " ALL QUEUES COMPLETED\n";
    cout << "==============================\n";
}

/*
    Debug function
*/
void Scheduler::printQueues() {

    cout << "\n--- HIGH QUEUE ---\n";
    for (int i = 0; i < highCount; i++)
        highQueue[i].printInfo();

    cout << "\n--- MEDIUM QUEUE ---\n";
    for (int i = 0; i < midCount; i++)
        midQueue[i].printInfo();

    cout << "\n--- LOW QUEUE ---\n";
    for (int i = 0; i < lowCount; i++)
        lowQueue[i].printInfo();
}
void Scheduler::blockProcess(int pid) {
    bool found=false;
    for (int i = 0; i < highCount; i++) {
        if (highQueue[i].getPID() == pid) {
            highQueue[i].block();
            cout << "[INTERRUPT] PID " << pid << " BLOCKED (HIGH)\n";
             found = true;
            return;
        }
    }

    for (int i = 0; i < midCount; i++) {
        if (midQueue[i].getPID() == pid) {
            midQueue[i].block();
            cout << "[INTERRUPT] PID " << pid << " BLOCKED (MEDIUM)\n";
             found = true;
            return;
        }
    }

    for (int i = 0; i < lowCount; i++) {
        if (lowQueue[i].getPID() == pid) {
            lowQueue[i].block();
            cout << "[INTERRUPT] PID " << pid << " BLOCKED (LOW)\n";
             found = true;
            return;
        }
    }
    if (!found) {
        cout << "[INTERRUPT] ERROR: PID " << pid << " NOT FOUND\n";
    }
}
//resume a process
void Scheduler::resumeProcess(int pid) {
    bool found = false;
    for (int i = 0; i < highCount; i++) {
        if (highQueue[i].getPID() == pid) {
            highQueue[i].unblock();
            cout << "[INTERRUPT] PID " << pid << " RESUMED (HIGH)\n";
            found = true;
            return;
        }
    }

    for (int i = 0; i < midCount; i++) {
        if (midQueue[i].getPID() == pid) {
            midQueue[i].unblock();
            cout << "[INTERRUPT] PID " << pid << " RESUMED (MEDIUM)\n";
            found=true;
            return;
        }
    }

    for (int i = 0; i < lowCount; i++) {
        if (lowQueue[i].getPID() == pid) {
            lowQueue[i].unblock();
            cout << "[INTERRUPT] PID " << pid << " RESUMED (LOW)\n";
            found=true;
            return;
        }
    }
    if (!found) {
        cout << "[INTERRUPT] ERROR: PID " << pid << " NOT FOUND\n";
    }
}
//kill a process
void Scheduler::killProcess(int pid) {

    bool found = false;

    for (int i = 0; i < highCount; i++) {
        if (highQueue[i].getPID() == pid) {

            highQueue[i].kill();
            cout << "[INTERRUPT] PID " << pid << " KILLED (HIGH)\n";

            found = true;
            return;
        }
    }

    for (int i = 0; i < midCount && !found; i++) {
        if (midQueue[i].getPID() == pid) {

            midQueue[i].kill();
            cout << "[INTERRUPT] PID " << pid << " KILLED (MEDIUM)\n";

            found = true;
            return;
        }
    }

    for (int i = 0; i < lowCount && !found; i++) {
        if (lowQueue[i].getPID() == pid) {

            lowQueue[i].kill();
            cout << "[INTERRUPT] PID " << pid << " KILLED (LOW)\n";

            found = true;
            return;
        }
    }

    if (!found) {
        cout << "[INTERRUPT] ERROR: PID " << pid << " NOT FOUND\n";
    }
}
