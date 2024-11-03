#pragma once
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Passenger {
public:
    string name;
    int day, month, year;
    int age;
    char gender;
    string berthPreference;
    bool mealOption;
    string mealType;
    bool insurance;
    float ticketPrice;
    string seatNumber = "";

    Passenger() {}

    void enterPassengerDetails(bool isVandeBharat) {
        cout << "Enter passenger name (no numbers): ";
        while (true) {
            cin >> ws;
            getline(cin, name);
            if (name.find_first_of("0123456789") != string::npos) {
                cout << "Invalid name. Please enter again (no numbers): ";
            }
            else break;
        }

        cout << "Enter date of birth (DD MM YYYY): ";
        while (true)
        {
            cin.clear();
            cin.ignore();
            cin >> day >> month >> year;
            if (!cin.fail() && 0 < day && day < 32 && 0 < month && month < 13 && year > 1900)
                break;
        }
        age = calculateAge();

        cout << "Enter gender (M/F): ";
        while (true)
        {
            cin.clear();
            cin.ignore(CHAR_MAX, '\n');
            cin >> gender;
            if (!cin.fail() && (gender == 'M' || gender == 'm' || gender == 'F' || gender == 'f'))
                break;
        }

        if (!isVandeBharat)
        {
            cout << "Enter berth/seat preference (lower/middle/top/side window): ";
            cin >> berthPreference;
        }

        if (!isVandeBharat) {
            cout << "Meal option? (1 for Yes, 0 for No): ";
            cin >> mealOption;
            if (mealOption) {
                cout << "Veg or Non-Veg: ";
                cin.ignore();
                getline(cin, mealType);
            }
            else {
                mealType = "None";
            }
        }
        else {
            mealOption = true;
            cout << "Meal options are free. Please choose Veg or Non-Veg: ";
            cin.ignore();
            getline(cin, mealType);
        }

        cout << "Do you want insurance? (1 for Yes, 0 for No): ";
        while (true)
        {
            cin.clear();
            
            cin >> insurance;
            if (!cin.fail())
                break;
            cin.ignore();
        }

    }

    void displayPassengerInfo(int passengerNumber) const {
        cout << "Passenger " << passengerNumber + 1 << ": " << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Berth Preference: " << berthPreference << endl;
        cout << "Meal: " << (mealOption ? mealType : "No meal") << endl;
        cout << "Insurance: " << (insurance ? "Yes" : "No") << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Ticket Price: " << ticketPrice << endl;
        cout << "----------------------------" << endl;
    }

    // Function to apply discounts based on age
    void applyAgeDiscount(int basePrice) {

        if (age > 65)   ticketPrice = basePrice * 0.75;

        else if (age < 6)   ticketPrice = basePrice * 0.2;

        else    ticketPrice = basePrice;

    }

private:
    int calculateAge() {
        time_t t = time(0);
        tm now;  // Declare tm structure
        localtime_s(&now, &t);  // Use localtime_s

        int currentYear = now.tm_year + 1900;
        int currentMonth = now.tm_mon + 1;
        int currentDay = now.tm_mday;

        int age = currentYear - year;
        if (currentMonth < month || (currentMonth == month && currentDay < day)) {
            age--;
        }
        return age;
    }


};