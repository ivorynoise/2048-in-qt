#include "subject.h"
#include "observer.h"

Subject::Subject()
{
}

void Subject::notifyObservers(){
    for(Observer* curObserver : observers){
        curObserver->notify();
    }
}

void Subject::registerObserver(Observer *curObserver){
    observers.push_back(curObserver);
}
