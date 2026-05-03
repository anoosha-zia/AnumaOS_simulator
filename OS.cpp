#include "OS.h"
#include"tasks/notepad.h"
#include <iostream>
#include <thread>
#include <chrono>

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

    cout << "\n[OS] Launching Multilevel Queue Scheduler...\n";

    scheduler.runMultilevelQueue(quantum);
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
#include "tasks/Notepad.h"   // adjust path if needed

void OperatingSystem::launchNotepad() {

    cout << "\n[OS] Launching Notepad...\n";

    // create process for notepad
    Process p(rand() % 1000 + 1, 5); // random PID, burst time

    p.setType(Process::USER);
    p.setPriority(2);
    p.setRAM(1);
    p.setHDD(1);

    // check resources
    if (!checkResources(1, 1)) {
        cout << "[OS] Not enough resources!\n";
        return;
    }

    allocateResources(1, 1);
    createProcess(p);

    // run actual app logic
    Notepad np("note.txt");

    int choice;
    string text;

    while (true) {

        cout << "\n--- NOTEPAD ---\n";
        cout << "1. Write\n2. Append\n3. View\n4. Exit\n";
        cin >> choice;

        cin.ignore();

        if (choice == 1) {
            cout << "Enter text: ";
            getline(cin, text);
            np.write(text);
        }
        else if (choice == 2) {
            cout << "Enter text: ";
            getline(cin, text);
            np.append(text);
        }
        else if (choice == 3) {
            np.view();
        }
        else {
            cout << "[OS] Closing Notepad...\n";
            freeResources(1, 1);
            break;
        }
    }
}
