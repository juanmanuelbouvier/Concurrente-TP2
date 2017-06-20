
#ifndef CLIENTE_BDD_EVENTHANDLER_H
#define CLIENTE_BDD_EVENTHANDLER_H


class EventHandler {

public:
    virtual int handleSignal ( int signum ) = 0;
    virtual ~EventHandler () {};

};


#endif //CLIENTE_BDD_EVENTHANDLER_H
