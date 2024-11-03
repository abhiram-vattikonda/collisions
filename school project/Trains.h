#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Train {
protected:
    string trainName;
    int trainNumber;
    string departureTime;
    string arrivalTime;
    vector<string> classTypes;
    int basePrice;

public:
    Train(string name, int number, string depTime, string arrTime, int price)
        : trainName(name), trainNumber(number), departureTime(depTime), arrivalTime(arrTime), basePrice(price) {}

    virtual void displayClassOptions() {
        cout << "Available class types: " << endl;
        for (size_t i = 0; i < classTypes.size(); i++) {
            cout << i + 1 << ". " << classTypes[i] << endl;
        }
    }

    virtual int getPrice(int classIndex) {
        return basePrice;
    }

    string getTrainName() { return trainName; }
    string getDepartureTime() { return departureTime; }
    string getArrivalTime() { return arrivalTime; }
    vector<string> getClassTypes() { return classTypes; }

    void displayTrainInfo() {
        cout << "Train: " << trainName << " (" << trainNumber << ") " << endl;
        cout << "Departure: " << departureTime << ", Arrival: " << arrivalTime << endl;
    }
};

class VandeBharat : public Train {
public:
    VandeBharat() : Train("Vande Bharat Super Fast Express", 12456, "10:00", "15:30", 0) {
        classTypes = { "Executive", "Normal" };
    }

    void displayClassOptions() override {
        Train::displayClassOptions();
        cout << "Note: Meal options are free for all passengers (Veg/Non-Veg)." << endl;
    }

    int getPrice(int classIndex) override {
        if (classIndex == 1) return 2200;
        else if (classIndex == 2) return 1100;
        return 0;
    }
};

class RegularTrain : public Train {
public:
    RegularTrain(string name, int number, string depTime, string arrTime, int price)
        : Train(name, number, depTime, arrTime, price) {
        classTypes = { "1st AC", "2nd AC", "3rd AC", "Sleeper" };
    }

    int getPrice(int classIndex) override {
        if (classIndex == 1) return 3200;
        if (classIndex == 2) return 2100;
        if (classIndex == 3) return 1400;
        if (classIndex == 4) return 700;
        return 0;
    }
};