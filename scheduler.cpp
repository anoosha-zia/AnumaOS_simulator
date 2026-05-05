#include "scheduler.h"
#include <iostream>
#include<thread>
using namespace std;

/*
    Constructor:
    Initializes all queues
*/
Scheduler::Scheduler() {

    highCount = 0;
    midCount = 0;
    lowCount = 0;
    currentProcess=nullptr;
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
void Scheduler::executeFCFS(Process queue[], int count) {
  
    for (int i = 0; i < count; i++) {
    currentProcess=&queue[i];
        cout << "\nContext Switch → PID " << queue[i].getPID() << endl;

        // Run until process finishes
        while (queue[i].getRemainingTime() > 0) {

            // Skip blocked or killed processes
            if (queue[i].getState() == Process::BLOCKED ||
                queue[i].getState() == Process::TERMINATED) {
                break;
            }

            queue[i].setState(Process::RUNNING);

            //  Run using thread (1 unit for FCFS simulation)
            thread t(&Process::execute, &queue[i], 1);
            t.join();

            // If still not finished → go back to READY
            if (queue[i].getState() != Process::TERMINATED) {
                queue[i].setState(Process::READY);
            }
        }

        // Final state
        if (queue[i].getState() != Process::TERMINATED) {
            queue[i].setState(Process::TERMINATED);
        }

        cout << "PID " << queue[i].getPID() << " completed.\n";
    }
}

/*
    ============================
    MEDIUM QUEUE → ROUND ROBIN
    ============================
*/
void Scheduler::executeRoundRobin(Process queue[], int count, int quantum) {

    bool done = false;

    while (!done) {

        done = true;

        for (int i = 0; i < count; i++) {
            currentProcess=&queue[i];
            // Skip finished processes
            if (queue[i].getRemainingTime() <= 0)
                continue;

            // Skip blocked processes
            if (queue[i].getState() == Process::BLOCKED)
                continue;

            cout << "\nContext Switch → PID " << queue[i].getPID() << endl;

            queue[i].setState(Process::RUNNING);

            // Run process using thread with time slice
            thread t(&Process::execute, &queue[i], quantum);
            t.join();

            // Update state after execution
            if (queue[i].getState() != Process::TERMINATED) {
                queue[i].setState(Process::READY);
                done = false;  // still work remaining
            }
        }
    }
}

/*
    ============================
    LOW QUEUE → PRIORITY
    ============================
*/
void Scheduler::executePriority(Process queue[], int count) {

    // (Optional) If you have priority values, sort first
    // You already have swap() — you can use it here if needed

    for (int i = 0; i < count; i++) {
        currentProcess=&queue[i];
        cout << "\nContext Switch → PID " << queue[i].getPID() << endl;

        // Run until process finishes
        while (queue[i].getRemainingTime() > 0) {

            // Skip blocked or terminated processes
            if (queue[i].getState() == Process::BLOCKED ||
                queue[i].getState() == Process::TERMINATED) {
                break;
            }

            queue[i].setState(Process::RUNNING);

            //  Thread-based execution (like FCFS)
            thread t(&Process::execute, &queue[i], 1);
            t.join();

            // If still running → back to READY
            if (queue[i].getState() != Process::TERMINATED) {
                queue[i].setState(Process::READY);
            }
        }

        // Final state safety
        if (queue[i].getState() != Process::TERMINATED) {
            queue[i].setState(Process::TERMINATED);
        }

        cout << "PID " << queue[i].getPID() << " completed.\n";
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
int Scheduler::getCurrentPID() {

    if (currentProcess != nullptr &&
        currentProcess->getState() != Process::TERMINATED) {
        return currentProcess->getPID();
    }

    return -1; // no process running
}
