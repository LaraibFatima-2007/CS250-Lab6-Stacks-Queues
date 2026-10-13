/*
 * Name: Laraib Fatima
 * CMS ID: 542052
 * Course: CS-250: Data Structures and Algorithms
 * Lab 6: Stacks and Queues - Task 4
 * Date: 12th October 2025
 * Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Description: Emergency Ward Waiting Room Management System.
 */

#include <iostream>
#include <string>

using namespace std;

class EmergencyWaitingRoom {
private:
    struct Patient {
        int id;
        string name;
    };
    
    Patient* queueArr;
    int capacity;
    int frontIdx;
    int rearIdx;
    int size;
    int idCounter; // Auto-generated 

public:
    // Constructor
    EmergencyWaitingRoom(int cap = 100) {
        capacity = cap;
        queueArr = new Patient[capacity];
        frontIdx = 0;
        rearIdx = -1;
        size = 0;
        idCounter = 1;
    }

    // Destructor
    ~EmergencyWaitingRoom() {
        delete[] queueArr;
    }

    // 1. Register Patient
    void RegisterPatient(string name) {
        if (size >= capacity) {
            cout << "Waiting room is full!\n";
            return;
        }
        rearIdx = (rearIdx + 1) % capacity;
        queueArr[rearIdx] = {idCounter, name};
        size++;
        
        cout << "Registered Patient -> ID: " << idCounter << " (" << name << ")\n";
        idCounter++;
    }

    // 2. Serve Patient
    void ServePatient() {
        if (CanDoctorGoHome()) {
            cout << "No patients waiting to be served.\n";
            return;
        }
        Patient p = queueArr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        size--;
        
        cout << "Serving Patient ID: " << p.id << " (" << p.name << ")\n";
    }

    // 3. CancelAll
    void CancelAll() {
        frontIdx = 0;
        rearIdx = -1;
        size = 0;
        cout << "All appointments cancelled. Doctor can go to lunch!\n";
    }

    // 4. CanDoctorGoHome
    bool CanDoctorGoHome() {
        return size == 0;
    }

    // 5. ShowAllPatient
    void ShowAllPatient() {
        if (CanDoctorGoHome()) {
            cout << "No patients currently waiting in the room.\n";
            return;
        }
        
        // Create a temporary array to store IDs
        int* tempIDs = new int[size];
        for (int i = 0; i < size; i++) {
            tempIDs[i] = queueArr[(frontIdx + i) % capacity].id;
        }
        
        // IDs in ascending order
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (tempIDs[j] > tempIDs[j + 1]) {
                    int temp = tempIDs[j];
                    tempIDs[j] = tempIDs[j + 1];
                    tempIDs[j + 1] = temp;
                }
            }
        }

        cout << "Waiting Patients IDs: ";
        for (int i = 0; i < size; i++) {
            cout << tempIDs[i] << " ";
        }
        cout << endl;
        
        delete[] tempIDs;
    }
};

int main() {
    EmergencyWaitingRoom room;
    int choice;
    string name;

    do {
        cout << "\n--- Emergency Ward Waiting Room Menu ---\n";
        cout << "1. Register Patient\n";
        cout << "2. Serve Patient\n";
        cout << "3. Show All Patient IDs (Sorted)\n";
        cout << "4. Cancel All Appointments\n";
        cout << "5. Can Doctor Go Home?\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter patient name: ";
            cin >> name;
            room.RegisterPatient(name);
        } 
        else if (choice == 2) {
            room.ServePatient();
        } 
        else if (choice == 3) {
            room.ShowAllPatient();
        } 
        else if (choice == 4) {
            room.CancelAll();
        } 
        else if (choice == 5) {
            if (room.CanDoctorGoHome()) {
                cout << "Yes: No one is waiting, doctor can go home.\n";
            } else {
                cout << "No: Patients are still waiting.\n";
            }
        }
    } while (choice != 6);

    return 0;
}