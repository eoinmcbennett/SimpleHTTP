//
// Created by Eoin on 06/08/2020.
//

#ifndef SERVERTEST_ISUBJECT_H
#define SERVERTEST_ISUBJECT_H

class IObserver;


class ISubject{
public:
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach() = 0;
    virtual void Notify(Request* request) = 0;
};
#endif //SERVERTEST_ISUBJECT_H
