#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
using namespace std;

const int TOTAL_SEATS = 30;

struct Passenger
{
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};

int* seats = nullptr;
Passenger* head = nullptr;

// Function to clear input
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to book ticket
void bookTicket()
{
    int seatNo = 0;

    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        if (seats[i] == 0)
        {
            seatNo = i + 1;
            break;
        }
    }

    if (seatNo == 0)
    {
        cout << "All seats are booked.\n";
        return;
    }

    Passenger* newPassenger = new Passenger;

    newPassenger->seatNo = seatNo;

    cout << "Enter Name: ";
    getline(cin >> ws, newPassenger->name);

    cout << "Enter Age: ";
    while (!(cin >> newPassenger->age) || newPassenger->age <= 0)
    {
        cout << "Enter valid age: ";
        clearInput();
    }

    cout << "Enter Gender (M/F): ";
    cin >> newPassenger->gender;

    newPassenger->next = nullptr;

    if (head == nullptr)
    {
        head = newPassenger;
    }
    else
    {
        Passenger* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newPassenger;
    }

    seats[seatNo - 1] = 1;

    cout << "Ticket booked! Seat No: " << seatNo << "\n";
}

// Function to cancel ticket
void cancelTicket()
{
    int seatNo;

    cout << "Enter seat number to cancel: ";

    if (!(cin >> seatNo))
    {
        cout << "Invalid input.\n";
        clearInput();
        return;
    }

    if (seatNo < 1 || seatNo > TOTAL_SEATS ||
        seats[seatNo - 1] == 0)
    {
        cout << "Seat is not booked or invalid.\n";
        return;
    }

    Passenger* current = head;
    Passenger* previous = nullptr;

    while (current != nullptr &&
           current->seatNo != seatNo)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Passenger not found.\n";
        return;
    }

    if (previous == nullptr)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    delete current;

    seats[seatNo - 1] = 0;

    cout << "Ticket cancelled successfully.\n";
}

// Function to view train status
void viewTrainStatus()
{
    cout << "\n--- Train Status ---\n";

    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        cout << "Seat " << i + 1 << ": ";

        if (seats[i] == 1)
            cout << "Booked";
        else
            cout << "Available";

        cout << "\n";
    }
}

// Function to view passenger list
void viewPassengerList()
{
    if (head == nullptr)
    {
        cout << "No passengers booked yet.\n";
        return;
    }

    cout << "\n--- Passenger List ---\n";

    Passenger* current = head;

    while (current != nullptr)
    {
        cout << "Seat No: " << current->seatNo
             << " | Name: " << current->name
             << " | Age: " << current->age
             << " | Gender: " << current->gender
             << "\n";

        current = current->next;
    }
}

// Function to free allocated memory
void freeMemory()
{
    Passenger* current = head;

    while (current != nullptr)
    {
        Passenger* nextPassenger = current->next;

        delete current;

        current = nextPassenger;
    }

    head = nullptr;

    free(seats);

    seats = nullptr;
}

// Main function
int main()
{
    seats = (int*)malloc(TOTAL_SEATS * sizeof(int));

    if (seats == nullptr)
    {
        cout << "Memory allocation failed.\n";
        return 1;
    }

    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        seats[i] = 0;
    }

    int choice;

    do
    {
        cout << "\n===== Railway Reservation System =====\n";

        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Please enter a valid number.\n";
            clearInput();
            continue;
        }

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                cancelTicket();
                break;

            case 3:
                viewTrainStatus();
                break;

            case 4:
                viewPassengerList();
                break;

            case 5:
                freeMemory();

                cout << "Program closed successfully.\n";
                cout << "Memory released.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
