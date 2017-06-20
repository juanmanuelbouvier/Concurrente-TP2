
#ifndef GESTOR_BDD_EVENTHANDLER_H
#define GESTOR_BDD_EVENTHANDLER_H

class EventHandler {

public:
    virtual int handleSignal ( int signum ) = 0;
    virtual ~EventHandler () {};

};


#endif //GESTOR_BDD_EVENTHANDLER_H
