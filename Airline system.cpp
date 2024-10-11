#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Flight struct to hold flight data
struct Flight {
    int flightID;
    string flightName;
    string departureCity;
    string arrivalCity;
    string departureDate;
    int seatsAvailable;
    double price;
};

// Ticket struct to hold ticket data
struct Ticket {
    int flightID;
    string passengerName;
    double amountPaid;
};

// Function declarations
void adminMenu();
void userMenu();
void addFlight();
void deleteFlight();
void updateFlight();
void viewAllFlights();
void searchFlights();
void bookFlight();
void cancelFlight();
void viewBookedFlights();
void makePayment(Ticket& ticket);
bool authenticateAdmin();
void displayFlight(const Flight& flight);

// Function to display the main menu and route to admin or user functions
void mainMenu() {
    int choice;
    cout << "Welcome to the Airline System" << endl;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        if (authenticateAdmin()) {
            adminMenu();
        }
        else {
            cout << "Authentication failed!" << endl;
        }
        break;
    case 2:
        userMenu();
        break;
    case 3:
        cout << "Exiting the system..." << endl;
        break;
    default:
        cout << "Invalid choice. Try again." << endl;
        mainMenu();
        break;
    }
}

// Authentication function for the admin
bool authenticateAdmin() {
    string password;
    cout << "Enter admin password: ";
    cin >> password;
    if (password == "AdMiN192837465") {
        return true;
    }
    return false;
}

// Admin menu
void adminMenu() {
    int choice;
    cout << "\n Admin Menu" << endl;
    cout << "1. Add Flight" << endl;
    cout << "2. Delete Flight" << endl;
    cout << "3. Update Flight" << endl;
    cout << "4. View All Flights" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        addFlight();
        break;
    case 2:
        deleteFlight();
        break;
    case 3:
        updateFlight();
        break;
    case 4:
        viewAllFlights();
        break;
    case 5:
        cout << "Exiting admin menu..." << endl;
        break;
    default:
        cout << "Invalid choice. Try again." << endl;
        adminMenu();
        break;
    }
}

// User menu
void userMenu() {
    int choice;
    cout << "\n User Menu" << endl;
    cout << "1. Search Flights" << endl;
    cout << "2. Book Flight" << endl;
    cout << "3. Cancel Flight" << endl;
    cout << "4. View Booked Flights" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        searchFlights();
        break;
    case 2:
        bookFlight();
        break;
    case 3:
        cancelFlight();
        break;
    case 4:
        viewBookedFlights();
        break;
    case 5:
        cout << "Exiting user menu..." << endl;
        break;
    default:
        cout << "Invalid choice. Try again." << endl;
        userMenu();
        break;
    }
}

// Function to add a flight (Admin)
void addFlight() {
    Flight newFlight;
    ofstream outFile("flights.txt", ios::app); 

    cout << "Enter flight ID: ";
    cin >> newFlight.flightID;
    cout << "Enter flight name: ";
    cin.ignore();
    getline(cin, newFlight.flightName);
    cout << "Enter departure city: ";
    getline(cin, newFlight.departureCity);
    cout << "Enter arrival city: ";
    getline(cin, newFlight.arrivalCity);
    cout << "Enter departure date (YYYY-MM-DD): ";
    getline(cin, newFlight.departureDate);
    cout << "Enter seats available: ";
    cin >> newFlight.seatsAvailable;
    cout << "Enter ticket price: ";
    cin >> newFlight.price;

    outFile << newFlight.flightID << " " << newFlight.flightName << " " << newFlight.departureCity << " "
        << newFlight.arrivalCity << " " << newFlight.departureDate << " " << newFlight.seatsAvailable << " "
        << newFlight.price << endl;

    outFile.close();
    cout << "Flight added successfully!" << endl;
    adminMenu();
}

// Function to delete a flight (Admin)
void deleteFlight() {
    int flightID;
    cout << "Enter the flight ID to delete: ";
    cin >> flightID;

    ifstream inFile("flights.txt");
    ofstream tempFile("temp.txt");
    Flight flight;
    bool found = false;

    while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
        >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
        if (flight.flightID == flightID) {
            found = true;
            continue; // Skip the line to be deleted
        }
        tempFile << flight.flightID << " " << flight.flightName << " " << flight.departureCity << " "
            << flight.arrivalCity << " " << flight.departureDate << " " << flight.seatsAvailable << " "
            << flight.price << endl;
    }

    inFile.close();
    tempFile.close();
    remove("flights.txt");
    rename("temp.txt", "flights.txt");

    if (found) {
        cout << "Flight deleted successfully!" << endl;
    }
    else {
        cout << "Flight ID not found!" << endl;
    }

    adminMenu();
}

// Function to update a flight (Admin)
void updateFlight() {
    int flightID;
    cout << "Enter the flight ID to update: ";
    cin >> flightID;

    ifstream inFile("flights.txt");
    ofstream tempFile("temp.txt");
    Flight flight;
    bool found = false;

    while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
        >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
        if (flight.flightID == flightID) {
            found = true;
            cout << "Enter new flight name: ";
            cin.ignore();
            getline(cin, flight.flightName);
            cout << "Enter new departure city: ";
            getline(cin, flight.departureCity);
            cout << "Enter new arrival city: ";
            getline(cin, flight.arrivalCity);
            cout << "Enter new departure date (YYYY-MM-DD): ";
            getline(cin, flight.departureDate);
            cout << "Enter new seats available: ";
            cin >> flight.seatsAvailable;
            cout << "Enter new ticket price: ";
            cin >> flight.price;
        }
        tempFile << flight.flightID << " " << flight.flightName << " " << flight.departureCity << " "
            << flight.arrivalCity << " " << flight.departureDate << " " << flight.seatsAvailable << " "
            << flight.price << endl;
    }

    inFile.close();
    tempFile.close();
    remove("flights.txt");
    rename("temp.txt", "flights.txt");

    if (found) {
        cout << "Flight updated successfully!" << endl;
    }
    else {
        cout << "Flight ID not found!" << endl;
    }

    adminMenu();
}

// Function to view all flights (Admin)
void viewAllFlights() {
    ifstream inFile("flights.txt");
    Flight flight;
    cout << "\nFlight Records:" << endl;
    while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
        >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
        displayFlight(flight);
    }

    inFile.close();
    adminMenu();
}

// Function to display flight details
void displayFlight(const Flight& flight) {
    cout << "Flight ID: " << flight.flightID << endl;
    cout << "Flight Name: " << flight.flightName << endl;
    cout << "Departure City: " << flight.departureCity << endl;
    cout << "Arrival City: " << flight.arrivalCity << endl;
    cout << "Departure Date: " << flight.departureDate << endl;
    cout << "Seats Available: " << flight.seatsAvailable << endl;
    cout << "Price: " << flight.price << endl;
    cout << "-------------------------------" << endl;
}

// Function to search flights (User)
void searchFlights() {
    string departureCity, arrivalCity, date;
    cout << "Enter departure city: ";
    cin.ignore();
    getline(cin, departureCity);
    cout << "Enter arrival city: ";
    getline(cin, arrivalCity);
    cout << "Enter departure date (YYYY-MM-DD): ";
    getline(cin, date);

    ifstream inFile("flights.txt");
    Flight flight;
    bool found = false;
    cout << "\nAvailable Flights:" << endl;

    while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
        >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
        if (flight.departureCity == departureCity && flight.arrivalCity == arrivalCity && flight.departureDate == date) {
            displayFlight(flight);
            found = true;
        }
    }

    if (!found) {
        cout << "No flights available for the given criteria." << endl;
    }

    inFile.close();
    userMenu();
}

// Function to book a flight (User)
void bookFlight() {
    int flightID;
    string passengerName;
    cout << "Enter the flight ID to book: ";
    cin >> flightID;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, passengerName);

    ifstream inFile("flights.txt");
    Flight flight;
    Ticket ticket;
    bool flightFound = false;

    while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
        >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
        if (flight.flightID == flightID && flight.seatsAvailable > 0) {
            flightFound = true;
            ticket.flightID = flightID;
            ticket.passengerName = passengerName;
            ticket.amountPaid = flight.price; // Assuming full price for simplicity

            // Make the payment
            makePayment(ticket);

            // Update flight data
            flight.seatsAvailable--;
            break;
        }
    }

    inFile.close();

    // Update the flight data in the file
    ofstream tempFile("temp.txt");
    inFile.open("flights.txt");

    while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
        >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
        if (flight.flightID == flightID) {
            // Update the seats available
            flight.seatsAvailable--;
        }
        tempFile << flight.flightID << " " << flight.flightName << " " << flight.departureCity << " "
            << flight.arrivalCity << " " << flight.departureDate << " " << flight.seatsAvailable << " "
            << flight.price << endl;
    }

    inFile.close();
    tempFile.close();
    remove("flights.txt");
    rename("temp.txt", "flights.txt");

    if (flightFound) {
        cout << "Flight booked successfully!" << endl;
    }
    else {
        cout << "Flight not found or fully booked!" << endl;
    }

    userMenu();
}

// Function to cancel a flight (User)
void cancelFlight() {
    int flightID;
    string passengerName;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, passengerName);
    cout << "Enter the flight ID to cancel: ";
    cin >> flightID;

    // Find the ticket in the booked tickets
    ifstream bookedFile("booked_tickets.txt");
    Ticket ticket;
    bool ticketFound = false;
    vector<Ticket> tickets;

    while (bookedFile >> ticket.flightID >> ticket.passengerName >> ticket.amountPaid) {
        if (ticket.flightID == flightID && ticket.passengerName == passengerName) {
            ticketFound = true;
            continue; // Skip the ticket to be canceled
        }
        tickets.push_back(ticket); // Keep the rest
    }
    bookedFile.close();

    // Rewrite the booked tickets file without the canceled ticket
    ofstream tempFile("temp_tickets.txt");
    for (const auto& t : tickets) {
        tempFile << t.flightID << " " << t.passengerName << " " << t.amountPaid << endl;
    }
    tempFile.close();
    remove("booked_tickets.txt");
    rename("temp_tickets.txt", "booked_tickets.txt");

    // If ticket found, update the flight data
    if (ticketFound) {
        // Update flight data
        ifstream inFile("flights.txt");
        Flight flight;
        bool flightUpdated = false;

        while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
            >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
            if (flight.flightID == flightID) {
                flightUpdated = true;
                flight.seatsAvailable++; // Increase available seats
                break;
            }
        }

        inFile.close();

        // Update the flight data in the file
        ofstream tempFile2("temp_flights.txt");
        inFile.open("flights.txt");

        while (inFile >> flight.flightID >> flight.flightName >> flight.departureCity >> flight.arrivalCity
            >> flight.departureDate >> flight.seatsAvailable >> flight.price) {
            if (flight.flightID == flightID) {
                flight.seatsAvailable++; // Increase available seats
            }
            tempFile2 << flight.flightID << " " << flight.flightName << " " << flight.departureCity << " "
                << flight.arrivalCity << " " << flight.departureDate << " " << flight.seatsAvailable << " "
                << flight.price << endl;
        }

        inFile.close();
        tempFile2.close();
        remove("flights.txt");
        rename("temp_flights.txt", "flights.txt");

        cout << "Flight canceled successfully! Your amount of " << ticket.amountPaid << " has been refunded." << endl;
    }
    else {
        cout << "Ticket not found!" << endl;
    }

    userMenu();
}

// Function to view booked flights (User)
void viewBookedFlights() {
    ifstream bookedFile("booked_tickets.txt");
    Ticket ticket;
    cout << "\nBooked Tickets:" << endl;
    while (bookedFile >> ticket.flightID >> ticket.passengerName >> ticket.amountPaid) {
        cout << "Flight ID: " << ticket.flightID << ", Passenger Name: " << ticket.passengerName
            << ", Amount Paid: " << ticket.amountPaid << endl;
    }

    bookedFile.close();
    userMenu();
}

// Function to make payment for a ticket
void makePayment(Ticket& ticket) {
    cout << "Processing payment of " << ticket.amountPaid << " for " << ticket.passengerName << endl;
    // Here you could implement actual payment logic (e.g., using a payment API)

    // Save the booked ticket to a file
    ofstream bookedFile("booked_tickets.txt", ios::app);
    bookedFile << ticket.flightID << " " << ticket.passengerName << " " << ticket.amountPaid << endl;
    bookedFile.close();

    cout << "Payment successful!" << endl;
}

int main() {
    mainMenu();
    return 0;
}
