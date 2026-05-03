#include "scheduler.h"
#include "process.h"

class OperatingSystem {

private:

    int totalRAM, totalHDD, totalCores;
    int usedRAM, usedHDD;

    bool kernelMode;

    Scheduler scheduler;  

public:
    OperatingSystem();

    void bootScreen();
    void setHardware(int ram, int hdd, int cores);

    void enterKernelMode();
    void enterUserMode();
    bool isKernelMode();

    bool checkResources(int ram, int hdd);
    void allocateResources(int ram, int hdd);
    void freeResources(int ram, int hdd);

    // CORE INTEGRATION FUNCTION
    void createProcess(Process p);
    void runMultilevelQueue(int quantum);
    void shutdown();
};
