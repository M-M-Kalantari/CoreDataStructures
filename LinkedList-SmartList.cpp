#include <iostream>
#include <string>
using namespace std;

// -----------------------------
// Node class
// -----------------------------
class Node {
public:
    int data;
    Node *next;
    Node *prev;

    explicit Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// -----------------------------
// Circular Doubly Linked List
// -----------------------------
class LinkedList {
private:
    Node *start;
    Node *end;
    int size;

public:
    LinkedList() : start(nullptr), end(nullptr), size(0) {}

    // -----------------------------
    // Insert a node
    // index: 0=start, -1=end, -2=sorted, >=0=index
    // -----------------------------
    void insert(int data, int index) {
        Node *newNode = new Node(data);

        // 1) Empty list
        if (size == 0) {
            start = end = newNode;
            newNode->next = newNode->prev = newNode;
            size++;
            cout << "Inserted at index 0\n";
            return;
        }

        // 2) Insert at beginning
        if (index == 0) {
            newNode->next = start;
            newNode->prev = end;
            start->prev = newNode;
            end->next = newNode;
            start = newNode;
            size++;
            cout << "Inserted at index 0\n";
            return;
        }

        // 3) Insert at end
        if (index == -1 || index >= size) {
            newNode->prev = end;
            newNode->next = start;
            end->next = newNode;
            start->prev = newNode;
            end = newNode;
            size++;
            cout << "Inserted at index " << size - 1 << "\n";
            return;
        }

        // 4) Insert sorted
        if (index == -2) {
            Node *temp = start;
            int i = 0;
            do {
                if (data <= temp->data) break;
                temp = temp->next;
                i++;
            } while (temp != start);

            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            if (temp == start) start = newNode;

            size++;
            cout << "Inserted at index " << i << "\n";
            return;
        }

        // 5) Insert at specific index
        Node *temp = start;
        for (int i = 0; i < index - 1; i++)
            temp = temp->next;

        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;

        size++;
        cout << "Inserted at index " << index << "\n";
    }

    // -----------------------------
    // Print nodes
    // index >=0: specific nodes
    // -1: in order, -2: reverse, -3: ascending, -4: descending
    // -----------------------------
    void print(int index) {
        if (size == 0) {
            cout << "List is empty.\n";
            return;
        }

        Node *temp;
        int i;

        if (index >= 0) {
            temp = start;
            for (i = 0; i < index && i < size; i++) {
                temp = temp->next;
            }
            cout << "[" << i << "]->" << temp->data << "\n";
            return;
        }

        switch (index) {
            case -1: // In order
                temp = start;
                i = 0;
                do {
                    cout << "[" << i << "]->" << temp->data << "\n";
                    temp = temp->next;
                    i++;
                } while (temp != start);
                break;

            case -2: // Reverse
                temp = end;
                i = 0;
                do {
                    cout << "[" << i << "]->" << temp->data << "\n";
                    temp = temp->prev;
                    i++;
                } while (temp != end);
                break;

            case -3: // Ascending
            case -4: // Descending
            {
                int *arr = new int[size];
                temp = start;
                for (int j = 0; j < size; j++) {
                    arr[j] = temp->data;
                    temp = temp->next;
                }

                // Simple bubble sort
                for (int i = 0; i < size - 1; i++)
                    for (int j = i + 1; j < size; j++)
                        if ((index == -3 && arr[i] > arr[j]) || (index == -4 && arr[i] < arr[j]))
                            swap(arr[i], arr[j]);

                for (int j = 0; j < size; j++)
                    cout << "[" << j + 1 << "]->" << arr[j] << "\n";

                delete[] arr;
                break;
            }

            default:
                cout << "Invalid print option.\n";
        }
    }

    // -----------------------------
    // Search for a value
    // -----------------------------
    void search(int data) {
        if (size == 0) {
            cout << "List is empty.\n";
            return;
        }

        Node *temp = start;
        for (int i = 0; i < size; i++) {
            if (temp->data == data) {
                cout << "Data found at index: " << i << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Data not found.\n";
    }

    // -----------------------------
    // Count nodes
    // -----------------------------
    void count() {
        cout << "Number of nodes: " << size << "\n";
    }

    // -----------------------------
    // Delete node by index
    // -----------------------------
    void deleteNode(int index) {
        if (size == 0) {
            cout << "List is empty.\n";
            return;
        }

        if (size == 1) {
            delete start;
            start = end = nullptr;
            size = 0;
            cout << "Node deleted. List is now empty.\n";
            return;
        }

        Node *temp = start;
        if (index == 0) { // Delete beginning
            temp = start;
            start = start->next;
            start->prev = end;
            end->next = start;
        } else if (index >= size - 1) { // Delete end
            temp = end;
            end = end->prev;
            end->next = start;
            start->prev = end;
        } else { // Delete middle
            for (int i = 0; i < index; i++)
                temp = temp->next;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        size--;
        cout << "Node deleted.\n";
    }

    // -----------------------------
    // Clear entire list
    // -----------------------------
    void clearList() {
        while (size > 0)
            deleteNode(0);
        cout << "List cleared.\n";
    }
};

// -----------------------------
// Main menu
// -----------------------------
int main() {
    LinkedList list;
    int choice, data, index;

    while (true) {
        cout << "\n----- Smart Linked-List MENU -----\n";
        cout << "1) Insert\n";
        cout << "2) Print list\n";
        cout << "3) Search\n";
        cout << "4) Count nodes\n";
        cout << "5) Delete a node\n";
        cout << "6) Clear list\n";
        cout << "0) Exit\n";
        cout << "----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 0:
                cout << "Exiting program...\n";
                list.clearList();
                return 0;

            case 1:
                cout << "Enter value and insertion index (0=start, -1=end, -2=sorted): ";
                cin >> data >> index;
                list.insert(data, index);
                break;

            case 2:
                cout << "Print options: -1=In order, -2=Reverse, -3=Ascending, -4=Descending, >=0=index: ";
                cin >> index;
                list.print(index);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> data;
                list.search(data);
                break;

            case 4:
                list.count();
                break;

            case 5:
                cout << "Enter node index to delete: ";
                cin >> index;
                list.deleteNode(index);
                break;

            case 6:
                list.clearList();
                break;

            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
