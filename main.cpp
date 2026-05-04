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
    int choice;
 
    while (true) {
    cout << "\n[CLOCK] " << os.getClockTime() << endl;
    cout << "\n========== OS MENU ==========\n";
        cout << "1. Create Process\n";
        cout << "2. Kernel Mode ON\n";
        cout << "3. User Mode ON\n";
        cout << "4. Run MLQ(Multi Level Queue)\n";
        cout << "5. Block Process (Interrupt)\n";
        cout << "6. Resume Process\n";
        cout << "7. Kill Process\n";
        cout<<  "8. Launch notepad\n";
        cout<<  "9. Launch calculator\n";
        cout << "10. Shutdown OS\n";
        cout << "=============================\n";
        cout << "Enter choice: ";
        cin >> choice;
        sleep(1);
        system("clear");
        cout << "\n[CLOCK] " << os.getClockTime() << endl;
        if (choice == 1) {

            int id, bt, ramReq, hddReq, pr;

            cout << "Enter PID: ";
            cin >> id;

            cout << "Burst Time: ";
            cin >> bt;

            cout << "RAM Required: ";
            cin >> ramReq;

            cout << "HDD Required: ";
            cin >> hddReq;

            cout << "Priority: ";
            cin >> pr;

            Process p(id, bt);
            p.setRAM(ramReq);
            p.setHDD(hddReq);
            p.setPriority(pr);

            os.createProcess(p);
        }
        else if (choice == 2) {
            os.enterKernelMode();
        }

        else if (choice == 3) {
            os.enterUserMode();
        }
        else if (choice == 4) {
             int q;
            cout << "Enter Quantum for MLQ (User Queue): ";
            cin >> q;

            os.runMultilevelQueue(q);
        }
        else if (choice == 5) {
            int pid;
            cout << "Enter PID to block: ";
            cin >> pid;
            os.interruptBlock(pid);
        }

        else if (choice == 6) {
            int pid;
            cout << "Enter PID to resume: ";
            cin >> pid;
            os.interruptResume(pid);
        }

        else if (choice == 7) {
            int pid;
            cout << "Enter PID to kill: ";
            cin >> pid;
            os.interruptKill(pid);
        }
        else if (choice == 8) {
        os.launchNotepad();
        }
         else if (choice == 9) {
        os.launchCalculator();
        }
        else if (choice == 10) {
            os.shutdown();
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
