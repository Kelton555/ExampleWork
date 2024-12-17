// Kelton
// [CLASS CODE HERE]
// November 28, 2024
// Modified November 29, 2024
// Function comments added 12/8/2024

#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "ChanceEvent.h"

using namespace std;

// takes two double references and will replace them with a calculated numerator and denominator to roughly equal the chance of the event (within 5% either side)
// the returned doubles will be very close to integers
// e.g. if the chance is 40% (stored as 0.40), this function should return 2.00 and 5.00
void ChanceEvent::getApproxNumeratorDenominator(double& num, double& den) const {
    num = 1.0;
    den = round(num/chance);

    // loop and refine while the approximation is too vague
    while (num/den > chance + 0.05 || chance - 0.05 > num/den) { // 0.05 represents a 5% maximum error, e.g. 75% could be represented anywhere from (70%:80%) exclusive
        num += 1.0;
        den = round(num/chance);
    }
}

// takes two integer references and will replace them with a calculated numerator and denominator to roughly equal the chance of the event (within 5% either side)
// e.g. if the chance is 40% (stored as 0.40), this function should return 2 and 5
void ChanceEvent::getApproxNumeratorDenominator(int& num, int& den) const {
    double dNum, dDen;
    getApproxNumeratorDenominator(dNum, dDen);
    num = static_cast<int>(dNum);
    den = static_cast<int>(dDen);
}

// takes a double reference variable and will clamp it to a valid chance range if required 
// if 1 or more, clamps to 0.9999; if 0 or less, clamps to 0.0001
void ChanceEvent::clampChance(double& dChance) {
    // clamp the chance to a valid value
    if (dChance >= 1) {
        dChance = 0.9999;
    } else if (dChance <= 0) {
        dChance = 0.0001;
    }
}

// default constructor
// sets chance to 50% and item to 'Undefined'
ChanceEvent::ChanceEvent() {
    setChance(0.5);
    setName("Undefined");
}

// constructor inputting chance (which will be clamped if not within 0<x<1) and item name
ChanceEvent::ChanceEvent(double dChance, string sName) {
    setChance(dChance); // clamping occurs within this setter function
    setName(sName);
}

// returns the chance (0<x<1)
double ChanceEvent::getChance() const {
    return chance;
}

// returns the item name
string ChanceEvent::getName() const {
    return string(name);
}

// returns the approximate numerator of the calculated numerator and denominator as an int
// consider calling getApproxNumeratorDenominator(int num, int den) to get full fraction
int ChanceEvent::getApproxNumerator() const {
    double num, den;
    getApproxNumeratorDenominator(num, den);
    return static_cast<int>(num);
}

// returns the approximate denominator of the calculated numerator and denominator as an int
// consider calling getApproxNumeratorDenominator(int num, int den) to get full fraction
int ChanceEvent::getApproxDenominator() const {
    double num, den;
    getApproxNumeratorDenominator(num, den);
    return static_cast<int>(den);
}

// return the chance of the event happening (0<x<1) gievn some number of occurences
// calculates chance of event not happening occurences time(s) in a row 
double ChanceEvent::getChanceFromActions(int iActions) const {
    double notChance = 1.0-chance; // the chance of it not happening
    notChance = pow(notChance, iActions); // calculate chance of it not happening iActions times in a row
    return (1.0 - notChance); // chance = 1.0 - chance of not happening
}

// returns the amount of times an event has to occur to have a given chance (0<x<1) of it occuring
// rounds up to never undersell the amount of events required (e.g. at least 1 event will always be required)
int ChanceEvent::getActionsFromChance(double dChance) const {
    clampChance(dChance); // clamps using reference variable

    int actions = static_cast<int>(
        ceil( // rounded up since an event can't occur a fractional amount of times
            1 / (log10(1.0 - chance) / log10(1.0 - dChance)) // 1/(log notDesiredChance (notChance)) = chances on average for event to occur 
        ) // https://dropchance.app/ with my equation testing here: https://www.desmos.com/calculator/yzhuhrtsv3
    );

    return actions;
}

// sets the chance of the event after construction
// chance is clamped if not already (0<x<1)
void ChanceEvent::setChance(double dChance) {
    clampChance(dChance); // clamps using reference variable
    chance = dChance;
}

// sets the name of the event after construction
// will cut the name off at 39 characters by default, as it's stored as a char[]
// the name cutoff point is determined by the const ChanceEvent::NAME_LENGTH
void ChanceEvent::setName(string sName) {
    strncpy(name, sName.c_str(), ChanceEvent::NAME_LENGTH);
    name[ChanceEvent::NAME_LENGTH - 1] = '\0';
}

// operator<< overloaded to allow for easy display
ostream& operator<<(ostream& out, const ChanceEvent& event) {
    out << event.name << ": " << setprecision(2) << fixed << event.chance*100 << '%';
    return out;
}
