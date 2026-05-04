#include "calculator.h"
#include <iostream>
using namespace std;

/*
    start:
    Runs calculator until user exits
*/
void Calculator::start() {

    int choice;
    int a, b;

    while (true) {

        cout << "\n--- CALCULATOR ---\n";
        cout << "1. Add\n";
        cout << "2. Subtract\n";
        cout << "3. Multiply\n";
        cout << "4. Divide\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 5) {
            cout << "[Calculator] Closing...\n";
            break;
        }

        cout << "Enter two numbers: ";
        cin >> a >> b;

        if (choice == 1)
            cout << "Result: " << add(a, b) << endl;

        else if (choice == 2)
            cout << "Result: " << subtract(a, b) << endl;

        else if (choice == 3)
            cout << "Result: " << multiply(a, b) << endl;

        else if (choice == 4)
            cout << "Result: " << divide(a, b) << endl;

        else
            cout << "Invalid choice!\n";
    }
}

/*
    basic operations
*/
int Calculator::add(int a, int b) {
    return a + b;
}

int Calculator::subtract(int a, int b) {
    return a - b;
}

int Calculator::multiply(int a, int b) {
    return a * b;
}

float Calculator::divide(int a, int b) {

    if (b == 0) {
        cout << "Error: Division by zero!\n";
        return 0;
    }

    return (float)a / b;
}
