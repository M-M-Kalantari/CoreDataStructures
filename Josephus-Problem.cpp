#include <iostream>
using namespace std;

/* ANSI color codes */
#define RESET   "\033[0m"
#define GREEN   "\033[32m"   // نفر فعلی
#define RED     "\033[31m"   // نفر در حال حذف

/* Doubly linked list node */
struct Node {
    int id;
    Node* next;
    Node* prev;
    Node(int v) : id(v), next(nullptr), prev(nullptr) {}
};

/* Josephus Circular Doubly Linked List */
class JosephusList {
private:
    Node* head;
    int size;

public:
    JosephusList() : head(nullptr), size(0) {}

    void create(int n) {
        for (int i = 1; i <= n; i++)
            pushBack(i);
    }

    void pushBack(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
        }
        size++;
    }

    /* Display with colors */
    void display(Node* current, Node* toRemove) {
        Node* temp = head;
        cout << "\nCircle: ";
        do {
            if (temp == current)
                cout << GREEN << "[*" << temp->id << "*] " << RESET;
            else if (temp == toRemove)
                cout << RED << "[!" << temp->id << "!] " << RESET;
            else
                cout << "[ " << temp->id << " ] ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    int solve() {
        Node* curr = head;

        while (size > 1) {
            Node* victim = curr->next;
            display(curr, victim);
            cout << "Killed: " << victim->id << endl;

            victim->prev->next = victim->next;
            victim->next->prev = victim->prev;

            if (victim == head)
                head = victim->next;

            curr = victim->next;
            delete victim;
            size--;
        }

        cout << "\nFinal survivor:";
        display(curr, nullptr);
        return curr->id;
    }
};

int main() {
    int n;
    cout << "Enter number of people: ";
    cin >> n;
    if (n <= 0) {
        cout << "Invalid input!";
        return 0;
    }

    JosephusList jl;
    jl.create(n);

    int winner = jl.solve();
    cout << "\nWinner is person: " << winner << endl;

    return 0;
}