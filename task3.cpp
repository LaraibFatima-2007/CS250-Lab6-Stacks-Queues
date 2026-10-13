/*
 * Name: Laraib Fatima
 * CMS ID: 542052
 * Course: CS-250: Data Structures and Algorithms
 * Lab 6: Stacks and Queues - Task 3
 * Date: 12th October 2025
 * Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Description: Print Server Request Handling System using a dynamic circular queue.
 */

#include <iostream>

using namespace std;

// Structure to hold print request details
struct PrintRequest {
    int id;
    int arrivalTime;
    int processingTime;
};

class PrintServerQueue {
private:
    PrintRequest* arr;
    int capacity;
    int head;
    int tail;
    int count;

    // function to resize the array dynamically
    void resize(int new_capacity) {
        PrintRequest* newArr = new PrintRequest[new_capacity];
        
        for (int i = 0; i < count; i++) {
            newArr[i] = arr[(head + i) % capacity];
        }
        
        delete[] arr; 
        arr = newArr;
        head = 0;
        tail = count;
        capacity = new_capacity;
        
        cout << " New Capacity: " << capacity << endl;
    }

public:
    // Constructor
    PrintServerQueue(int cap = 2) {
        capacity = cap;
        arr = new PrintRequest[capacity];
        head = 0;
        tail = 0;
        count = 0;
    }

    // Destructor to free memory
    ~PrintServerQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }

    // Enqueue operation
    void enqueue(PrintRequest req) {
        if (isFull()) {
            resize(capacity * 2); // Double capacity when full
        }
        arr[tail] = req;
        tail = (tail + 1) % capacity;
        count++;
        
        cout << "Successfully Enqueued Request ID: " << req.id << endl;
        displayState();
    }

    // Dequeue operation
    PrintRequest dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty! No print requests to dequeue.\n";
            return {0, 0, 0};
        }
        
        PrintRequest req = arr[head];
        head = (head + 1) % capacity;
        count--;
        
        cout << "Processed & Dequeued Request ID: " << req.id << endl;
        displayState();
        
        // Auto shrink if queue becomes too sparse
        if (count > 0 && count <= capacity / 4 && capacity > 2) {
            resize(capacity / 2);
        }
        
        return req;
    }

    // View front request
    PrintRequest front() {
        if (isEmpty()) {
            cout << "Queue is Empty!\n";
            return {0, 0, 0};
        }
        return arr[head];
    }

    // Display current queue state
    void displayState() {
        cout << "  -> Current Queue State (Count: " << count << ", Capacity: " << capacity << "): ";
        if (isEmpty()) {
            cout << "[Empty]\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "[ID: " << arr[(head + i) % capacity].id << "] ";
        }
        cout << endl;
    }
};

int main() {
    PrintServerQueue pq(2); // Initial capacity
    int choice;
    double totalWaitingTime = 0;
    int processedCount = 0;
    int currentTime = 0;

    do {
        cout << "\n--- Print Server Management System ---\n";
        cout << "1. Enqueue Print Request\n";
        cout << "2. Dequeue (Process) Print Request\n";
        cout << "3. View Front Request\n";
        cout << "4. Show Average Waiting Time\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            PrintRequest r;
            cout << "Enter Request ID: ";
            cin >> r.id;
            cout << "Enter Arrival Time: ";
            cin >> r.arrivalTime;
            cout << "Enter Processing Time: ";
            cin >> r.processingTime;
            
            pq.enqueue(r);
        } 
        else if (choice == 2) {
            if (!pq.isEmpty()) {
                PrintRequest r = pq.front();
                int waitingTime = max(0, currentTime - r.arrivalTime);
                totalWaitingTime += waitingTime;
                processedCount++;
                
                currentTime += r.processingTime;
                pq.dequeue();
            } else {
                pq.dequeue();
            }
        } 
        else if (choice == 3) {
            PrintRequest r = pq.front();
            if (r.id != 0) {
                cout << "Front Request -> ID: " << r.id 
                     << ", Arrival: " << r.arrivalTime 
                     << ", Processing Time: " << r.processingTime << endl;
            }
        } 
        else if (choice == 4) {
            if (processedCount == 0) {
                cout << "No requests processed yet.\n";
            } else {
                double avgWait = totalWaitingTime / processedCount;
                cout << "Average Waiting Time for Processed Requests: " << avgWait << " units\n";
            }
        }
    } while (choice != 5);

    return 0;
}