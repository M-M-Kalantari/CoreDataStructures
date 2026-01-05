#include <iostream>
#include <string>
using namespace std;

// ------------------------------
// Global Variables and Array
// ------------------------------

// Static array of fixed size 15
int staticArray[15];

// Pointer for dynamically allocated array
int *dynamicArray;

// Size of the dynamic array (user-defined)
int arraySize = 0;

// ------------------------------
// Struct Example
// ------------------------------
struct Student {
    string name;
    int age;
};

// ------------------------------
// Function: Pointer vs Variable
// Demonstrates how pointers and variables work
// ------------------------------
void Pointer_vs_Variable() {
    cout << "\n/*/ Pointer vs Variable\n";

    int x = 2584;
    int *p = &x; // Pointer pointing to x

    cout << "Variable = " << x << " or " << *p << endl; // Dereferencing pointer
    cout << "Pointer = " << p << " or " << &x << endl;  // Pointer address
}

// ------------------------------
// Function: create_DynamicArray
// Prompts user to create a dynamic array of integers
// ------------------------------
void create_DynamicArray() {
    cout << "\n/*/ Creating dynamic array...\n";

    cout << "Enter array size: ";
    cin >> arraySize;

    // Allocate memory dynamically
    dynamicArray = new int[arraySize];

    // Fill the array with user input
    for (int i = 0; i < arraySize; i++) {
        cout << "Element " << i << ": ";
        cin >> dynamicArray[i];
    }

    cout << "Dynamic array created successfully.\n";
}

// ------------------------------
// Function: print_DynamicArray
// Prints all elements of the dynamic array
// ------------------------------
void print_DynamicArray() {
    cout << "\n/*/ Printing dynamic array...\n";

    if (dynamicArray == nullptr) {
        cout << "Error: The array is not created. Please create it first.\n";
        create_DynamicArray(); // If not created, create it first
    }

    // Use a pointer to traverse the array
    int *p = &dynamicArray[0];
    for (int i = 0; i < arraySize; i++) {
        cout << "Element " << i << ": " << *p << endl;
        p++;
    }

    cout << "Dynamic array printed successfully.\n";
}

// ------------------------------
// Function: calculations_DynamicArray
// Calculates average, maximum, and minimum of the dynamic array
// ------------------------------
void calculations_DynamicArray() {
    cout << "\n/*/ Calculating dynamic array...\n";

    if (dynamicArray == nullptr) {
        cout << "Error: The array is not created. Please create it first.\n";
        create_DynamicArray();
    }

    int *p = &dynamicArray[0];
    int sum = 0;
    int max = 0;
    int min = 0;

    // Loop through the array to compute sum, max, and min
    for (int i = 0; i < arraySize; i++) {
        sum += *p;

        if (i == 0) {
            max = *p;
            min = *p;
        } else {
            if (*p > max) max = *p;
            if (*p < min) min = *p;
        }

        p++;
    }

    cout << "Average = " << sum / arraySize << endl;
    cout << "Maximum = " << max << endl;
    cout << "Minimum = " << min << endl;

    cout << "Dynamic array calculated successfully.\n";
}

// ------------------------------
// Function: reverse_DynamicArray
// Reverses the dynamic array in-place
// ------------------------------
void reverse_DynamicArray() {
    cout << "\n/*/ Reversing dynamic array...\n";

    if (dynamicArray == nullptr) {
        cout << "Error: The array is not created. Please create it first.\n";
        create_DynamicArray();
    }

    // Print original array
    int *p = &dynamicArray[0];
    cout << "Original array: ";
    for (int i = 0; i < arraySize; i++) {
        cout << "[" << *p << "]";
        p++;
    }
    cout << endl;

    // Reverse the array using two pointers
    int *start = dynamicArray;
    int *end = dynamicArray + arraySize - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }

    // Print reversed array
    p = &dynamicArray[0];
    cout << "Reversed array: ";
    for (int i = 0; i < arraySize; i++) {
        cout << "[" << *p << "]";
        p++;
    }
    cout << endl;

    cout << "Dynamic array reversed successfully.\n";
}

// ------------------------------
// Function: free_Memory
// Frees the dynamically allocated memory
// ------------------------------
void free_Memory() {
    if (dynamicArray != nullptr) {
        delete[] dynamicArray;
        dynamicArray = nullptr;
        cout << "Memory freed.\n";
    } else {
        cout << "No memory allocated.\n";
    }
}

// ------------------------------
// Function: Pointer_Struct
// Demonstrates pointer usage with a struct
// ------------------------------
void Pointer_Struct() {
    cout << "\n/*/ Pointer Struct\n";

    Student s;
    Student* p = &s; // Pointer to struct

    // Input student details
    cout << "Enter student name: ";
    cin >> p->name;

    cout << "Enter student age: ";
    cin >> p->age;

    // Output student details
    cout << "\nStudent info:\n";
    cout << "Name: " << p->name << "\n";
    cout << "Age: " << p->age << "\n";
}

// ------------------------------
// Main Function: Menu-driven program
// ------------------------------
int main() {
    while (true) {
        cout << "\n\n----- Pointer -----\n";
        cout << "1) Pointer vs Variable\n";
        cout << "2) Create dynamic array\n";
        cout << "3) Print dynamic array\n";
        cout << "4) Reverse dynamic array\n";
        cout << "5) Average - Maximum - Minimum\n";
        cout << "6) Free memory\n";
        cout << "7) Pointer to Struct\n";
        cout << "0) Exit\n";
        cout << "-----------------------\n";
        cout << "Enter your choice:\t";

        int choice;
        cin >> choice;

        if (choice == 0) {
            free_Memory(); // Ensure memory is freed before exit
            cout << "\nExiting program...\n";
            break;
        }

        switch (choice) {
            case 1:
                Pointer_vs_Variable();
                break;

            case 2:
                create_DynamicArray();
                break;

            case 3:
                print_DynamicArray();
                break;

            case 4:
                reverse_DynamicArray();
                break;

            case 5:
                calculations_DynamicArray();
                break;

            case 6:
                free_Memory();
                break;

            case 7:
                Pointer_Struct();
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}