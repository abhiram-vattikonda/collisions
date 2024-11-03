
/*  Here, we are not including iosteam, vector, string, ctime libreries as they are already included in the "Trains.h" and "Passenger.h" libraries

*/


#include <ctime>
#include <iomanip> 
#include <fstream>

#include "Trains.h"
#include "Passenger.h"

using namespace std;


bool checkSourceDestination(string from, string to) {
    return from != to;
}

Train* selectTrain() {
    // Initializing all the normal trains
    vector<Train*> trains;
    trains.push_back(new VandeBharat());
    trains.push_back(new RegularTrain("Special Train", 4567, "09:00", "13:30", 0));
    trains.push_back(new RegularTrain("SF Train", 12637, "08:45", "14:00", 0));
    trains.push_back(new RegularTrain("Duronto Express", 22567, "11:30", "17:00", 0));
    trains.push_back(new RegularTrain("Eastern Express", 34219, "12:15", "18:30", 0));

    // Printing available trins
    cout << "Available Trains: " << endl;
    for (size_t i = 0; i < trains.size(); i++) {
        cout << i + 1 << ". " << trains[i]->getTrainName() << endl;
    }

    // Selecting which train we want
    int trainChoice;
    cout << "Select train by number: ";
    while (true)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> trainChoice;
        if (!cin.fail() && 0 < trainChoice && trainChoice <= trains.size())
            break;
    }
    

    return trains[trainChoice - 1];
}

void editOrDeletePassengers(vector<Passenger>& passengers, bool isVandeBharat) {
    int choice;
    do {
        // Asking if the user needs to change something at the end
        cout << "Do you want to (1) Edit or (2) Delete a passenger? (0 to finish): ";
        cin >> choice;
        if (choice == 1) {
            // To Edit
            int passengerIndex;
            cout << "Enter passenger number to edit (0 to exit): ";
            cin >> passengerIndex;
            if (passengerIndex == 0) break;
            passengerIndex--;
            passengers[passengerIndex].enterPassengerDetails(isVandeBharat);
        }

        else if (choice == 2) {
            // To delete
            int passengerIndex;
            cout << "Enter passenger number to delete (0 to exit): ";
            cin >> passengerIndex;
            if (passengerIndex == 0) break;
            passengers.erase(passengers.begin() + passengerIndex - 1);
        }
    } while (choice != 0);
}

string paymentMethod()
{
    // Prompt for payment method
    int paymentChoice;
    cout << "Select payment method:\n1. Card\n2. UPI\n3. Train Wallet\n4. Net Banking\nChoice: ";
    cin >> paymentChoice;

    string paymentMethod;
    switch (paymentChoice) {
    case 1: paymentMethod = "Card"; break;
    case 2: paymentMethod = "UPI"; break;
    case 3: paymentMethod = "Train Wallet"; break;
    case 4: paymentMethod = "Net Banking"; break;
    default: paymentMethod = "Unknown"; break;
    }

    cout << "\nPayment Method Selected: " << paymentMethod << endl;

    return paymentMethod;

}

int priceCalculationAndPrintResults(vector<Passenger> passengers)
{
    // Calculating the final price
    int totalPrice = 0;
    for (const auto& passenger : passengers) {
        totalPrice += passenger.ticketPrice;
    }

    // Adding gst
    double gstAmount = totalPrice * 0.09;
    totalPrice += gstAmount;
    cout << "Total ticket price (including 9% GST): " << endl;
    cout << fixed << setprecision(2) << totalPrice << endl;


    // Printing final results
    cout << "\nTicket Summary:" << endl;
    for (size_t i = 0; i < passengers.size(); i++) {
        passengers[i].displayPassengerInfo(i);
    }
    cout << "Total Price (including 9% GST): " << totalPrice << endl;

    return totalPrice;
}


vector<int> dateOfDeparture()
{
    // getting the current date
    time_t t = time(0);
    tm now;  // Declare tm structure
    localtime_s(&now, &t);  // Use localtime_s

    // getting departure date
    int day, month, year;
    cout << "Enter date of Departure (DD MM YYYY): ";
    while (true)
    {
        cin.clear();
        cin.ignore();
        cin >> day >> month >> year;
        if (!cin.fail() && 0 < day && day < 32 && 0 < month && month < 13 && year > 1900)
        {// Checking if valid date
            if (now.tm_year < year)   break;
            else if (now.tm_year == year && (now.tm_mon + 1) < month) break;
            else if (now.tm_year == year && (now.tm_mon + 1) == month && now.tm_mday <= day) break;
            else continue;
        }
    }

    return vector<int>{ day, month, year};
    
}


int selectingClass(Train* selectedTrain)
{
    // Selecting which class
    selectedTrain->displayClassOptions();
    int classChoice;
    cout << "Select class type: ";
    while (true)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> classChoice;
        if (!cin.fail() && 0 < classChoice && classChoice <= selectedTrain->getClassTypes().size())
            break;
    }

    return classChoice;
}


int numberOfPassengers()
{
    // Selecting number of passengers
    int numPassengers;
    cout << endl << "Enter number of passengers: ";
    while (true)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> numPassengers;
        if (!cin.fail() && 0 < numPassengers)
            break;
    }

    return numPassengers;
}

vector<Passenger> initializePassengers(Train* selectedTrain, int numPassengers, int classChoice, bool isVandeBharat)
{
    // Initializing passengers
    vector<Passenger> passengers(numPassengers);

    int randNum = rand() % 20;// Seat numbers from 0 to 49
    for (int i = 0; i < numPassengers; i++) {

        cout << endl << "Enter details for Passenger " << i + 1 << ": " << endl;
        passengers[i].enterPassengerDetails(isVandeBharat);
        int basePrice = selectedTrain->getPrice(classChoice);
        passengers[i].applyAgeDiscount(basePrice);
        switch (classChoice)
        {// Seat Arraingment
            case 1:
                passengers[i].seatNumber.append("H-" + to_string(randNum + i));
                break;

            case 2:
                passengers[i].seatNumber.append("A-" + to_string(randNum + i));
                break;

            case 3:
                passengers[i].seatNumber.append("B-" + to_string(randNum + i));
                break;

            case 4:
                passengers[i].seatNumber.append("S-" + to_string(randNum + i));
                break;

            default:
                break;
        }
            
            
        if (!isVandeBharat && passengers[i].mealOption) {
            passengers[i].ticketPrice += 200;
        }
    }

    return passengers;
}


void printingToFile(Train* selectedTrain, vector<Passenger> passengers, vector<int> departuredate, string payMethod, string from, string to, int classChoice, int totalPrice)
{
    // Generate PDF or print summary to file
    ofstream ticketFile("TicketSummary.txt");
    if (ticketFile.is_open()) {
        // Printing train info
        ticketFile << "Train Reservation Ticket Summary\n\n";
        ticketFile << "Departure: " << from << ", Destination: " << to << "\n";
        ticketFile << "Date: " << departuredate[0] << "/" << departuredate[1] << "/" << departuredate[2] << "\n";
        ticketFile << "Train: " << selectedTrain->getTrainName() << "\n";
        ticketFile << "Class Type: " << classChoice << "\n";
        ticketFile << "Departure: " << selectedTrain->getDepartureTime() << ", Arrival: " << selectedTrain->getArrivalTime() << "\n\n";
        ticketFile << "Passengers:\n";

        // Printing passenger info
        for (size_t i = 0; i < passengers.size(); i++) {
            ticketFile << "Passenger " << i + 1 << endl;
            ticketFile << "Name: " << passengers[i].name << endl;
            ticketFile << "Age: " << passengers[i].age << endl;
            ticketFile << "Gender: " << passengers[i].gender << endl;
            ticketFile << "Berth Preference: " << passengers[i].berthPreference << endl;
            ticketFile << "Meal: " << (passengers[i].mealOption ? passengers[i].mealType : "No meal") << endl;
            ticketFile << "Insurance: " << (passengers[i].insurance ? "Yes" : "No") << endl;
            ticketFile << "Ticket Price: " << passengers[i].ticketPrice << endl << endl;
        }

        // Printing final price
        ticketFile << "Total Price (including 9% GST): " << totalPrice << "\n";
        ticketFile << "Payment Method: " << payMethod << "\n";
        ticketFile.close();
        cout << "Ticket Summary saved to TicketSummary.txt." << endl;
    }
    else {
        cout << "Error generating ticket summary file." << endl;
    }
}




int main() {

    // Getting the departure and destination
    string from, to;
    cout << "Enter departure: ";
    getline(cin, from);
    cout << "Enter destination: ";
    getline(cin, to);
    while (!checkSourceDestination(from, to)) {
        // Checking if both are same
        cout << endl<<  "Source and destination cannot be the same. Please re-enter: ";
        cin >> from >> to;
    }

    // Getting date of departure
    vector<int> departuredate(3);
    departuredate = dateOfDeparture();
    cout << endl;


    // Selecting the train you want to travel on
    Train* selectedTrain = selectTrain();
    bool isVandeBharat = selectedTrain->getTrainName() == "Vande Bharat Super Fast Express";
    cout << endl;

    // Choosing the class
    int classChoice = selectingClass(selectedTrain);

    // Selecting number of passengers
    int numPassengers = numberOfPassengers();
    

    // Initializing passengers
    vector<Passenger> passengers(numPassengers);
    passengers = initializePassengers(selectedTrain, numPassengers, classChoice, isVandeBharat);
    
    // Option to Edit or Delete the passengers
    editOrDeletePassengers(passengers, isVandeBharat);


    // Calculating total price and Displaying the final result in consoule
    int totalPrice = priceCalculationAndPrintResults(passengers);

    string payMethod = paymentMethod();


    // Generate PDF or print summary to file
    printingToFile(selectedTrain, passengers, departuredate, payMethod, from, to, classChoice, totalPrice);

    delete selectedTrain; // Free dynamically allocated memory
    return 0;
}