// Kelton
// [CLASS CODE HERE]
// November 28, 2024
// Modified November 29, 2024
// Function comments added 12/8/2024

#include <string>
#include <iostream>
#include <iomanip>
#include "TimeChanceEvent.h"

using namespace std;

// default constructor; default constructs a ChanceEvent and sets events per second to 1.0
TimeChanceEvent::TimeChanceEvent() : ChanceEvent() {
    eventsPerSecond = 1.0;
}

// full constructor intaking a drop chance (0<x<1), item name, and a number of events per second
// passes drop chance and item name into the ChanceEvent constructor
TimeChanceEvent::TimeChanceEvent(double dChance, string sName, double dEventsPerSecond) : ChanceEvent(dChance, sName) {
    eventsPerSecond = dEventsPerSecond;
}

// returns the events per second
double TimeChanceEvent::getEventsPerSecond() const {
    return eventsPerSecond;
}

// outputs a formatted message to cout displaying the chance of the event (with an approximate fraction) and how frequently it occurs
void TimeChanceEvent::displayChance() const {
    int num, den;
    getApproxNumeratorDenominator(num, den);
    cout << name << " has a " << setprecision(2) << fixed << chance*100 << "\% (~" << num << "/" << den << ") chance to drop every " 
         << 1/eventsPerSecond << " second(s).\n"
         << "This means the event occurs " << eventsPerSecond << " time(s) per second.\n";
}

// outputs a formatted message to cout displaying the chance of the item being dropped given an input number of actions
// also outputs the amount of time it would take for that many actions
void TimeChanceEvent::displayChanceFromActions(int iActions) const {
    cout << "Given " << iActions << " action(s), you have around a " << getChanceFromActions(iActions)*100 
         << "\% chance to obtain a(n) " << name << ".\n"
         << "That would take around " << setprecision(2) << fixed << iActions/eventsPerSecond << " second(s).\n";
}

// outputs a formatted message to cout displaying the amount of occurences needed to reach an input desired chance (0<x<1)
// e.g. given an event with a 50% chance and a desired chance of 75%, it will indicate that 2 occurences are required
// also outputs the amount of time it would take for the calculated number of occurences
void TimeChanceEvent::displayActionsFromChance(double dChance) const {
    clampChance(dChance);
    int actions = getActionsFromChance(dChance);
    cout << "To have about a " << setprecision(2) << fixed << dChance*100 << "\% chance to get a(n) " << name 
         << ", you would need " << actions << " action(s).\n"
         << "This would take " << actions/eventsPerSecond << " second(s).\n";
}

// directly sets the events per second after construction
void TimeChanceEvent::setEventsPerSecond(double dEventsPerSecond) {
    eventsPerSecond = dEventsPerSecond;
}

// sets the events per second after construction, calculating from an input events per minute
void TimeChanceEvent::setEventsPerMinute(double dEventsPerMinute) {
    eventsPerSecond = dEventsPerMinute / 60.0;
}

// sets the events per second after construction, calculating from an input events per hour
void TimeChanceEvent::setEventsPerHour(double dEventsPerHour) {
    eventsPerSecond = dEventsPerHour / 3600.0;
}

// sets the events per second after construction, calculating from an input seconds per event
void TimeChanceEvent::setSecondsPerEvent(double dSeconds) {
    eventsPerSecond = (1/dSeconds);
}

// sets the events per second after construction, calculating from an input minutes per event
void TimeChanceEvent::setMinutesPerEvent(double dMinutes) {
    eventsPerSecond = (1/(dMinutes / 60.0));
}

// sets the events per second after construction, calculating from an input hours per event
void TimeChanceEvent::setHoursPerEvent(double dHours) {
    eventsPerSecond = (1/(dHours / 3600.0));
}

// operator<< overloaded to allow for easy display
ostream& operator<<(ostream& out, const TimeChanceEvent& event) {
    out << event.name << ": " << setprecision(2) << fixed << event.chance*100 << "\% per " << 1/event.eventsPerSecond << "s";
    return out;
}
