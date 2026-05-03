#include<iostream>
#include<unistd.h>
#include "scheduler.h"

using namespace std;

// System variables (later you can move these to a System class)
int totalRAM, usedRAM = 0;
int totalHDD, usedHDD = 0;
int cpuCores;

// Boot screen
void bootOS(){
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
        sleep(1);
    }

    cout << "\n\n<><><><><><><><><><>       System Ready!        <><><><><><><>\n";
    sleep(1);
}

// Take hardware input
void initializeSystem(){
    cout << "Enter Total RAM (MB): ";
    cin >> totalRAM;

    cout << "Enter Hard Disk Size (GB): ";
    cin >> totalHDD;

    cout << "Enter Number of CPU Cores: ";
    cin >> cpuCores;
}

// Display system info
void showSystemInfo(){
    cout << "\n<><><><> SYSTEM INFO <><><><>\n";
    cout << "Total RAM: " << totalRAM << " MB\n";
    cout << "Used RAM: " << usedRAM << " MB\n";
    cout << "Total HDD: " << totalHDD << " GB\n";
    cout << "Used HDD: " << usedHDD << " GB\n";
    cout << "CPU Cores: " << cpuCores << endl;
}

// Process simulation function
void runProcessSimulation() {
    Scheduler scheduler;

    // Sample processes (later: take input)
    scheduler.addProcess(Process(1, 5));
    scheduler.addProcess(Process(2, 3));
    scheduler.addProcess(Process(3, 4));

    scheduler.runFCFS();
    scheduler.runRoundRobin(2);
}

// Main menu
void menu(){
    int choice;
 cout << "\n<><><><> AnumaOS MENU <><><><>\n";
        cout << "1. System Info\n";
        cout << "2. Run Process Scheduler\n";
        cout << "3. Running Processes (Coming Soon)\n";
        cout << "4. Kernel Mode (Coming Soon)\n";
        cout << "5. Shutdown\n";
    do{
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                showSystemInfo();
                break;

            case 2:
                runProcessSimulation();   //
                break;

            case 5:
                cout << "\nShutting down AnumaOS...\n";
                sleep(1);
                break;

            default:
                cout << "Feature not implemented yet.\n";
        }

    } while(choice != 5);
}

int main(){
    initializeSystem();
    bootOS();
    menu();
    return 0;
}
