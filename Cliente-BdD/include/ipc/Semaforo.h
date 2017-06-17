
#ifndef CLIENTE_BDD_SEMAFORO_H
#define CLIENTE_BDD_SEMAFORO_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaforo {

private:
    int id;
    int valorInicial;

    int inicializar () const;

public:
    Semaforo ( const std::string& nombre,const int valorInicial );
    ~Semaforo();

    int wait () const; // decrementa
    int signal () const; // incrementa
    int eliminar () const;
};

#endif //CLIENTE_BDD_SEMAFORO_H
