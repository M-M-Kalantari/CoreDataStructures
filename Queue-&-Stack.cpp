#include <iostream>
using namespace std;

const int SIZE = 25;

/* =========================
   Stack Implementation
   ========================= */
class Stack {
private:
    int arr[SIZE];
    int top;

public:
    Stack() : top(-1) {
    }

    // Push element to stack
    void push(int value) {
        if (top == 99) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++top] = value;
        cout << "Pushed to stack.\n";
    }

    // Pop element from stack
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow!\n";
            return;
        }
        cout << "Popped: " << arr[top--] << endl;
    }

    // Display stack
    void display() {
        if (top == -1) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack: ";
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

/* =========================
   Linear Queue Implementation
   ========================= */
class LinearQueue {
private:
    int arr[SIZE];
    int front, rear;

public:
    LinearQueue() : front(0), rear(-1) {
    }

    // Enqueue element
    void enqueue(int value) {
        if (rear == 99) {
            cout << "Queue Overflow!\n";
            return;
        }
        arr[++rear] = value;
        cout << "Enqueued to queue.\n";
    }

    // Dequeue element
    void dequeue() {
        if (front > rear) {
            cout << "Queue Underflow!\n";
            return;
        }
        cout << "Dequeued: " << arr[front++] << endl;
    }

    // Display queue
    void display() {
        if (front > rear) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue: ";
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

/* =========================
   Circular Queue Implementation
   ========================= */
class CircularQueue {
private:
    int arr[SIZE];
    int front, rear, count;

public:
    CircularQueue() : front(0), rear(-1), count(0) {
    }

    // Enqueue element
    void enqueue(int value) {
        if (count == SIZE) {
            cout << "Queue Overflow!\n";
            return;
        }
        rear = (rear + 1) % SIZE;
        arr[rear] = value;
        count++;
        cout << "Enqueued to queue.\n";
    }

    // Dequeue element
    void dequeue() {
        if (count == 0) {
            cout << "Queue Underflow!\n";
            return;
        }
        cout << "Dequeued: " << arr[front] << endl;
        front = (front + 1) % SIZE;
        count--;
    }

    // Display queue
    void display() {
        if (count == 0) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue: ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % SIZE] << " ";
        }
        cout << endl;
    }
};

/* =========================
   Main Program (Interactive)
   ========================= */
int main() {
    Stack stack;
    LinearQueue linear_queue;
    CircularQueue circular_queue;
    int choice, value;

    while (true) {
        cout << "\n====== Menu ======\n";
        cout << "\n--- Stack ---\n";
        cout << "1. Push to Stack\n";
        cout << "2. Pop from Stack\n";
        cout << "3. Display Stack\n";
        cout << "\n--- Linear Queue ---\n";
        cout << "4. Enqueue to Queue\n";
        cout << "5. Dequeue from Queue\n";
        cout << "6. Display Queue\n";
        cout << "\n--- Circular Queue ---\n";
        cout << "7. Enqueue to Circular Queue\n";
        cout << "8. Dequeue from Circular Queue\n";
        cout << "9. Display Circular Queue\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                stack.push(value);
                break;

            case 2:
                stack.pop();
                break;

            case 3:
                stack.display();
                break;

            case 4:
                cout << "Enter value: ";
                cin >> value;
                linear_queue.enqueue(value);
                break;

            case 5:
                linear_queue.dequeue();
                break;

            case 6:
                linear_queue.display();
                break;

            case 7:
                cout << "Enter value: ";
                cin >> value;
                circular_queue.enqueue(value);
                break;

            case 8:
                circular_queue.dequeue();
                break;

            case 9:
                circular_queue.display();
                break;

            case 0:
                cout << "Goodbye!\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
