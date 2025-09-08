// 1. Searching and Sorting -- CO1, CO2 
// Design a program to maintain a student database that performs the following tasks: 
// 1. Add and store student details (ID, Name, CGPA) using dynamically allocated memory. 
// 2. Expand the student list using realloc() as new entries are added. 
// 3. Implement Linear Search and Binary Search to find student records by ID. 
// 4. Implement at least two Sorting Algorithms (Bubble Sort, Selection Sort, or Insertion Sort) to sort student records by: 
// o Name (Alphabetically) 
// o CGPA (Ascending/Descending) 
// 5. Analyze and compare the performance of search operations before and after sorting. 


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <chrono>

using namespace std;

struct Student {
    int id;
    char name[50];
    float cgpa;
};

// Function Prototypes
void addStudent(Student* &students, int &size);
void displayStudents(Student* students, int size);
int linearSearch(Student* students, int size, int id);
int binarySearch(Student* students, int size, int id);
void bubbleSortByName(Student* students, int size);
void selectionSortByCGPA(Student* students, int size, bool ascending);

int main() {
    Student* students = (Student*)malloc(0); // Initially empty
    int size = 0, choice;

    do {
        cout << "\n===== Student Database Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Linear Search by ID\n";
        cout << "4. Binary Search by ID (after sorting by ID)\n";
        cout << "5. Sort by Name (Bubble Sort)\n";
        cout << "6. Sort by CGPA (Selection Sort)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                addStudent(students, size);
                break;

            case 2:
                displayStudents(students, size);
                break;

            case 3: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;

                auto start = chrono::high_resolution_clock::now();
                int index = linearSearch(students, size, id);
                auto end = chrono::high_resolution_clock::now();

                if(index != -1)
                    cout << "Student found: " << students[index].name << " | CGPA: " << students[index].cgpa << "\n";
                else
                    cout << "Student not found!\n";

                cout << "Linear Search Time: "
                     << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n";
                break;
            }

            case 4: {
                // Sort by ID for Binary Search
                sort(students, students + size, [](Student a, Student b){ return a.id < b.id; });

                int id;
                cout << "Enter ID to search: ";
                cin >> id;

                auto start = chrono::high_resolution_clock::now();
                int index = binarySearch(students, size, id);
                auto end = chrono::high_resolution_clock::now();

                if(index != -1)
                    cout << "Student found: " << students[index].name << " | CGPA: " << students[index].cgpa << "\n";
                else
                    cout << "Student not found!\n";

                cout << "Binary Search Time: "
                     << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n";
                break;
            }

            case 5:
                bubbleSortByName(students, size);
                cout << "Sorted by Name (Alphabetically)\n";
                break;

            case 6: {
                int order;
                cout << "Sort CGPA in: 1. Ascending  2. Descending: ";
                cin >> order;
                selectionSortByCGPA(students, size, order == 1);
                cout << "Sorted by CGPA\n";
                break;
            }

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while(choice != 0);

    free(students);
    return 0;
}

// Function Definitions

void addStudent(Student* &students, int &size) {
    size++;
    students = (Student*)realloc(students, size * sizeof(Student));

    cout << "Enter Student ID: ";
    cin >> students[size - 1].id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(students[size - 1].name, 50);
    cout << "Enter CGPA: ";
    cin >> students[size - 1].cgpa;

    cout << "Student added successfully!\n";
}

void displayStudents(Student* students, int size) {
    if(size == 0) {
        cout << "No students in database.\n";
        return;
    }
    cout << "\nID\tName\t\tCGPA\n";
    for(int i = 0; i < size; i++) {
        cout << students[i].id << "\t" << students[i].name << "\t\t" << students[i].cgpa << "\n";
    }
}

int linearSearch(Student* students, int size, int id) {
    for(int i = 0; i < size; i++) {
        if(students[i].id == id)
            return i;
    }
    return -1;
}

int binarySearch(Student* students, int size, int id) {
    int low = 0, high = size - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if(students[mid].id == id)
            return mid;
        else if(students[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void bubbleSortByName(Student* students, int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(strcmp(students[j].name, students[j + 1].name) > 0) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void selectionSortByCGPA(Student* students, int size, bool ascending) {
    for(int i = 0; i < size - 1; i++) {
        int index = i;
        for(int j = i + 1; j < size; j++) {
            if(ascending ? (students[j].cgpa < students[index].cgpa) : (students[j].cgpa > students[index].cgpa)) {
                index = j;
            }
        }
        swap(students[i], students[index]);
    }
}
