#include "OS.h"
#include "process.h"
#include <iostream>
#include<unistd.h>

using namespace std;

int main() {

    OperatingSystem os;

    os.bootScreen();
    sleep(1);
    system("clear");

    int ram, hdd, cores;

    cout << "Enter RAM (GB): ";
    cin >> ram;

    cout << "Enter HDD (GB): ";
    cin >> hdd;

    cout << "Enter CPU cores: ";
    cin >> cores;
    os.setHardware(ram, hdd, cores);
    sleep(1);
    system("clear");
    os.launchClock();
    
  string cmd;

while (true) {

    cout << "\nAnumaOS> ";
    cin >> cmd;

    system("clear");
    cout << "\n[CLOCK] " << os.getClockTime() << endl;

    // ================= ALIASES =================

    if (cmd == "ls") {
        cmd = "ps";   // alias
    }
    else if (cmd == "exit") {
        cmd = "shutdown";
    }

    // ================= COMMANDS =================

    if (cmd == "ps") {
        cout << "\n[OS] Showing Process Queues...\n";
        os.printAllQueues();   // you already have printQueues()
    }

    else if (cmd == "shutdown") {
        os.shutdown();
        break;
    }

    // ================= EXEC SYSTEM =================

    else if (cmd == "exec") {

        string app;
        cin >> app;

        if (app == "calc") {
            os.launchCalculator();
        }
        else if (app == "notepad") {
            os.launchNotepad();
        }
        else {
            cout << "Unknown app\n";
        }
    }

    // ================= EXISTING COMMANDS =================

    else if (cmd == "create") {
        int id, bt, ramReq, hddReq, pr;

        cout << "PID: "; cin >> id;
        cout << "Burst Time: "; cin >> bt;
        cout << "RAM: "; cin >> ramReq;
        cout << "HDD: "; cin >> hddReq;
        cout << "Priority: "; cin >> pr;

        Process p(id, bt);
        p.setRAM(ramReq);
        p.setHDD(hddReq);
        p.setPriority(pr);

        os.createProcess(p);
    }

    else if (cmd == "run") {
        int q;
        cout << "Quantum: ";
        cin >> q;
        os.runMultilevelQueue(q);
    }
    else if (cmd == "current") {
    cout << "Current PID: " << os.getCurrentPID() << endl;
    }
    else if (cmd == "block") {
        int pid; cin >> pid;
        os.interruptBlock(pid);
    }

    else if (cmd == "resume") {
        int pid; cin >> pid;
        os.interruptResume(pid);
    }

    else if (cmd == "kill") {
        int pid; cin >> pid;
        os.interruptKill(pid);
    }

    else if (cmd == "kernel") os.enterKernelMode();
    else if (cmd == "user") os.enterUserMode();

    else {
        cout << "Unknown command. Type help.\n";
    }
}
        
    return 0;
}
