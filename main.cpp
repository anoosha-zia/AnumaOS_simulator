#include "OS.h"
#include "process.h"
#include <iostream>

using namespace std;

int main() {

    OperatingSystem os;

    os.bootScreen();

    int ram, hdd, cores;

    cout << "Enter RAM (GB): ";
    cin >> ram;

    cout << "Enter HDD (GB): ";
    cin >> hdd;

    cout << "Enter CPU cores: ";
    cin >> cores;

    os.setHardware(ram, hdd, cores);

    int choice;
 cout << "\n========== OS MENU ==========\n";
        cout << "1. Create Process\n";
        cout << "2. Kernel Mode ON\n";
        cout << "3. User Mode ON\n";
        cout << "4. Run MLQ(Multi Level Queue)\n";
        cout << "7. Shutdown OS\n";
        cout << "=============================\n";
    while (true) {
        cout << "Enter choice: ";
        cin >> choice;

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

        else if (choice == 7) {
            os.shutdown();
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
