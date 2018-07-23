#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject
{
public:
    Subject();
    void notifyObservers();
    void registerObserver(Observer* curObserver);
private:
    std::vector<Observer*> observers;
};

#endif // SUBJECT_H
