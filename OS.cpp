#include "OS.h"
#include"notepad.h"
#include <iostream>
#include <thread>
#include <chrono>
#include<string>

using namespace std;

/*
    Constructor:
    Initializes OS name and resets system state.
*/
OperatingSystem::OperatingSystem() {
  

    totalRAM = 0;
    totalHDD = 0;
    totalCores = 0;

    usedRAM = 0;
    usedHDD = 0;

    kernelMode = false;
}

/*
    bootScreen:
    Custom boot screen (your design preserved)
*/
void OperatingSystem::bootScreen() {

    system("clear");

    cout<<"        ██████   ███    ██  ██   ██  ███    ███   ██████"<<endl;
    cout<<"       ██    ██  ██ █   ██  ██   ██  ██ █  █ ██  ██    ██"<<endl;
    cout<<"       ██ ██ ██  ██  █  ██  ██   ██  ██  ██  ██  ██ ██ ██"<<endl;
    cout<<"       ██    ██  ██   █ ██  ██   ██  ██      ██  ██    ██"<<endl;
    cout<<"       ██    ██  ██    ███   █████   ██      ██  ██    ██"<<endl;

    cout<<"\n<><><><><><><><><><>    AnumaOS Booting     <><><><><><><><><>";
    cout << endl;

    cout<< "\n<><><><><><><><><><>      Loading...      <><><><><><><>"<<endl;

    for(int i = 0; i < 7; i++){
        cout << "      o";
        cout.flush();

        // using chrono instead of sleep()
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "\n\n<><><><><><><><><><>       System Ready!        <><><><><><><>\n";

    this_thread::sleep_for(chrono::seconds(1));
}

/*
    setHardware:
    Initializes system hardware limits.
*/
void OperatingSystem::setHardware(int ram, int hdd, int cores) {

    totalRAM = ram;
    totalHDD = hdd;
    totalCores = cores;

    cout << "\n[OS] Hardware Initialized:\n";
    cout << "RAM: " << totalRAM << " GB\n";
    cout << "HDD: " << totalHDD << " GB\n";
    cout << "CPU Cores: " << totalCores << "\n\n";
}

/*
    Kernel Mode ON
*/
void OperatingSystem::enterKernelMode() {
    kernelMode = true;
    cout << "[KERNEL MODE ENABLED]\n";
}

/*
    User Mode ON
*/
void OperatingSystem::enterUserMode() {
    kernelMode = false;
    cout << "[USER MODE ENABLED]\n";
}

bool OperatingSystem::isKernelMode() {
    return kernelMode;
}

/*
    Resource Check
*/
bool OperatingSystem::checkResources(int ram, int hdd) {
    return (usedRAM + ram <= totalRAM &&
            usedHDD + hdd <= totalHDD);
}

/*
    Allocate Resources
*/
void OperatingSystem::allocateResources(int ram, int hdd) {
    usedRAM += ram;
    usedHDD += hdd;
}

/*
    Free Resources
*/
void OperatingSystem::freeResources(int ram, int hdd) {
    usedRAM -= ram;
    usedHDD -= hdd;
}

/*
    createProcess:
    FULL integration with scheduler
*/
void OperatingSystem::createProcess(Process p) {
//this should be done in kernel mode only
     if (!kernelMode) {
        cout << "[ERROR] Kernel mode required to create process\n";
        return;
    }

    cout << "\n[OS] Creating Process PID: " << p.getPID() << endl;

    // 1. Check resources
    if (!checkResources(p.getRAM(), p.getHDD())) {
        cout << "[OS] Not enough resources. Process rejected.\n";
        return;
    }

    // 2. Allocate resources
    allocateResources(p.getRAM(), p.getHDD());

    // 3. Add to scheduler (READY QUEUE)
    scheduler.addProcess(p);

    cout << "[OS] Process added to Ready Queue\n";
}

/*
    Scheduler Controls
*/

void OperatingSystem::runMultilevelQueue(int quantum) {
     if (!kernelMode) {
        cout << "[ERROR] Kernel mode required to run scheduler\n";
        return;
    }
    //run → scheduler starts → shell continues immediately
    cout << "[OS] Starting Scheduler in background...\n";

    thread schedulerThread(&Scheduler::runMultilevelQueue, &scheduler, quantum);
    schedulerThread.detach();
}
/*
    shutdown:
    Terminates OS and clears all resources.
*/
void OperatingSystem::shutdown() {

    cout << "\n[OS] Shutting down...\n";

    cout << "[OS] Terminating all processes...\n";

    usedRAM = 0;
    usedHDD = 0;

    cout << "[OS] System safely powered off.\n";
}
//interrupt functionalities
void OperatingSystem::interruptBlock(int pid) {
    scheduler.blockProcess(pid);
}

void OperatingSystem::interruptResume(int pid) {
    scheduler.resumeProcess(pid);
}

void OperatingSystem::interruptKill(int pid) {
    scheduler.killProcess(pid);
}

//tasks


      void OperatingSystem::launchNotepad() {

    cout << "\n[OS] Creating Notepad Process...\n";

    if (!checkResources(1, 1)) {
        cout << "[OS] Not enough resources!\n";
        return;
    }

    Process p(rand() % 1000 + 1, 7);
    p.setTaskType(Process::NOTEPAD);
    p.setPriority(2);

    allocateResources(1, 1);
    scheduler.addProcess(p);

    cout << "[OS] Notepad Process added to Ready Queue\n";
    scheduler.runMultilevelQueue(2);   
}
void OperatingSystem::launchCalculator() {

    if (!checkResources(1, 1)) {
        cout << "Not enough resources\n";
        return;
    }

    Process p(rand() % 1000 + 1, 5);
    p.setTaskType(Process::CALCULATOR);

    allocateResources(1, 1);
    scheduler.addProcess(p);

    cout << "[OS] Calculator Process created\n";
    scheduler.runMultilevelQueue(2);   
}
void OperatingSystem::launchClock() {

    thread t(&Clock::start, &clock);
    t.detach();

    cout << "[AnumaOS] Clock started in background\n";
}
string OperatingSystem::getClockTime() {
    return clock.getTime();
}
void OperatingSystem::printAllQueues(){
scheduler.printQueues();
}
int OperatingSystem::getCurrentPID() {
    return scheduler.getCurrentPID();
}
