// Kelton
// [CLASS CODE HERE]
// November 28, 2024

#ifndef TIME_CHANCE_EVENT_H
#define TIME_CHANCE_EVENT_H

#include <string>
#include "ChanceEvent.h"

class TimeChanceEvent : public ChanceEvent {
    protected:
        double eventsPerSecond;
    public:
        // constructors
        TimeChanceEvent();
        TimeChanceEvent(double, string, double);

        // getters
        double getEventsPerSecond() const;

        virtual void displayChance() const override;
        virtual void displayChanceFromActions(int) const override;
        virtual void displayActionsFromChance(double) const override;

        // setters
        void setEventsPerSecond(double);
        void setEventsPerMinute(double);
        void setEventsPerHour(double);

        void setSecondsPerEvent(double);
        void setMinutesPerEvent(double);
        void setHoursPerEvent(double);

        // operators
        friend ostream& operator<<(ostream&, const TimeChanceEvent&);
};

#endif
