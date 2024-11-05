// This program was made for the Midterm project of an introductory programming course

// Kelton
// 2/26/2024 - Amended 3/12/2024
// MultiCalculator.cpp
// A calculator program with two modes: two numbers and an operation, or calculate a mean from a non-fixed length series of numbers.

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main() {
    const int LPAD = 3, RPAD = 25; 

    string calculatorUser;
    cout << "Who is using this calculator? ";
    getline(cin, calculatorUser);

    int calculatorChoice;
    cout << "\nWhich calculator would you like to use?\n"
         << setw(LPAD) << left << "1." << setw(RPAD) << right << "Basic calculator\n"
         << setw(LPAD) << left << "2." << setw(RPAD) << right << "Average calculator\n";
    cout << "Selection: ";
    cin >> calculatorChoice;
    cout << endl;

    switch(calculatorChoice) {
        case 1:
            double number1, number2;
            int operationChoice;

            cout << "Please enter a number (a): ";
            cin >> number1;
            cout << "Please enter a second number (b): ";
            cin >> number2;

            cout << "\nPlease select an operation from this list:\n"
                 << setw(LPAD) << left << "1." << setw(RPAD) << right << "Addition (a + b)\n"
                 << setw(LPAD) << left << "2." << setw(RPAD) << right << "Subtraction (a - b)\n"
                 << setw(LPAD) << left << "3." << setw(RPAD) << right << "Multiplication (a * b)\n"
                 << setw(LPAD) << left << "4." << setw(RPAD) << right << "Division (a / b)\n"
                 << setw(LPAD) << left << "5." << setw(RPAD) << right << "Power (a ^ b)\n"
                 << setw(LPAD) << left << "6." << setw(RPAD) << right << "Root (bth root of a)\n"
                 << setw(LPAD) << left << "7." << setw(RPAD) << right << "Logarithm (log b (a))\n"
                 << setw(LPAD) << left << "8." << setw(RPAD) << right << "Modulo (a % b)\n";
            cout << "\nSelection: ";
            cin >> operationChoice;

            cout << endl;
            switch(operationChoice) {
                case 1:
                    cout << number1 << " + " << number2 << " = " << number1 + number2;
                    break;
                case 2:
                    cout << number1 << " - " << number2 << " = " << number1 - number2;
                    break;
                case 3:
                    cout << number1 << " * " << number2 << " = " << number1 * number2;
                    break;
                case 4:
                    cout << number1 << " / " << number2 << " = " << number1 / number2;
                    break;
                case 5:
                    cout << number1 << " ^ " << number2 << " = " << pow(number1, number2);
                    break;
                case 6:
                    cout << "Root " << number2 << " of " << number1 << " = " << pow(number1, (1/number2)); // x^(1/n) = nth root of x
                    break;
                case 7:
                    cout << "log " << number2 << " (" << number1 << ") = " << log10(number1) / log10(number2); // log a (b) / log a (c) = log c (b)
                    break;
                case 8:
                    cout << number1 << " % " << number2 << " = " << fmod(number1, number2);
                    break;
                default:
                    cout << "Invalid operation. Please re-run the program and select a valid operation.";
                    return 1;
            }
            break; // end of case

        case 2: { // this one needs to be in braces because of the declaration of count, otherwise compiler throws an error on 'default:'
            double total;
            double count = 0;
            char meanType;

            cout << "Which type of mean would you like to calculate? Enter \"A\" for arithmetic or \"G\" for geometric: ";
            cin >> meanType;

            switch (meanType) {
                case 'A':
                    total = 0;
                    break;
                case 'G':
                    total = 1;
                    break;
                default:
                    cout << "That is not a valid type of mean! Please re-run the program and enter a different value.";
                    return 2;
            }

            double inputNumber;
            cout << "Please enter a number to use in the mean: ";
            cin >> inputNumber;

            while (inputNumber) { // while input number is not zero
                switch(meanType) { // could use only 1 case and a default case as meanType is already validated, but this is better for readability
                    case 'A':
                        total += inputNumber;
                        break;
                    case 'G':
                        total *= inputNumber;
                        break;
                }
                count++;

                cout << "Please enter another number to use in the mean. Enter 0 if you're done entering numbers: ";
                cin >> inputNumber;
            }

            if (!count) { // if count is zero 
                cout << "You must input at least 1 number to determine a mean.";
                return 3;
            }

            if (meanType == 'A') {
                cout << "The arithmetic mean of your data is: " << (total / count);
            } else if (meanType == 'G') { // unneccessary else if, as meanType is already validated, but it's better for readability and updating
                cout << "The geometric mean of your data is: " << (pow(total, (1/count))); // x ^ (1/n) = nth root of x
            }
            break; // end of case
        }
        default:
            cout << "Invalid calculator selection! Please re-run the program and select a calculator type from the provided list.";
            return 4;
    }

    cout << "\n\nThank you for using this calculator, " << calculatorUser << "!";

    return 0;
}
