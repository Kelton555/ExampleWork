// Kelton
// [CLASS CODE HERE]
// November 28, 2024

#ifndef DROP_CHANCE_EVENT_H
#define DROP_CHANCE_EVENT_H

#include <string>
#include "ChanceEvent.h"

using namespace std;

class DropChanceEvent : public ChanceEvent {
    protected:
        char dropper[ChanceEvent::NAME_LENGTH];
    public:
        // constructors
        DropChanceEvent();
        DropChanceEvent(double, string, string); 

        // getters
        string getDropper() const;

        virtual void displayChance() const override;
        virtual void displayChanceFromActions(int) const override;
        virtual void displayActionsFromChance(double) const override;

        // setter
        void setDropper(string);

        // operators
        friend ostream& operator<<(ostream&, const DropChanceEvent&);
};

#endif
