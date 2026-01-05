#include <iostream>
using namespace std;

// ---------------------------------------------------------
// Node structure for the singly linked list
// ---------------------------------------------------------
struct Node {
    int data;
    Node *next;
};

// ---------------------------------------------------------
// Insert a new node at the beginning of the list
// ---------------------------------------------------------
void insertAtBeginning(Node *&head) {
    cout << "\n>>> [START] Insert at Beginning\n";

    int value;
    cout << "Enter value: ";
    cin >> value;

    Node *newNode = new Node;   // Allocate memory for a new node
    newNode->data = value;      // Store the provided value in the new node
    newNode->next = head;       // Point new node's next to the current head (could be nullptr)
    head = newNode;             // Update head to be the new node (now first element)

    cout << ">>> [DONE] Inserted at beginning successfully.\n";
}

// ---------------------------------------------------------
// Insert a new node at the end of the list
// ---------------------------------------------------------
void insertAtEnd(Node *&head) {
    cout << "\n>>> [START] Insert at End\n";

    int value;
    cout << "Enter value: ";
    cin >> value;

    Node* newNode = new Node;   // Allocate a new node
    newNode->data = value;      // Assign the input value to the new node
    newNode->next = nullptr;    // Since this will become the last node, its next is nullptr

    if (head == nullptr) {      // If the list is empty...
        head = newNode;         // ...the new node becomes the head
        cout << ">>> [DONE] Inserted as first node (list was empty).\n";
        return;                 // Finish the operation
    }

    Node* temp = head;          // Start traversal from the head
    while (temp->next != nullptr) { // Move until the current node is the last (next == nullptr)
        temp = temp->next;      // Advance to next node
    }
    temp->next = newNode;       // Link the former last node to the newly created node

    cout << ">>> [DONE] Inserted at end successfully.\n";
}

// ---------------------------------------------------------
// Insert a new node while keeping the list sorted
// (ascending order)
// ---------------------------------------------------------
void insertSorted(Node *&head) {
    cout << "\n>>> [START] Insert Sorted\n";

    int value;
    cout << "Enter value: ";
    cin >> value;

    Node* newNode = new Node;   // Allocate a new node
    newNode->data = value;      // Set its data
    newNode->next = nullptr;    // Default next is nullptr

    // If list empty or new value should be new head:
    if (head == nullptr || value <= head->data) {
        newNode->next = head;   // Link new node to current head (maybe nullptr)
        head = newNode;         // Make new node the head
        cout << ">>> [DONE] Inserted in sorted order (new head).\n";
        return;
    }

    Node* current = head;       // Start from head to find insertion point
    // Move while next exists and next's data is still less than value
    while (current->next != nullptr && current->next->data < value) {
        current = current->next; // Advance to next node
    }
    // Insert newNode after current (could be middle or end)
    newNode->next = current->next; // Point new node to current's next
    current->next = newNode;       // Link current to new node

    cout << ">>> [DONE] Inserted in sorted order successfully.\n";
}

// ---------------------------------------------------------
// Delete the first node that matches the specified value
// ---------------------------------------------------------
void deleteValue(Node *&head) {
    cout << "\n>>> [START] Delete Value\n";

    int value;
    cout << "Enter value to delete: ";
    cin >> value;

    if (head == nullptr) {      // Empty list: nothing to delete
        cout << "List is empty. Nothing to delete.\n";
        return;
    }

    // If the head node holds the target value:
    if (head->data == value) {
        Node* del = head;       // Keep pointer to node to delete
        head = head->next;      // Move head to next node (could be nullptr)
        delete del;             // Free memory of removed node
        cout << ">>> [DONE] Value deleted from head.\n";
        return;
    }

    Node* current = head;      // Start traversal to search for the node
    Node* prev = nullptr;      // Will keep track of node before current

    // Traverse until we find the node or reach end
    while (current != nullptr && current->data != value) {
        prev = current;        // Save previous node
        current = current->next; // Advance current
    }

    if (current != nullptr) {  // Found the node
        prev->next = current->next; // Bypass current node in the list
        delete current;            // Free memory
        cout << ">>> [DONE] Value deleted successfully.\n";
    } else {
        cout << "Value not found. Nothing deleted.\n"; // Value not in list
    }
}

// ---------------------------------------------------------
// Search for a value inside the list
// ---------------------------------------------------------
void search(Node *&head) {
    cout << "\n>>> [START] Search\n";

    int value;
    cout << "Enter value to search: ";
    cin >> value;

    Node *result = nullptr;    // Will point to the found node (if any)
    Node* temp = head;         // Start from head

    while (temp != nullptr) {  // Traverse entire list
        if (temp->data == value) {
            result = temp;     // Save the node where value is found (keeps last occurrence)
            break;             // Stop at first occurrence (change if you want last)
        }
        temp = temp->next;     // Advance to next node
    }

    if (result != nullptr)
        cout << ">>> Found! Address: " << result << endl; // Print pointer (address)
    else
        cout << ">>> Value NOT found.\n";

    cout << ">>> [DONE] Search completed.\n";
}

// ---------------------------------------------------------
// Print all nodes of the list
// ---------------------------------------------------------
void printList(Node *&head) {
    cout << "\n>>> [START] Print List\n";

    if (head == nullptr) {     // Empty list check
        cout << "List is empty.\n";
        return;
    }

    Node* temp = head;         // Start from head
    cout << "Linked List: ";
    while (temp != nullptr) {  // Traverse until end
        cout << "[" << temp->data << " - " << temp << "] -> "; // Show value and node address
        temp = temp->next;     // Move to next node
    }
    cout << "NULL\n";          // End marker

    cout << ">>> [DONE] Printing completed.\n";
}

// ---------------------------------------------------------
// Count how many nodes exist in the list
// ---------------------------------------------------------
void countNodes(Node *&head) {
    cout << "\n>>> [START] Count Nodes\n";

    int count = 0;             // Counter initialization
    Node* temp = head;         // Start traversal from head

    while (temp != nullptr) {  // Count each node until end
        count++;               // Increment for each visited node
        temp = temp->next;     // Advance to next
    }

    cout << "Number of nodes: " << count << endl; // Output count
    cout << ">>> [DONE] Counting completed.\n";
}

// ---------------------------------------------------------
// Delete all nodes and clear the list
// ---------------------------------------------------------
void clearList(Node *&head) {
    cout << "\n>>> [START] Clear List\n";

    Node* temp;                // Temporary pointer for deletion
    while (head != nullptr) {  // Keep deleting until list becomes empty
        temp = head;           // Save current head to delete
        head = head->next;     // Move head forward
        delete temp;           // Free the node memory
    }

    cout << ">>> [DONE] List cleared.\n";
}

// ---------------------------------------------------------
// Main program with menu loop
// ---------------------------------------------------------
int main() {
    // Pointer to the first node of the linked list
    // set to null to represent an empty list
    Node *head = nullptr;

    int choice;
    while (true) {
        cout << "\n\n----- Linked-List MENU -----\n";
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

        if (choice == 0) {
            cout << "\n>>> Exiting program...\n";
            break;
        }

        // Handle menu options
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

    // Final cleanup
    clearList(head);
    return 0;
}