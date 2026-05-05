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
g++ -I. -I./tasks *.cpp tasks/*.cpp -o main
Compile tasks separately:

g++ tasks/calculator.cpp -o calculator
##🛠️ Technologies Used
C++
Linux System Calls
POSIX Threads
Terminal-based UI
##👨‍🎓 Academic Purpose

This project was developed as part of an Operating Systems Lab course to demonstrate understanding of OS-level concepts through simulation.

##Command Categories

The shell supports the following categories of commands:

##🧠 A. System Commands
🔹 Show Help
help

Displays all available commands.

🔹 Shutdown System
shutdown

Safely terminates OS execution and clears resources.

🔹 Mode Switching
kernel

Enables kernel mode.

user

Switches back to user mode.

🔹 Clock View
clock

Displays current system time.

##⚙️ B. Process Management Commands
🔹 Create Process
create

Then user enters:

PID
Burst Time
RAM requirement
HDD requirement
Priority

Example:

AnumaOS> create
PID: 1
Burst Time: 5
RAM: 2
HDD: 10
Priority: 1
🔹 Run Scheduler (MLQ)
run

Then input:

Quantum: 2

Executes Multilevel Queue Scheduling:

High Queue → FCFS
Medium Queue → Round Robin
Low Queue → Priority Scheduling
exec notepad
