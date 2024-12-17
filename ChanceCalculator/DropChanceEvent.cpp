// Kelton
// [CLASS CODE HERE]
// November 28, 2024
// Modified November 29, 2024
// Function comments added 12/8/2024

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "DropChanceEvent.h"

using namespace std;

// default constructor; default constructs a ChanceEvent and sets the dropper to 'Undefined'
DropChanceEvent::DropChanceEvent() : ChanceEvent() {
    setDropper("Undefined");
}

// full constructor, intaking a drop chance (0<x<1), item name, and dropper name
// drop chance and item name are passed on to the ChanceEvent constructor
DropChanceEvent::DropChanceEvent(double dChance, string sName, string sDropper) : ChanceEvent(dChance, sName) {
    setDropper(sDropper);
}

// returns the name of the item dropper
string DropChanceEvent::getDropper() const {
    return string(dropper);
}

// sets the item dropper name after construction
// will cut the name off at 39 character by default, as it's stored as a char[]
// the name cutoff point is determined by the const ChanceEvent::NAME_LENGTH
void DropChanceEvent::setDropper(string sDropper) {
    strncpy(dropper, sDropper.c_str(), ChanceEvent::NAME_LENGTH);
    dropper[ChanceEvent::NAME_LENGTH - 1] = '\0';
}

// outputs a formatted message to cout displaying the chance of the event
// also outputs an approximate fractional representation of the chance
void DropChanceEvent::displayChance() const {
    int num, den;
    getApproxNumeratorDenominator(num, den);
    cout << name << " has a " << setprecision(2) << fixed << chance*100 << "\% chance to drop from each " << dropper << ".\n"
         << "That's about a " << num << "/" << den << " chance.\n";
}

// outputs a formatted message to cout displaying the chance of the item being dropped given an input number of actions
void DropChanceEvent::displayChanceFromActions(int iActions) const {
    cout << "Given " << iActions << " " << dropper << "(s), " << name << " has about a " << setprecision(2) << fixed
         << getChanceFromActions(iActions)*100 << "\% chance to drop.\n";
}

// outputs a formatted message to cout displaying the amount of occurences needed to reach an input desired chance (0<x<1)
// e.g. given an event with a 50% chance and a desired chance of 75%, it will indicate that 2 occurences are required
void DropChanceEvent::displayActionsFromChance(double dChance) const {
    clampChance(dChance);
    cout << "To have about a " << setprecision(2) << fixed << dChance*100 << "\% chance for " << name 
         << " to drop, you would have to loot from " << getActionsFromChance(dChance) << " " << dropper << "(s)\n";
}

// operator<< overloaded to allow for easy display
ostream& operator<<(ostream& out, const DropChanceEvent& event) {
    out << event.name << ": " << setprecision(2) << fixed << event.chance*100 << "\% from " << event.dropper;
    return out;
}
