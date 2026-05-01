##AnumaOS – Operating System Simulator
👨‍💻 Project Overview

AnumaOS is a terminal-based operating system simulator developed in C++.
It demonstrates core operating system concepts including process management, scheduling, resource allocation, and multitasking using Linux system calls.

##⚙️ Features
->Boot sequence simulation with animated loading screen
->System resource initialization (RAM, HDD, CPU cores)
->Process Control Block (PCB) implementation
->Process creation using fork() and exec()
->Round Robin scheduling algorithm
->Multilevel queue scheduling (basic implementation)
->Memory (RAM/HDD) management simulation
->Kernel mode for process control (kill/terminate processes)
->Basic system utilities (calculator, clock, notepad, etc.)
->Terminal-based multitasking simulation
##🧠 OS Concepts Implemented
->Process Management
->Scheduling (Round Robin, Multilevel Queue)
->Context Switching
->Resource Allocation
->User Mode vs Kernel Mode
->Process Creation (fork/exec)
->Inter-process Communication (basic simulation)
->Synchronization (mutex/semaphore basics)
##🗂️ Project Structure
OS_Project/
│── main.cpp
│── pcb.h / pcb.cpp
│── scheduler.h / scheduler.cpp
│── resource_manager.cpp
│── kernel.cpp
│── tasks/
│     ├── calculator.cpp
│     ├── clock.cpp
│     ├── notepad.cpp
│     ├── file_ops.cpp
│     └── ...
##🚀 How to Run
g++ main.cpp -o os -pthread
./os

Compile tasks separately:

g++ tasks/calculator.cpp -o calculator
##🛠️ Technologies Used
C++
Linux System Calls
POSIX Threads
Terminal-based UI
##👨‍🎓 Academic Purpose

This project was developed as part of an Operating Systems Lab course to demonstrate understanding of OS-level concepts through simulation.
