// This program was made for the final project of an introductory programming course.

// Kelton
// Timeline (dates marked with a "~" added retrospectively from memory)
// Creation: 4/20/2024
// Word Associating Started and Implemented: ~4/21/2024
// Equations Started and Implemented: ~4/24/2024
// File Handling Started and Implemented: 4/29/2024
// Completion: 4/30/2024
// WordAssociation.cpp

// This program has two functions:
// 1. Allow user to associate strings with one another (input 1 string, get back its associated string, or a message stating that it is not associated if there is no association).
// 2. Allow user to define mathematical equations that can be run. These equations can use variables that the user will be prompted to fill out.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> // used by referencing https://cplusplus.com/reference/sstream/stringstream/stringstream/

using namespace std;

void removeIndex(vector<int>&, int);
void removeIndex(vector<string>&, int);
void removeIndex(vector<vector<string>>&, int);

void readAllStrings(istream&, vector<string>&);
void crawlForVariables(vector<string>&, string);

string inputLine(string);

vector<double> getVariablesForEquation(vector<string>);

double evaluateEquation(const string[], int, string);
double evaluateEquation(const string[], int, vector<string>, string);
double getNumberByString(string);
double getNumberByString(string, vector<string>, vector<double>);
double performOperation(const string[], int, double, string, double);

int presentMenu(const string[], int);
int presentDataDeletionMenu(vector<vector<string>>, vector<string>, vector<int>, int);
int presentEquationSelectionMenu(vector<vector<string>>, vector<string>, vector<int>, int);
int matchWord(vector<vector<string>>, vector<int>, string);
int getOperationID(const string[], int);

int getMenuInput();

bool isValidEquation(vector<string>, string, const string[], int);
bool isValidOperation(const string[], int, string);

int main() {
    // Load file menu (startup menu)
    const int MENU_LOAD_YES = 1;
    const int MENU_LOAD_NO = 2;

    const int MENU_LOAD_STRING_COUNT = 3;
    const string MENU_LOAD[MENU_LOAD_STRING_COUNT] = {"Would you like to load data from an existing file?", "Yes", "No"}; //0 is intro, 1 is choice 1, etc.

    // Main menu
    const int MENU_MAIN_ASSOCIATIONS = 1;
    const int MENU_MAIN_EQUATIONS = 2;
    const int MENU_MAIN_NEW_ASSOCIATION = 3;
    const int MENU_MAIN_NEW_EQUATION = 4;
    const int MENU_MAIN_REMOVE_ASSOCIATION = 5;
    const int MENU_MAIN_REMOVE_EQUATION = 6;
    const int MENU_MAIN_SAVE_EXIT = 7;
    const int MENU_MAIN_EXIT = 8;

    const int MENU_MAIN_STRING_COUNT = 9;
    const string MENU_MAIN[MENU_MAIN_STRING_COUNT] = {"Select a choice from the options below:", "Evaluate a string for associations", "Use an equation", "Make a new association", "Make a new equation", "Remove an association", "Remove an equation", "Save and exit", "Exit without saving"};

    // Association Type choice menu
    const int MENU_ASSOCIATION_TYPE_SINGULAR = 1;
    const int MENU_ASSOCIATION_TYPE_PLURAL = 2;
    
    const int MENU_ASSOCIATION_STRING_COUNT = 3;
    const string MENU_ASSOCIATION[MENU_ASSOCIATION_STRING_COUNT] = {"Which type of association would you like to create?", "Singular (Can have spaces)", "Multiple (Can NOT have spaces)"};

    // and now we're done defining menu stuff
    const int DATA_TYPE_ASSOCIATION = 0;
    const int DATA_TYPE_EQUATION = 1;

    const int OPERATION_COUNT = 8;
    const string OPERATIONS[] = {"+", "-", "*", "/", "%", "^", "RT", "LG"};

    vector<int> dataTypes;
    vector<vector<string>> wordAssociations;
    vector<string> associatedWords;

    if (presentMenu(MENU_LOAD, MENU_LOAD_STRING_COUNT) == MENU_LOAD_YES) {
        ifstream inputFileStream;

        cout << endl; // formatting
        do { // designed using concepts from https://cplusplus.com/forum/beginner/6033/
            string fileName = inputLine("Enter filename to load (including extension): ");
            inputFileStream.open(fileName);
        } while (!inputFileStream.is_open()); // loop while there is not a file open

        bool loadSuccess = true;

        int i;
        while (inputFileStream >> i) { // i will be the number of lines to read for vector<vector<string>>
            inputFileStream.ignore(); // clear the newline left behind

            // load the variable amount of strings first
            vector<string> loadedStrings;
            for (int j = 0; j < i; j++) {
                string inputString;
                getline(inputFileStream, inputString);
                loadedStrings.push_back(inputString);
            }

            // next we load the singular string of data
            string associated;
            getline(inputFileStream, associated);

            // finally, we load the dataType
            int dataType;
            if (!(inputFileStream >> dataType)) { // if it fails to read into dataType
                loadSuccess = false;
                break; // this just saves a bit of execution type because all loaded data will be thrown out in the event of an error anyways
            }

            // we'll add a sanity check that the dataType is valid
            if (!(DATA_TYPE_ASSOCIATION <= dataType && dataType <= DATA_TYPE_EQUATION)) { // if dataType is not valid
                loadSuccess = false;
                break; // this just saves a bit of execution type because all loaded data will be thrown out in the event of an error anyways
            }

            // and we'll check that equations are valid
            if (dataType == DATA_TYPE_EQUATION) {
                if (!isValidEquation(loadedStrings, associated, OPERATIONS, OPERATION_COUNT)) { // if not valid
                    loadSuccess = false;
                    break; // just save a bit of execution time, all data will be wiped anyways
                }
            }

            wordAssociations.push_back(loadedStrings);
            associatedWords.push_back(associated);
            dataTypes.push_back(dataType);
        }

        if (!inputFileStream.eof()) { // if we've reached this point, it means the >> into an int failed
            loadSuccess = false;      // if the end of file has not been reached, something went wrong somewhere
        }

        if (!loadSuccess) { // if the load failed
            cout << "Failed while loading file; no data has been loaded.\n";
            wordAssociations.clear();
            associatedWords.clear();
            dataTypes.clear();
        }

        inputFileStream.close();
    }

    int choice;
    do {
        choice = presentMenu(MENU_MAIN, MENU_MAIN_STRING_COUNT);
        switch(choice) { // every case will be given its own scope to avoid issues
            case MENU_MAIN_ASSOCIATIONS: {
                int index = matchWord(wordAssociations, dataTypes, inputLine("\nEnter string to lookup (spaces allowed): "));

                if (index > -1) { // it found a match
                    cout << "Your string is associated with the string: " << associatedWords[index] << endl;
                } else {
                    cout << "Your string is not associated with any other string.\n";
                }
            } break;
            case MENU_MAIN_EQUATIONS: {
                int equationIndex = presentEquationSelectionMenu(wordAssociations, associatedWords, dataTypes, DATA_TYPE_EQUATION);

                if (equationIndex > -1) {
                    if (isValidEquation(wordAssociations[equationIndex], associatedWords[equationIndex], OPERATIONS, OPERATION_COUNT)) {
                        if (wordAssociations[equationIndex].size() > 1) { // if there are variables
                            double solution = evaluateEquation(OPERATIONS, OPERATION_COUNT, wordAssociations[equationIndex], associatedWords[equationIndex]);

                            if (!isnan(solution)) {
                                cout << "\nThe equation evaluated to: " << solution << endl;
                            } else {
                                cout << "\nThe equation could not be evaluated.\n";
                            }
                        } else {
                            double solution = evaluateEquation(OPERATIONS, OPERATION_COUNT, associatedWords[equationIndex]);

                            if (!isnan(solution)) {
                                cout << "\nThe equation evaluated to: " << solution << endl;
                            } else {
                                cout << "\nThe equation could not be evaluated.\n";
                            }
                        }
                    } else {
                        cout << "\nThe selected equation is invalid.\n";
                    }    
                } else {
                    cout << "\nThere are no equations to display.\n";
                }
            } break;
            case MENU_MAIN_NEW_ASSOCIATION: {
                int typeChoice = presentMenu(MENU_ASSOCIATION, MENU_ASSOCIATION_STRING_COUNT); // input validation handled by function; no need to account for exiting this menu either

                vector<string> wordsToAssociate;
                string associateTo;

                switch(typeChoice) {
                    case MENU_ASSOCIATION_TYPE_SINGULAR:
                        wordsToAssociate.push_back(inputLine("\nEnter the string that should be associated with another string (spaces allowed): "));
                        associateTo = inputLine("Enter the string to associate the previous string with (spaces allowed): ");
                    break;
                    case MENU_ASSOCIATION_TYPE_PLURAL:
                        stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
                        ss.str(inputLine("Enter the string(s) you would like associated with another string, separated by spaces. Press enter when done: ")); // https://cplusplus.com/reference/sstream/stringstream/str/
                        readAllStrings(ss, wordsToAssociate); // will directly fill in wordsToAssociate
                        associateTo = inputLine("Enter the string to associate the previous string(s) with (spaces allowed): ");
                    break;
                }

                dataTypes.push_back(DATA_TYPE_ASSOCIATION);
                wordAssociations.push_back(wordsToAssociate);
                associatedWords.push_back(associateTo);
            } break;
            case MENU_MAIN_NEW_EQUATION: {
                vector<string> metadata;

                metadata.push_back(inputLine("Enter a name for the equation: "));

                string equation = inputLine("Enter an equation. You can use operators +, -, *, /, %, ^, RT, LG. The equation must start and end with a number or variable. Any undefined, non-numerical terms will be treated as variables. Separate your arguments with spaces: ");
                crawlForVariables(metadata, equation);

                if (isValidEquation(metadata, equation, OPERATIONS, OPERATION_COUNT)) {
                    dataTypes.push_back(DATA_TYPE_EQUATION);
                    wordAssociations.push_back(metadata);
                    associatedWords.push_back(equation);
                } else {
                    cout << "Invalid equation. Equation was not stored.\n";
                }
            } break;
            case MENU_MAIN_REMOVE_ASSOCIATION: {
                int indexToRemove = presentDataDeletionMenu(wordAssociations, associatedWords, dataTypes, DATA_TYPE_ASSOCIATION);

                if (indexToRemove > -1) { // it exists
                    removeIndex(dataTypes, indexToRemove);
                    removeIndex(wordAssociations, indexToRemove);
                    removeIndex(associatedWords, indexToRemove);
                } else {
                    cout << "\nThere are no word associations to remove.\n";
                }
            } break;
            case MENU_MAIN_REMOVE_EQUATION: {
                int indexToRemove = presentDataDeletionMenu(wordAssociations, associatedWords, dataTypes, DATA_TYPE_EQUATION);

                if (indexToRemove > -1) { // it exists
                    removeIndex(dataTypes, indexToRemove);
                    removeIndex(wordAssociations, indexToRemove);
                    removeIndex(associatedWords, indexToRemove);
                } else {
                    cout << "\nThere are no equations to remove.\n";
                }
            } break;
            case MENU_MAIN_SAVE_EXIT: {
                ofstream outputFileStream;

                do { // designed using concepts from https://cplusplus.com/forum/beginner/6033/
                    string fileName = inputLine("Enter filename to save to (including extension): ");
                    outputFileStream.open(fileName);
                } while (!outputFileStream.is_open()); // loop while there is not a file open

                for (int i = 0; i < wordAssociations.size(); i++) {
                    // first, write the amount of strings
                    outputFileStream << wordAssociations[i].size() << endl;

                    // next, loop through the strings to save
                    for (int j = 0; j < wordAssociations[i].size(); j++) {
                        outputFileStream << wordAssociations[i][j] << endl;
                    }

                    // next, a singular string per object
                    outputFileStream << associatedWords[i] << endl;

                    // finally, the datatype
                    outputFileStream << dataTypes[i];

                    // only add a newline if it's not the final object
                    if (i + 1 < wordAssociations.size()) {
                        outputFileStream << endl;
                    }
                }

                outputFileStream.close();
            } break; 
            case MENU_MAIN_EXIT: break; // except for this case, it doesn't get its own scope because it does nothing
        }
    } while (choice != MENU_MAIN_SAVE_EXIT && choice != MENU_MAIN_EXIT);

    return 0;
}

int presentMenu(const string choiceArray[], int arrayLength) {
    int selection = 0;
    do {
        cout << endl << choiceArray[0] << endl; // print the intro string

        for (int i = 1; i < arrayLength; i++) { // print all the choices
            cout << i << ". " << choiceArray[i] << endl;
        }

        cout << "Choice: ";
        selection = getMenuInput(); // removed cin >>, replaced with a function using getline to remove infinite looping bugs
    } while (selection < 1 || selection > (arrayLength - 1)); // arrayLength includes the intro string, so the amount of choices is arraylength-1

    return selection;
}

void removeIndex(vector<int> &modifyVector, int index) {
    modifyVector.erase(modifyVector.begin() + index); // https://cplusplus.com/reference/vector/vector/erase/
}

void removeIndex(vector<string> &modifyVector, int index) {
    modifyVector.erase(modifyVector.begin() + index); // https://cplusplus.com/reference/vector/vector/erase/
}

void removeIndex(vector<vector<string>> &modifyVector, int index) {
    modifyVector.erase(modifyVector.begin() + index); // https://cplusplus.com/reference/vector/vector/erase/
}

int matchWord(vector<vector<string>> strings, vector<int> dataTypes, string matchString) {
    const int DATA_TYPE_ASSOCIATION = 0; // defined here alongside in main because no globals allowed (my interpretation of class news post #/#/####)
    const int DATA_TYPE_EQUATION = 1;

    for (int i = 0; i < strings.size(); i++) {
        if (dataTypes[i] == DATA_TYPE_ASSOCIATION) { // only search associations
            for (int j = 0; j < strings[i].size(); j++) {
                if (strings[i][j] == matchString) {
                    return i; // index of the matching data
                }
            }
        }
    }

    return -1; // readable failure condition, as the above testing could never return -1
}

string inputLine(string questionString) {
    cout << questionString;

    string inputString;
    getline(cin, inputString);

    return inputString;
}

void readAllStrings(istream &stream, vector<string> &readTo) {
    string input;
    while (stream >> input) {
        readTo.push_back(input);
    }

    stream.clear(); // we'll clean up the fail() to be nice
}

int presentDataDeletionMenu(vector<vector<string>> inputs, vector<string> outputs, vector<int> dataTypes, int menuDataType) {
    int selection = 0;
    int maxSelection = 0;

    // lets count how many of the type we have
    for (int i = 0; i < dataTypes.size(); i++) {
        if (dataTypes[i] == menuDataType) {
            maxSelection++;
        }
    }

    if (maxSelection == 0) { // we have none to display, let main() warn the user and return to main menu
        return -1;
    }

    do {
        cout << "\nSelect data to delete:\n";

        {  
            int j = 1;
            for (int i = 0; i < dataTypes.size(); i++) {
                if (dataTypes[i] == menuDataType) {
                    stringstream outputStream; // https://cplusplus.com/reference/sstream/stringstream/stringstream/

                    outputStream << j << ". " << inputs[i][0];
                    for (int k = 1; k < inputs[i].size(); k++) {
                        outputStream << ", " << inputs[i][k];
                    }
                    outputStream << ": ";

                    cout << setw(50) << left << outputStream.str() << outputs[i] << endl;
                    j++;
                }
            }
        }

        cout << "Choice: ";
        selection = getMenuInput(); // removed cin >>, replaced with a function using getline to remove infinite looping bugs
    } while (selection < 1 || selection > maxSelection);

    {
        int j = 1;
        for (int i = 0; i < dataTypes.size(); i++) {
            if (dataTypes[i] == menuDataType) {
                if (j == selection) {
                    return i;
                }

                j++;
            }
        }
    }

    return -2; // makes the compiler warning go away, this should never be reached though
}

int presentEquationSelectionMenu(vector<vector<string>> inputs, vector<string> equations, vector<int> dataTypes, int equationDataValue) {
    int selection = 0;
    int maxSelection = 0;

    for (int i = 0; i < dataTypes.size(); i++) {
        if (dataTypes[i] == equationDataValue) {
            maxSelection++;
        }
    }

    if (maxSelection == 0) {
        return -1;
    }

    do {
        cout << "\nSelect equation to utilize:\n";

        {  
            int j = 1;
            for (int i = 0; i < dataTypes.size(); i++) {
                if (dataTypes[i] == equationDataValue) {
                    stringstream outputString; // to use setw(), i want to output all in one string, so i will use this to construct a full string https://cplusplus.com/reference/sstream/stringstream/stringstream/

                    outputString << j << ". " << inputs[i][0];

                    if (inputs[i].size() > 1) { // if there's anything more than the name to the equation
                        outputString << " - ";  // add the dash to signify that there are variables
                    }

                    for (int k = 1; k < inputs[i].size(); k++) {
                        outputString << inputs[i][k];

                        if (k < inputs[i].size() - 1) { // adapted so that the first element can have a different separator
                            outputString << ", ";
                        }
                    }
                    
                    outputString << ": ";
                    cout << setw(50) << left << outputString.str() << equations[i] << endl;
                    j++;
                }
            }
        }

        cout << "Choice: ";
        selection = getMenuInput(); // removed cin >>, replaced with a function using getline to remove infinite looping bugs
    } while (selection < 1 || selection > maxSelection);

    cin.clear();

    {
        int j = 1;
        for (int i = 0; i < dataTypes.size(); i++) {
            if (dataTypes[i] == equationDataValue) {
                if (j == selection) {
                    return i;
                }

                j++;
            }
        }
    }

    return -2; // here to satiate the compiler; function should always return from somewhere before this point
}

int getMenuInput() { // you would think this is exactly what 'cin >> int' is fantastic for; unfortunately 'cin >> int' can result in infinite loops in validation code and idk why so we're going to do this instead [LATER ME EDIT: I think I know now]
    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    string inputString;
    int inputInt = -1;

    getline(cin, inputString);

    ss.str(inputString); //https://cplusplus.com/reference/sstream/stringstream/str/
    ss >> inputInt; // take the first part from the stream and attempt to put it into the int

    return inputInt; // will return the input int, anything outside range will be handled in the menu handler, if inputting int failed the returned int will be out of range and be caught
}

bool isValidEquation(vector<string> equationMetadata, string equationString, const string OPERATIONS[], int operationCount) {
    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    ss.str(equationString); // https://cplusplus.com/reference/sstream/stringstream/str/

    bool isValid = true;

    int i = 0;
    string testString;
    while (isValid && (ss >> testString)) {
        if (i % 2 == 0) { // should be a number
            bool isVariable = false;
            for (int j = 1; j < equationMetadata.size(); j++) {
                if (equationMetadata[j] == testString) {
                    isVariable = true;
                }
            }

            stringstream doubleTest;
            doubleTest.str(testString); // https://cplusplus.com/reference/sstream/stringstream/str/

            double testDouble;
            if (!(isVariable || (doubleTest >> testDouble))) { // if it failed both tests
                isValid = false; // will break the loop implicitly
            }
        } else { // should be an operation
            if (!isValidOperation(OPERATIONS, operationCount, testString)) { // if it is not an operation
                isValid = false; // will also break the loop implicitly
            }
        }

        i++;
    }

    return (isValid && (i % 2 == 1));   // equation must both end and start with a number to be valid; starting with a number is implicitly checked in the loop; ending with one is checked here
}                                       // i%2 should be 1 because it will be incremented after the last test; the last test should be on i%2 == 0 for it to be on a number. 0++ == 1

bool isValidOperation(const string OPERATIONS[], int operationCount, string checkString) {
    for (int i = 0; i < operationCount; i++) {
        if (OPERATIONS[i] == checkString) {
            return true;
        }
    }

    return false;
}

double evaluateEquation(const string OPERATIONS[], int operationCount, string equationString) {
    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    ss.str(equationString); // https://cplusplus.com/reference/sstream/stringstream/str/

    // we will assume that the equation is valid as main() will call isValidEquation() before passing into this function
    string evaluationString;
    ss >> evaluationString;

    double lastValue = getNumberByString(evaluationString);
    while ((!isnan(lastValue)) && (ss >> evaluationString)) { // while there's equation left to evaluate and a NAN has not occurred
        string newNumber;
        ss >> newNumber;
        // evaluationString will always be an operator, newNumber will always be the string of a number
        lastValue = performOperation(OPERATIONS, operationCount, lastValue, evaluationString, getNumberByString(newNumber));
    }

    return lastValue;
}

double evaluateEquation(const string OPERATIONS[], int operationCount, vector<string> equationMetadata, string equationString) {
    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    ss.str(equationString); // https://cplusplus.com/reference/sstream/stringstream/str/

    // we will assume that the equation is valid as main() will call isValidEquation() before passing into this function
    string evaluationString;
    ss >> evaluationString;

    vector<double> variables = getVariablesForEquation(equationMetadata);

    double lastValue = getNumberByString(evaluationString, equationMetadata, variables);
    while ((lastValue != NAN) && (ss >> evaluationString)) {
        string newNumber;
        ss >> newNumber;
        // evaluationString will always be an operator, newNumber will always be the string of a number
        lastValue = performOperation(OPERATIONS, operationCount, lastValue, evaluationString, getNumberByString(newNumber, equationMetadata, variables));
    }

    return lastValue;
}

double getNumberByString(string evaluationString) {
    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    ss.str(evaluationString); //https://cplusplus.com/reference/sstream/stringstream/str/

    double returnValue;
    ss >> returnValue; // we will assume it works because we have verified the equation already

    return returnValue;
}

double getNumberByString(string evaluationString, vector<string> equationMetadata, vector<double> variables) {
    // start at 1, first string in equationMetadata is equation name
    for (int i = 1; i < equationMetadata.size(); i++) {
        if (equationMetadata[i] == evaluationString) {
            return variables[i-1]; // variables is not padded to account for the equation name string in metadata, so we have to modify index
        }
    }

    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    ss.str(evaluationString); // https://cplusplus.com/reference/sstream/stringstream/str/

    double returnValue;
    ss >> returnValue; // we will assume it works because the equation has already been verified good to get to this point, and we've already confirmed it's not a variable.

    return returnValue;    
}

vector<double> getVariablesForEquation(vector<string> equationMetadata) {
    vector<double> variableValues;

    // starts at 1 because index 0 is the equation name
    for (int i = 1; i < equationMetadata.size(); i++) {
        cout << "Enter a value for the variable named \"" << equationMetadata[i] << "\": ";

        string inputString; // using getline because 'cin >>' problems seem to always crop up
        getline(cin, inputString);
        
        stringstream inputSStream; // double S intentional; S(tring)Stream
        inputSStream.str(inputString); // https://cplusplus.com/reference/sstream/stringstream/str/

        double variableValue;
        while (!(inputSStream >> variableValue)) {
            cout << "Re-enter a value for the variable named \"" << equationMetadata[i] << "\": ";
            getline(cin, inputString);
            inputSStream.str(inputString); // https://cplusplus.com/reference/sstream/stringstream/str/
            inputSStream.clear(); // clear the error
        }

        variableValues.push_back(variableValue);
    }

    return variableValues;
}

double performOperation(const string OPERATIONS[], int operationCount, double value1, string operation, double value2) {
    // we can assume that everything should be valid, because by this point the equation has passed verification, including verifying that every operation exists
    const int ADD = 0;
    const int SUB = 1;
    const int MUL = 2;
    const int DIV = 3;
    const int MOD = 4;
    const int POW = 5;
    const int ROOT = 6;
    const int LOG = 7;

    int operationNum;
    for (int i = 0; i < operationCount; i++) {
        if (OPERATIONS[i] == operation) {
            operationNum = i;
            break; // this break does absolutely nothing other than very slightly speed up execution; further loops will never do anything
        }
    }

    double returnNumber;
    switch(operationNum) {
        case ADD: {
            returnNumber = value1 + value2;
        } break;
        case SUB: {
            returnNumber = value1 - value2;
        } break;
        case MUL: {
            returnNumber = value1 * value2;
        } break;
        case DIV: {
            if (value2 == 0) {
                cout << "ERROR: Divide by zero!\n";
                returnNumber = NAN;
            } else {
                returnNumber = value1 / value2;
            }
        } break;
        case MOD: {
            if (value2 == 0) {
                cout << "ERROR: Mod by zero!\n";
                returnNumber = NAN;
            } else {
                returnNumber = fmod(value1, value2);
            }
        } break;
        case POW: {
            returnNumber = pow(value1, value2);
        } break;
        case ROOT: {
            if (value1 == 0) {
                cout << "ERROR: Root by zero!\n";
                returnNumber = NAN;
            } else {
                returnNumber = pow(value2, (1/value1)); // this is reversed so that 3 RT 27 means third root of 27 rather than 27th root of 3.
                if (isnan(returnNumber)) { // catch if it fails (e.g. an even root of a negative number)
                    cout << "ERROR: Invalid root!\n";
                }
            }
        } break;
        case LOG: {
            if (value1 == 1 || value1 <= 0) { // log1(x) is undefined; log0(x) is undefined; log{<0}(x) is undefined
                cout << "ERROR: Log by 1 or <=0!\n";
                returnNumber = NAN;
            } else if (value2 <= 0) { // logx(0) is undefined; logx(<0) is undefined
                cout << "ERROR: Log of <=0!\n";
                returnNumber = NAN;
            } else {
                returnNumber = log10(value2) / log10(value1); // this is reversed so that 2 LG 8 means log2(8) rather than log8(2).
            }
        } break;
    }

    return returnNumber;
}

void crawlForVariables(vector<string> &metadata, string equationString) {
    stringstream ss; // https://cplusplus.com/reference/sstream/stringstream/stringstream/
    ss.str(equationString); //https://cplusplus.com/reference/sstream/stringstream/str/

    int i = 0;
    string testingString;
    while ((ss >> testingString)) {
        if (i % 2 == 0) { // is meant to be a number/variable
            stringstream doubleTestStream;
            doubleTestStream.str(testingString);

            double doubleTest;
            if (!(doubleTestStream >> doubleTest)) { // if it's not a number, we consider it a variable
                bool unique = true;
                for (int j = 1; j < metadata.size(); j++) { // start at 1 because metadata has equation name in position 0
                    if (metadata[j] == testingString) {
                        unique = false;
                    }
                }

                if (unique) { // only push a variable if it's unique
                    metadata.push_back(testingString);
                }
            }
        }
        i++;
    }
}
