
#ifndef CLIENTE_BDD_CONECTOR_H
#define CLIENTE_BDD_CONECTOR_H


#include "ipc/LockFIle.h"

class Conector {

private:
    bool conectado;
    const char* archivoTmp = "../../tmp/cantClientes.txt";
    LockFile* lock;

    void initArchivo();

public:
    Conector ();
    ~Conector ();
    bool conectar ();
    bool desconectar ();
    int nroCliente ();

};


#endif //CLIENTE_BDD_CONECTOR_H
