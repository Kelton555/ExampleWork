// This program was made for the midterm project of a C++ programming course

// Kelton
// [CLASS CODE HERE]
// October 16, 2024

#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// structure for holding a GameCharacter
// contains:
// the character name as a pointer to a cstring
// wins losses and draws as integers
// hours played as a double
struct GameCharacter {
    char* characterName;
    int wins;
    int losses;
    int draws;
    double hoursPlayed;
};

// input methods
int getIntegerInput(int, int);
double getDoubleInput(double);
char* getStringInput(int);

// menu method
int showMenu();

// character output methods
void printCharacter(GameCharacter*);
void printCharacters(GameCharacter**, int);
void printCharactersStats(GameCharacter**, int);

// GameCharacter object methods
GameCharacter* createNewGameCharacter(char*, int, int, int, double);
GameCharacter* inputCharacterFromUser();
void removeGameCharacter(GameCharacter*);

// GameCharacter array modification methods
void addCharacterToList(GameCharacter***, int*, GameCharacter*);
void removeCharacterFromList(GameCharacter***, int*, GameCharacter*);

// GameCharacter array sorting methods
void sortByNames(GameCharacter***, int);
void sortByWins(GameCharacter***, int);
void sortByLosses(GameCharacter***, int);
void sortByHours(GameCharacter***, int);

// GameCharacter array searching method
int searchCharacterByName(GameCharacter**, int, char*);

// Sorting helper method
void swap(GameCharacter**, GameCharacter**);

// main body of program
// creates a central array of game characters to store all entered characters
// then enters a menu-driven loop to allow the user to view, add, and remove data
int main() {
    GameCharacter** characterList = nullptr;
    int characterListLength = 0;

    // menu-driven loop
    int selection = 7;
    do {
        selection = showMenu();

        // take actions based on which menu option was selected
        switch(selection) {
            case 1: // add a character
                cout << endl;
                addCharacterToList(&characterList, &characterListLength, inputCharacterFromUser());
            break;
            case 2: // remove a character
                // check if there are any characters that can be removed
                if (characterList == nullptr || characterListLength == 0) {
                    cout << "There are no characters to remove.\n";
                } else {
                    cout << endl;
                    printCharacters(characterList, characterListLength);
                    cout << "\nCharacter to remove: ";
                    removeCharacterFromList(&characterList, &characterListLength, characterList[getIntegerInput(1, characterListLength) - 1]);
                }
            break;
            case 3: // sort characters
                cout << "\nHow would you like to sort?\n"
                     << "1. By name (A-Z)\n"
                     << "2. By wins (high-low)\n"
                     << "3. By losses (high-low)\n"
                     << "4. By time played (high-low)\n"
                     << "Selection: ";
                // run the correct sorting function based on user input
                switch(getIntegerInput(1, 4)) {
                    case 1: sortByNames(&characterList, characterListLength); break;
                    case 2: sortByWins(&characterList, characterListLength); break;
                    case 3: sortByLosses(&characterList, characterListLength); break;
                    case 4: sortByHours(&characterList, characterListLength); break;
                }
            break;
            case 4: { // search for a character
                // curly brackets needed because new variables will be declared
                cout << "\nEnter a character name to search for: ";
                
                char* characterName = getStringInput(100);
                int index = searchCharacterByName(characterList, characterListLength, characterName);

                delete[] characterName; // free the space from the string
                characterName = nullptr; // just for safety

                if (index == -1) {
                    cout << "No matching character found.\n";
                } else {
                    cout << "Character found as character #" << (index + 1) << ".\n";
                    printCharacter(characterList[index]);
                    cout << endl; // printCharacter does not print an endl
                }
            } 
            break;
            case 5: // display all characters
                // check if there are any characters to display
                if (characterList == nullptr || characterListLength == 0) {
                    cout << "There are no characters to display.\n";
                } else {
                    cout << endl;
                    printCharacters(characterList, characterListLength);
                }
            break;
            case 6: // display calculated stats
                // check if there are any characters to display
                if (characterList == nullptr || characterListLength == 0) {
                    cout << "There are no characters to display.\n";
                } else {
                    cout << endl;
                    printCharactersStats(characterList, characterListLength);
                }
            break;
            case 7: break; // exit program
        }
    } while (selection != 7);
    
    return 0;
}

// read an integer from input within the range min-max (inclusive)
// exits the program with an error if min > max (code 100)
int getIntegerInput(int min, int max) {
    if (min > max) {
        cout << "ERROR: getIntegerInput() called with min > max!";
        exit(100);
    }

    int input;

    // while input fails, or input is out of range, loop
    while (!(cin >> input) || input < min || max < input) {
        cout << "Invalid input. Try again. Enter an integer in the range [" << min << ":" << max << "]: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n'); //https://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer | there will always be a newline to catch the ignoring, as cin will hold execution until a newline is entered
    }
    cin.ignore(INT_MAX, '\n'); // keep cin clean

    return input;
}

// reads a double from input
double getDoubleInput(double min) {
    double input;

    // while input fails or is under min, loop
    while (!(cin >> input) || input < min) {
        cout << "Invalid input. Try again. Enter a double value above " << setprecision(1) << fixed << min << ": ";
        cin.clear();
        cin.ignore(INT_MAX, '\n'); 
    }
    cin.ignore(INT_MAX, '\n'); // keep cin clean

    return input;
}

// gets a cstring from input, up to maxLength chars
// the returned string will be sized down to only the length required to hold the input
char* getStringInput(int maxLength) {
    char* inputString = new char[maxLength + 1]; // add one for the \0
    cin.getline(inputString, maxLength + 1); // again, add one for the \0
    
    // if a fail is registered, that means that the string didn't fit, so we clear the failure and the buffer
    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    // to save memory in storage (though not in process), cstrings will be transferred to a new char* properly sized
    int inputStringLength;
    // loop through the entire string, remember that 1 was added to maxLength, so <= is the correct comparison
    for (int i = 0; i <= maxLength; i++) {
        // if we've reached the end
        if (inputString[i] == '\0') {
            inputStringLength = i + 1; // remember to account for the \0
        }
    }
    
    char* processedInputString = new char[inputStringLength];
    strcpy_s(processedInputString, inputStringLength, inputString); // CSTRING FUNCTION

    delete[] inputString;
    return processedInputString;
}

// shows the main menu of the program and returns the integer selection
int showMenu() {
    cout << "\nSelect an option:\n"
         << setw(4) << left << "1." << setw(25) << right << "Add a character" << endl
         << setw(4) << left << "2." << setw(25) << right << "Remove a character" << endl
         << setw(4) << left << "3." << setw(25) << right << "Sort characters" << endl
         << setw(4) << left << "4." << setw(25) << right << "Search for a character" << endl
         << setw(4) << left << "5." << setw(25) << right << "Display all characters" << endl
         << setw(4) << left << "6." << setw(25) << right << "Display calc'd stats" << endl
         << setw(4) << left << "7." << setw(25) << right << "Exit program" << endl
         << "Selection: ";

    return getIntegerInput(1, 7);
}

// prints the details of a single character to output, no newline or preface included
void printCharacter(GameCharacter* character) {
    cout << character->characterName << " - W:" << character->wins << " L:" << character->losses << " D:" << character->draws << " - Hours: " << setprecision(1) << fixed << character->hoursPlayed;
}

// prints details of all of the characters in the list to output
void printCharacters(GameCharacter** characterList, int length) {
    // loop through the entire list and print each character
    for (int i = 0; i < length; i++) {
        cout << (i+1) << ". ";
        printCharacter(characterList[i]);
        cout << endl;
    }
}

// prints all of the characters from the list with calculated stats rather than the input stats
void printCharactersStats(GameCharacter** characterList, int length) {
    // loop through the entire list and print each character with some calculated stats
    for (int i = 0; i < length; i++) {
        int matchesPlayed = characterList[i]->wins + characterList[i]->losses + characterList[i]->draws;
        cout << (i+1) << ". " << characterList[i]->characterName << " - Win Rate: " << setprecision(2) << fixed << (static_cast<double>(characterList[i]->wins) / matchesPlayed)
                      << " | Favorable Rate: " << (static_cast<double>(characterList[i]->wins + characterList[i]->draws) / matchesPlayed)
                      << " | Wins/Hour: " << (characterList[i]->wins / characterList[i]->hoursPlayed) << endl;
    }
}

// creates a new GameCharacter with the provided information and returns a pointer to it
GameCharacter* createNewGameCharacter(char* characterName, int wins, int losses, int draws, double hoursPlayed) {
    GameCharacter* newCharacter = new GameCharacter;

    newCharacter->characterName = characterName;
    newCharacter->wins = wins;
    newCharacter->losses = losses;
    newCharacter->draws = draws;
    newCharacter->hoursPlayed = hoursPlayed;

    return newCharacter;
}

// asks the user for all the input required to create a GameCharacter, then returns a pointer to a newly created GameCharacter
GameCharacter* inputCharacterFromUser() {
    const int MAX_NAME_LENGTH = 100;
    cout << "Enter the characters name, up to " << MAX_NAME_LENGTH << " characters: ";
    char* characterName = getStringInput(MAX_NAME_LENGTH); // the string will be freed when the character is removed from the central list
    cout << "Enter your wins with this character: ";
    int wins = getIntegerInput(0, INT_MAX);
    cout << "Enter your losses with this character: ";
    int losses = getIntegerInput(0, INT_MAX);
    cout << "Enter your draws with this character: ";
    int draws = getIntegerInput(0, INT_MAX);
    cout << "Enter your playtime with this character in hours: ";
    double hoursPlayed = getDoubleInput(0.0);

    return createNewGameCharacter(characterName, wins, losses, draws, hoursPlayed);
}

// replaces the GameCharacter* array pointed to by the first parameter with a new one that contains the newly added character
// updates the length int pointed to by the second parameter
// deletes the old array from memory before returning
void addCharacterToList(GameCharacter*** characterListPtr, int* characterListLengthPtr, GameCharacter* characterToAdd) {
    GameCharacter** newCharacterList = new GameCharacter*[(*characterListLengthPtr) + 1];

    // loop through the previous character list to copy each to the new list
    for (int i = 0; i < (*characterListLengthPtr); i++) {
        newCharacterList[i] = (*characterListPtr)[i];
    }

    // add the new character to the end of the list
    newCharacterList[*characterListLengthPtr] = characterToAdd;

    delete[] (*characterListPtr); // remove the old list
    *characterListPtr = newCharacterList; // and change it to the new one

    (*characterListLengthPtr)++; // update the array length
}

// replaces the GameCharacter* array pointed to by the first parameter with a new one that does not contain the character pointed to by the third parameter
// will replace it with a nullptr if the array length becomes zero from this operation
// updates the length int pointed to by the second parameter
// deletes the old array from memory before returning
// deletes the character pointed to by parameter three from memory before returning
void removeCharacterFromList(GameCharacter*** characterListPtr, int* characterListLengthPtr, GameCharacter* characterToRemove) {
    // if the list is only one element long, that means it will become zero elements long, so we can skip most of the processing
    if (*characterListLengthPtr == 1) {
        delete[] (*characterListPtr);
        removeGameCharacter(characterToRemove);
        *characterListPtr = nullptr;
        (*characterListLengthPtr)--;
    } else { // otherwise,
        GameCharacter** newCharacterList = new GameCharacter*[(*characterListLengthPtr) - 1];

        // loop through the previous character list to copy all but the removed element over
        int index = 0;
        for (int i = 0; i < (*characterListLengthPtr); i++) {
            // if it is not the element we want to remove, we copy it over and increment index
            if ((*characterListPtr)[i] != characterToRemove) {
                newCharacterList[index] = (*characterListPtr)[i];
                index++;
            }
        }

        delete[] (*characterListPtr); // remove the old list
        *characterListPtr = newCharacterList; // replace it with the new list

        removeGameCharacter(characterToRemove); // free the space from the removed character and its name string

        (*characterListLengthPtr)--; // update the array length
    }
}

// frees the space of a GameCharacter object
// frees both the string for the character name and the object itself
void removeGameCharacter(GameCharacter* character) {
    delete[] character->characterName;
    delete[] character;
}

// searches for a character in the given list by name, returns the index of the first match or -1 if not found
int searchCharacterByName(GameCharacter** characterList, int length, char* characterName) {
    int index = -1;

    // loop through the list of characters
    for (int i = 0; i < length; i++) {
        // check if the names match
        if (strcmp(characterList[i]->characterName, characterName) == 0) { // CSTRING FUNCTION
            index = i;
            break;
        }
    }

    return index;
}

// sorts a list of GameCharacter* by name (a-z) using selection sort
void sortByNames(GameCharacter*** characterListPtr, int length) {
    // loops from the first element to the second to last element in the array
    for (int i = 0; i < (length - 1); i++) {
        GameCharacter** minCharacter = (*characterListPtr + i); // pointer to track the minimum element so far
        // loop from the value after the current value (we do not need to check the current value, it is already stored) until the end of the array
        for (int j = i+1; j < length; j++) {
            // if the new value would come before the current value, replace the current value with the new value
            if (strcmp((*characterListPtr)[j]->characterName, (*minCharacter)->characterName) < 0) { // CSTRING FUNCTION
                minCharacter = (*characterListPtr + j);
            }
        }
        // swap the first unsorted element with the minimum element from the rest of the array
        swap((*characterListPtr + i), minCharacter);
    }
}

// sorts a list of GameCharacter* by wins high to low using selection sort
void sortByWins(GameCharacter*** characterListPtr, int length) {
    // loops from the first element to the second to last element in the array
    for (int i = 0; i < (length - 1); i++) {
        GameCharacter** maxCharacter = (*characterListPtr + i); // pointer to track the maximum element so far
        // loop from the value after the current value (we do not need to check the current value, it is already stored) until the end of the array
        for (int j = i+1; j < length; j++) {
            // if the new value should come before the current value, replace the current value with the new value
            if ((*characterListPtr)[j]->wins > (*maxCharacter)->wins) {
                maxCharacter = (*characterListPtr + j);
            }
        }
        // swap the first unsorted element with the maximum element from the rest of the array
        swap((*characterListPtr + i), maxCharacter);
    }
}

// sorts a list of GameCharacter* by losses high to low using selection sort
void sortByLosses(GameCharacter*** characterListPtr, int length) {
    // loops from the first element to the second to last element in the array
    for (int i = 0; i < (length - 1); i++) {
        GameCharacter** maxCharacter = (*characterListPtr + i); // pointer to track the maximum element so far
        // loop from the value after the current value (we do not need to check the current value, it is already stored) until the end of the array
        for (int j = i+1; j < length; j++) {
            // if the new value should come before the current value, replace the current value with the new value
            if ((*characterListPtr)[j]->losses > (*maxCharacter)->losses) {
                maxCharacter = (*characterListPtr + j);
            }
        }
        // swap the first unsorted element with the maximum element from the rest of the array
        swap((*characterListPtr + i), maxCharacter);
    }
}

// sorts a list of GameCharacter* by hours high to low using selection sort
void sortByHours(GameCharacter*** characterListPtr, int length) {
    // loops from the first element to the second to last element in the array
    for (int i = 0; i < (length - 1); i++) {
        GameCharacter** maxCharacter = (*characterListPtr + i); // pointer to track the maximum element so far
        // loop from the value after the current value (we do not need to check the current value, it is already stored) until the end of the array
        for (int j = i+1; j < length; j++) {
            // if the new value should come before the current value, replace the current value with the new value
            if ((*characterListPtr)[j]->hoursPlayed > (*maxCharacter)->hoursPlayed) {
                maxCharacter = (*characterListPtr + j);
            }
        }
        // swap the first unsorted element with the maximum element from the rest of the array
        swap((*characterListPtr + i), maxCharacter);
    }
}

// swaps two GameCharacter* in memory
// used for sorting the array
void swap(GameCharacter** char1, GameCharacter** char2) {
    GameCharacter* tmp = *char1;
    *char1 = *char2;
    *char2 = tmp;
}
