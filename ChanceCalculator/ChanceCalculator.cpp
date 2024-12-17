// Kelton
// [CLASS CODE HERE]
// November 28, 2024
// Function comments added 12/8/2024
// Modified 12/10/24

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <filesystem>

#include "ChanceEvent.h"
#include "DropChanceEvent.h"
#include "TimeChanceEvent.h"

using namespace std;

int getUserIntInRange(int, int);
double getUserDoubleInRange(double, double);

double getUserChance();

double getUserDouble();
string getUserLine();

template<class T> void printVector(const vector<T>&);

void loadFile(vector<DropChanceEvent>&, vector<TimeChanceEvent>&);
void saveFile(vector<DropChanceEvent>&, vector<TimeChanceEvent>&);

int main() {
    vector<DropChanceEvent> dropChanceList;
    vector<TimeChanceEvent> timeChanceList;

    if (filesystem::exists("ChanceData.bin")) { // if file already exists, offer to load data on program start
        cout << "Program data detected. Would you like to load it?\n"
             << "1. Yes\n"
             << "2. No\n"
             << "Selection: ";
        if (getUserIntInRange(1,2) == 1) {
            loadFile(dropChanceList, timeChanceList);
        }
    }

    int userMainInput;
    do { // main loop
        cout << "\nMain Menu:\n"
             << "1. List all events\n"
             << "2. List all of a type of event\n"
             << "3. Find event by drop name\n"
             << "4. Create new event\n"
             << "5. Remove event\n"
             << "6. Calculate stats about event\n"
             << "7. Load events from file\n"
             << "8. Save events to file\n"
             << "9. Exit program\n"
             << "Selection: ";
        userMainInput = getUserIntInRange(1,9);

        switch(userMainInput) {
            case 1: // list all
                if (dropChanceList.size() > 0) { // if it's not empty
                    cout << "Drop Chance Events:\n";
                    printVector(dropChanceList);
                } else {
                    cout << "There are no Drop Chance Events.\n";
                }
                if (timeChanceList.size() > 0) {
                    cout << "Time Chance Events:\n";
                    printVector(timeChanceList);
                } else {
                    cout << "There are no Time Chance Events.\n";
                }
            break;
            case 2: // list of type
                cout << "Which list?\n"
                     << "1. Drop Chances\n"
                     << "2. Time Chances\n"
                     << "Selection: ";
                switch(getUserIntInRange(1,2)) {
                    case 1:
                        if (dropChanceList.size() > 0) {
                            cout << "Drop Chance Events:\n";
                            printVector(dropChanceList);
                        } else {
                            cout << "There are no Drop Chance Events.\n";
                        }
                    break;
                    case 2:
                        if (timeChanceList.size() > 0) {
                            cout << "Time Chance Events:\n";
                            printVector(timeChanceList);
                        } else {
                            cout << "There are no Time Chance Events.\n";
                        }
                    break;
                }
            break;
            case 3: {// find by drop name
                cout << "Enter result to search for: ";
                string inputDropName = getUserLine();
                int index = -1;
                // search drop chance list
                for (int i = 0; i < dropChanceList.size(); i++) {
                    if (dropChanceList[i].getName() == inputDropName) {
                        index = i;
                        break;
                    }
                }
                if (index != -1) { // found in drop chance list
                    cout << "Found at index " << index << " in the Drop Chance List:\n"
                         << dropChanceList[index] << endl;
                } else { // if not found in the drop chance list
                    // search time chance list
                    for (int i = 0; i < timeChanceList.size(); i++) {
                        if (timeChanceList[i].getName() == inputDropName) {
                            index = i;
                            break;
                        }
                    }
                    if (index != -1) { // found in time chance list
                        cout << "Found at index " << index << " in the Time Chance List:\n"
                             << timeChanceList[index] << endl;
                    }
                }

                if (index == -1) {
                    cout << "That drop wasn't found in either list.\n";
                }
            } break;
            case 4: // create event
                cout << "What type of chance?\n"
                     << "1. Drop Chance\n"
                     << "2. Time Based Chance\n"
                     << "Selection: ";
                switch(getUserIntInRange(1,2)) {
                    case 1: { // drop chance event
                        cout << "Enter the item name: ";
                        string userItemName = getUserLine();
                        cout << "Enter the percentage chance for it to drop: ";
                        double userChance = getUserChance();
                        cout << "Enter what the item drops from: ";
                        string userItemDropper = getUserLine();
                        DropChanceEvent newEvent(userChance, userItemName, userItemDropper);

                        dropChanceList.push_back(newEvent); // add drop event to list
                    } break;
                    case 2: { // time based event
                        cout << "Enter the item name: ";
                        string userItemName = getUserLine();
                        cout << "Enter the percentage chance for it to drop per attempt: ";
                        double userChance = getUserChance();
                        TimeChanceEvent newEvent(userChance, userItemName, 1);
                        cout << "How would you like to describe events per second?\n"
                             << "1. Events per second\n"
                             << "2. Events per minute\n"
                             << "3. Events per hour\n"
                             << "4. Seconds per event\n"
                             << "5. Minutes per event\n"
                             << "6. Hours per event\n"
                             << "Selection: ";
                        switch(getUserIntInRange(1,6)) {
                            case 1:  // events per second
                                cout << "Enter events per second: "; 
                                newEvent.setEventsPerSecond(getUserDoubleInRange(0.01,999999999.99)); 
                            break;
                            case 2: // events per minute
                                cout << "Enter events per minute: ";
                                newEvent.setEventsPerMinute(getUserDoubleInRange(0.01,999999999.99)); 
                            break;
                            case 3: // events per hour
                                cout << "Enter events per hour: ";
                                newEvent.setEventsPerHour(getUserDoubleInRange(0.01,999999999.99)); 
                            break;
                            case 4: // seconds per event
                                cout << "Enter seconds per event: ";
                                newEvent.setSecondsPerEvent(getUserDoubleInRange(0.01,999999999.99)); 
                            break;
                            case 5: // minutes per event
                                cout << "Enter minutes per event: ";
                                newEvent.setMinutesPerEvent(getUserDoubleInRange(0.01,999999999.99)); 
                            break;
                            case 6: // hours per event
                                cout << "Enter hours per event: ";
                                newEvent.setHoursPerEvent(getUserDoubleInRange(0.01,999999999.99)); 
                            break;
                        }
                        timeChanceList.push_back(newEvent); // add time event to list
                    } break;
                }
            break;
            case 5: // remove event
                cout << "Which list would you like to remove from?\n"
                     << "1. Drop Event\n"
                     << "2. Time Event\n"
                     << "3. Cancel\n"
                     << "Selection: ";
                switch(getUserIntInRange(1,3)) {
                    case 1: // drop event list
                        if (dropChanceList.size() == 0) {
                            cout << "No events available.\n";
                            break;
                        }
                        cout << "Select an event:\n";
                        printVector(dropChanceList);
                        cout << "Selection: ";
                        dropChanceList.erase( // find the element to erase by adding the user selection to the starting iterator
                            dropChanceList.begin() + getUserIntInRange(1,dropChanceList.size()) - 1
                        ); // then subtracting 1 because the user is presented with a 1 indexed list
                    break;
                    case 2: // time event list
                        if (timeChanceList.size() == 0) {
                            cout << "No events available.\n";
                            break;
                        }
                        cout << "Select an event:\n";
                        printVector(timeChanceList);
                        cout << "Selection: ";
                        timeChanceList.erase( // find the element to erase by adding the user selection to the starting iterator
                            timeChanceList.begin() + getUserIntInRange(1,timeChanceList.size()) - 1
                        ); // then subtracting 1 because the user is presented with a 1 indexed list
                    break;
                    case 3: break; // cancel
                }
            break;
            case 6: { // calculate about event
                ChanceEvent* selectedEvent = nullptr; // pointer of parent ChanceEvent type to share code after event selection
                cout << "Would you like to calculate about a drop or time based event?\n"
                     << "1. Drop Event\n"
                     << "2. Time Event\n"
                     << "Selection: ";
                switch(getUserIntInRange(1,2)) {
                    case 1: { // drop event
                        if (dropChanceList.size() == 0) {
                            cout << "No events available.\n";
                            break;
                        }
                        cout << "Select an event:\n";
                        printVector(dropChanceList);
                        cout << "Selection: ";
                        selectedEvent = &(dropChanceList[getUserIntInRange(1,dropChanceList.size()) - 1]);
                    } break;
                    case 2: { // time based event
                        if (timeChanceList.size() == 0) {
                            cout << "No events available.\n";
                            break;
                        }
                        cout << "Select an event:\n";
                        printVector(timeChanceList);
                        cout << "Selection: ";
                        selectedEvent = &(timeChanceList[getUserIntInRange(1,timeChanceList.size()) - 1]);
                    } break;
                }

                if (selectedEvent == nullptr) { // simple error checking, don't want to accidentally do anything with a null pointer
                    break;
                }

                cout << "What would you like to see?\n"
                     << "1. Drop chance\n"
                     << "2. Calculate chance given some number of events\n"
                     << "3. Calculate events to achieve a given chance\n"
                     << "Selection: ";
                switch(getUserIntInRange(1,3)) { // as the display methods are listed (though fully virtual) in ChanceEvent, they can be called from a ChanceEvent pointer (and it will point to the correct method depending on the derived type)
                    case 1: selectedEvent->displayChance(); break; // drop chance
                    case 2: // calculate chance from events
                        cout << "Enter how many times the event has occurred: ";
                        selectedEvent->displayChanceFromActions(getUserIntInRange(1,INT_MAX));
                    break;
                    case 3: // calculate events from chance
                        cout << "Enter what chance you'd like to achieve (percentage): ";
                        selectedEvent->displayActionsFromChance(getUserChance());
                    break;
                }
            } break;
            case 7: // load from file
                loadFile(dropChanceList, timeChanceList);
            break;
            case 8: // save to file
                saveFile(dropChanceList, timeChanceList);
            break;
            case 9: // exit program
                cout << "Would you like to save to file before exiting?\n"
                     << "1. Yes\n"
                     << "2. No\n"
                     << "Selection: ";
                if (getUserIntInRange(1,2) == 1) { // if user selected yes, then save
                    saveFile(dropChanceList, timeChanceList);
                }
            break; 
        }
    } while (userMainInput != 9); // loop while user input != quit

    return 0;
}

// intakes an integer from the user in the range [low:high]
int getUserIntInRange(int low, int high) {
    int input;
    cin >> input;
    while (cin.fail() || input < low || high < input) {
        cout << "Please enter an integer between [" << low << ":" << high << "]: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> input;
    }
    cin.ignore(INT_MAX, '\n'); // clean newline from cin
    return input;
}

// intakes a double from the user in the range [low:high]
double getUserDoubleInRange(double low, double high) {
    double input;
    cin >> input;
    while (cin.fail() || input < low || high < input) {
        cout << "Please enter a number between [" << setprecision(2) << fixed << low << ":" << high << "]: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> input;
    }
    cin.ignore(INT_MAX, '\n'); // clean newline from cin
    return input;
}

// intakes a double from the user as a percentage, then returns a normalized value clamped to the valid range [0.0001:0.9999]
double getUserChance() {
    double chance = getUserDouble()/100;
    ChanceEvent::clampChance(chance);
    return chance;
}

// intakes a double from the user with no range checks
double getUserDouble() {
    double input;
    cin >> input;
    while (cin.fail()) {
        cout << "Please enter a number: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> input;
    }
    cin.ignore(INT_MAX, '\n'); // clean newline from cin
    return input;
}

// intakes a string line from the user using getline()
string getUserLine() {
    string input;
    getline(cin, input);
    while (cin.fail()) {
        cout << "Please enter a string: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        getline(cin, input);
    }
    return input;
}

// prints the contents of a vector to cout using << operator
// the contents of any vector passed should have a valid << operator that allows for chaining
template<class T> void printVector(const vector<T>& vect) {
    for (int i = 0; i < vect.size(); i++) {
        cout << i + 1 << ". " << vect[i] << endl;
    }
}

// loads data from the preset filename (ChanceData.bin) into the provided vectors
// only loads premade binary data, data must have been saved into the file using saveFile() before this will work properly
// will remove all pre-existing data from vectors if file is opened successfully
void loadFile(vector<DropChanceEvent>& dropChanceList, vector<TimeChanceEvent>& timeChanceList) {
    fstream file;

    file.open("ChanceData.bin", ios::in | ios::binary);

    if (file.is_open()) {
        // clear vectors before loading new data
        dropChanceList.clear();
        timeChanceList.clear();

        file.seekg(0, ios::beg); // just for safety

        bool safe = true;
        char chanceType;
        file.read(&chanceType, 1); // read in the type of chance
        while (!file.eof() && safe) {
            switch(chanceType) {
                case 'D': { // drop chance
                    DropChanceEvent event;
                    file.read(reinterpret_cast<char *>(&event), sizeof(event));
                    dropChanceList.push_back(event);
                } break;
                case 'T': { // time chance
                    TimeChanceEvent event;
                    file.read(reinterpret_cast<char *>(&event), sizeof(event));
                    timeChanceList.push_back(event);
                } break;
                default: 
                    cout << "Bad data in file! Aborting remainder of load.\n";
                    safe = false; // this breaks the upper loop, file will be closed later
                break;
            }

            file.read(&chanceType, 1); // read in the type of chance, here to break loop when end is reached
        }
    } else {
        cout << "Failed to open file! Aborting load.\n";
    }

    file.close();
}

// saves data from vectors into file with predetermined name (ChanceData.bin)
// saved in a specific format to be loaded by loadFile()
void saveFile(vector<DropChanceEvent>& dropChanceList, vector<TimeChanceEvent>& timeChanceList) {
    fstream file;
    file.open("ChanceData.bin", ios::out | ios::binary | ios::trunc);
    
    if (file.is_open()) {
        char chanceType = 'U'; // undefined

        chanceType = 'D'; // drop chance
        for (int i = 0; i < dropChanceList.size(); i++) {
            file.write(&chanceType, 1);
            file.write(reinterpret_cast<char *>(&(dropChanceList[i])), sizeof(dropChanceList[i]));
        }   

        chanceType = 'T'; // time chance
        for (int i = 0; i < timeChanceList.size(); i++) {
            file.write(&chanceType, 1);
            file.write(reinterpret_cast<char *>(&(timeChanceList[i])), sizeof(timeChanceList[i]));
        }
    } else {
        cout << "Failed to open file! Aborting save.\n";
    }

    file.close();
}
