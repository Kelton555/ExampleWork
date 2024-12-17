// Kelton
// [CLASS CODE HERE]
// November 28, 2024
// Modified November 29, 2024

#ifndef CHANCE_EVENT_H
#define CHANCE_EVENT_H

#include <string>
#include <iostream>

using namespace std;

class ChanceEvent {
    public:
        static const int NAME_LENGTH = 40;
        static void clampChance(double&);
    protected:
        double chance;
        char name[NAME_LENGTH];
    public:
        // constructors
        ChanceEvent();
        ChanceEvent(double, string);

        // getters
        double getChance() const;
        string getName() const;

        int getApproxNumerator() const;
        int getApproxDenominator() const;
        double getChanceFromActions(int) const;
        int getActionsFromChance(double) const;

        // also getters, but using reference variables
        void getApproxNumeratorDenominator(double&, double&) const;
        void getApproxNumeratorDenominator(int&, int&) const;

        // pure virtual functions
        virtual void displayChance() const = 0;
        virtual void displayChanceFromActions(int) const = 0;
        virtual void displayActionsFromChance(double) const = 0;

        // setters
        void setChance(double);
        void setName(string);

        // operators
        friend ostream& operator<<(ostream&, const ChanceEvent&);
};

#endif
