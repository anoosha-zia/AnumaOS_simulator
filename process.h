#ifndef PROCESS_H
#define PROCESS_H

class Process {

public:

    enum State {
        READY,
        RUNNING,
        BLOCKED,
        TERMINATED
    };

    enum Type {
        SYSTEM,      // clock, scheduler tasks
        USER,        // calculator, notepad
        BACKGROUND   // copy, music simulation
    };

private:
    int pid;

    int burstTime;
    int remainingTime;

    int priority;

    // OS RESOURCE REQUIREMENTS (VERY IMPORTANT)
    int ramRequired;
    int hddRequired;

    State state;
    Type type;

public:

    Process();

    Process(int id, int bt);

    // Getters
    int getPID();
    int getBurstTime();
    int getRemainingTime();
    int getPriority();

    int getRAM();
    int getHDD();

    State getState();
    Type getType();

    // Setters
    void setPriority(int p);
    void setState(State s);
    void setType(Type t);

    void setRAM(int r);
    void setHDD(int h);

    // Core execution simulation
    void execute(int time);

    // Utility (for OS logging)
    void printInfo();
};

#endif
