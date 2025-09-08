// 3. Circular Queue -- CO1, CO2 
// Implement Circular Queue using Array. Perform following operations on it. 
// a) Insertion (Enqueue) 
// b) Deletion (Dequeue) 
// c) Display 
// (Note: Handle queue full condition by considering a fixed size of a queue.) 
 
 
#include <iostream> 
using namespace std; 
 
#define MAX 5  // Fixed size of the queue 
 
class CircularQueue { 
    int queue[MAX]; 
    int front, rear; 
 
public: 
    CircularQueue() { 
        front = -1; 
        rear = -1; 
    } 
 
    bool isFull() { 
        return (front == (rear + 1) % MAX); 
    } 
 
    bool isEmpty() { 
        return (front == -1); 
    } 
 
    void enqueue(int value) { 
        if (isFull()) { 
            cout << "Queue is Full! Cannot insert " << value << endl; 
            return; 
        } 
        if (isEmpty()) { 
            front = rear = 0; 
        } else { 
            rear = (rear + 1) % MAX; 
        } 
        queue[rear] = value; 
        cout << "Inserted: " << value << endl; 
    } 
 
    void dequeue() { 
        if (isEmpty()) { 
            cout << "Queue is Empty! Cannot delete.\n"; 
            return; 
        } 
        cout << "Deleted: " << queue[front] << endl; 
        if (front == rear) {  // Only one element 
            front = rear = -1; 
        } else { 
            front = (front + 1) % MAX; 
        } 
    } 
 
    void display() { 
        if (isEmpty()) { 
            cout << "Queue is Empty!\n"; 
            return; 
        } 
 
        cout << "Queue contents: "; 
        int i = front; 
        while (true) { 
            cout << queue[i] << " "; 
            if (i == rear) 
                break; 
            i = (i + 1) % MAX; 
        } 
        cout << endl; 
    } 
}; 
 
// Main menu-driven function 
int main() { 
    CircularQueue cq; 
    int choice, value; 
 
    do { 
        cout << "\n--- Circular Queue Menu ---\n"; 
        cout << "1. Enqueue (Insert)\n"; 
        cout << "2. Dequeue (Delete)\n"; 
        cout << "3. Display\n"; 
        cout << "4. Exit\n"; 
        cout << "Enter choice: "; 
        cin >> choice; 
 
        switch (choice) { 
        case 1: 
            cout << "Enter value to insert: "; 
            cin >> value; 
            cq.enqueue(value); 
            break; 
        case 2: 
            cq.dequeue(); 
            break; 
        case 3: 
            cq.display(); 
            break; 
        case 4: 
            cout << "Exiting...\n"; 
            break; 
        default: 
            cout << "Invalid choice!\n"; 
        } 
    } while (choice != 4); 
 
    return 0; 
} 
 
 