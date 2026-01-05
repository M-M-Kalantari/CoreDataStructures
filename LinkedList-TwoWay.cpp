#include <iostream>
using namespace std;

// =============================================================
// Node structure for the Doubly Linked List
// =============================================================
struct Node {
    int data;     // Holds the node's value
    Node *next;   // Pointer to the next node
    Node *prev;   // Pointer to the previous node
};

// =============================================================
// Insert a new node at the beginning of the list
// =============================================================
void insertAtBeginning(Node *&head) {
    cout << "\n>>> [START] Insert at Beginning\n";

    int value;
    cout << "Enter value: ";
    cin >> value;

    Node* newNode = new Node;   // Create a new node
    newNode->data = value;      // Set node value
    newNode->prev = nullptr;    // New head has no previous node
    newNode->next = head;       // Next will be the old head

    if (head != nullptr)        // If list not empty, fix old head's prev
        head->prev = newNode;

    head = newNode;             // Move head to the new node

    cout << ">>> [DONE] Inserted at beginning.\n";
}

// =============================================================
// Insert a new node at the end of the list
// =============================================================
void insertAtEnd(Node *&head) {
    cout << "\n>>> [START] Insert at End\n";

    int value;
    cout << "Enter value: ";
    cin >> value;

    Node* newNode = new Node;     // Create a new node
    newNode->data = value;        // Set node value
    newNode->next = nullptr;      // Last node has no next
    newNode->prev = nullptr;      // Will set later

    if (head == nullptr) {        // Case: empty list
        head = newNode;           // New node becomes head
        cout << ">>> [DONE] Inserted as first node.\n";
        return;
    }

    Node* temp = head;            // Start from head
    while (temp->next != nullptr) // Move to the last node
        temp = temp->next;

    temp->next = newNode;         // Last node points to new node
    newNode->prev = temp;         // New node points back to last

    cout << ">>> [DONE] Inserted at end.\n";
}

// =============================================================
// Insert a value in sorted ascending order
// =============================================================
void insertSorted(Node *&head) {
    cout << "\n>>> [START] Insert Sorted\n";

    int value;
    cout << "Enter value: ";
    cin >> value;

    Node* newNode = new Node;   // Create new node
    newNode->data = value;      // Set value

    // Case 1: list empty OR insert before head
    if (head == nullptr || value <= head->data) {
        newNode->next = head;       // New node points to old head
        newNode->prev = nullptr;    // No previous node

        if (head != nullptr)        // Fix previous pointer of old head
            head->prev = newNode;

        head = newNode;             // Move head to new node

        cout << ">>> [DONE] Inserted as new head.\n";
        return;
    }

    Node* current = head;           // Start walking the list

    // Move forward until we find the right spot
    while (current->next != nullptr && current->next->data < value) {
        current = current->next;
    }

    // Insert between current and current->next
    newNode->next = current->next;  // Link to next node
    newNode->prev = current;        // Link back to current

    if (current->next != nullptr)   // Fix next node's prev pointer
        current->next->prev = newNode;

    current->next = newNode;        // Current points to new node

    cout << ">>> [DONE] Inserted in sorted order.\n";
}

// =============================================================
// Delete a node with a specific value
// =============================================================
void deleteValue(Node *&head) {
    cout << "\n>>> [START] Delete Value\n";

    int value;
    cout << "Enter value to delete: ";
    cin >> value;

    if (head == nullptr) {                // Empty list
        cout << "List is empty.\n";
        return;
    }

    // Case 1: delete head
    if (head->data == value) {
        Node* del = head;                 // Store old head
        head = head->next;                // Move head forward

        if (head != nullptr)              // Fix prev pointer
            head->prev = nullptr;

        delete del;                       // Free memory
        cout << ">>> [DONE] Deleted value from head.\n";
        return;
    }

    Node* current = head->next;           // Start from second node

    // Find value
    while (current != nullptr && current->data != value) {
        current = current->next;
    }

    if (current == nullptr) {             // Value not found
        cout << "Value not found.\n";
        return;
    }

    // Fix links on both sides
    if (current->prev != nullptr)
        current->prev->next = current->next;

    if (current->next != nullptr)
        current->next->prev = current->prev;

    delete current;                        // Remove node

    cout << ">>> [DONE] Value deleted.\n";
}

// =============================================================
// Search for a value in the list
// =============================================================
void search(Node *&head) {
    cout << "\n>>> [START] Search\n";

    int value;
    cout << "Enter value to search: ";
    cin >> value;

    Node* temp = head;                     // Start from head
    while (temp != nullptr) {
        if (temp->data == value) {         // Found the value
            cout << ">>> Found! Address: " << temp << endl;
            return;
        }
        temp = temp->next;                 // Move forward
    }

    cout << ">>> Value NOT found.\n";
}

// =============================================================
// Print the list forward AND backward
// =============================================================
void printList(Node *&head) {
    cout << "\n>>> [START] Print List\n";

    if (head == nullptr) {                // Empty list
        cout << "List is empty.\n";
        return;
    }

    Node* temp = head;                    // Start from head

    cout << "Forward : ";
    while (temp->next != nullptr) {       // Print forward
        cout << "[" << temp->data << "] <-> ";
        temp = temp->next;
    }
    cout << "[" << temp->data << "] -> NULL\n"; // Last node

    cout << "Backward: ";
    while (temp != nullptr) {             // Print backward
        cout << "[" << temp->data << "] <-> ";
        temp = temp->prev;
    }
    cout << "NULL\n";

    cout << ">>> [DONE] Printing completed.\n";
}

// =============================================================
// Count the number of nodes in the list
// =============================================================
void countNodes(Node *&head) {
    cout << "\n>>> [START] Count Nodes\n";

    int count = 0;
    Node* temp = head;

    while (temp != nullptr) {     // Loop through all nodes
        count++;
        temp = temp->next;
    }

    cout << "Number of nodes: " << count << endl;
    cout << ">>> [DONE] Counting completed.\n";
}

// =============================================================
// Clear the entire list and free memory
// =============================================================
void clearList(Node *&head) {
    cout << "\n>>> [START] Clear List\n";

    Node* temp = head;

    while (temp != nullptr) {     // Walk and delete each node
        Node* del = temp;
        temp = temp->next;
        delete del;
    }

    head = nullptr;               // Mark list as empty

    cout << ">>> [DONE] List cleared.\n";
}

// =============================================================
// Main program menu
// =============================================================
int main() {
    Node* head = nullptr;    // Pointer to the first node
    int choice;

    while (true) {           // Infinite menu loop
        cout << "\n\n----- Doubly Linked-List MENU -----\n";
        cout << "1) Insert at beginning\n";
        cout << "2) Insert at end\n";
        cout << "3) Insert sorted\n";
        cout << "4) Delete a value\n";
        cout << "5) Search\n";
        cout << "6) Print list\n";
        cout << "7) Count nodes\n";
        cout << "8) Clear list\n";
        cout << "0) Exit\n";
        cout << "----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0)      // Exit program
            break;

        switch (choice) {
            case 1: insertAtBeginning(head); break;
            case 2: insertAtEnd(head); break;
            case 3: insertSorted(head); break;
            case 4: deleteValue(head); break;
            case 5: search(head); break;
            case 6: printList(head); break;
            case 7: countNodes(head); break;
            case 8: clearList(head); break;
            default: cout << "Invalid choice!\n";
        }
    }

    clearList(head);          // Cleanup before exit
    return 0;                 // End program
}