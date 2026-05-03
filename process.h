#ifndef PROCESS_H
#define PROCESS_H
enum State { READY, RUNNING, WAITING, TERMINATED };
class Process {
private:
    int pid;
    int burstTime;
    int remainingTime;
    int priority;
    State state;
public:
    Process();
    Process(int id, int bt);

    int getPID();
    int getBurstTime();
    int getRemainingTime();
    int getPriority();
    void setPriority(int p);
    void setState(State s);
    State getState();
    //let the program execute if remaining time is less than the time given
    void execute(int time);
};

#endif
