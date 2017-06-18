
#ifndef CLIENTE_BDD_CONECTOR_H
#define CLIENTE_BDD_CONECTOR_H


#include "ipc/ExclusiveLockFile.h"
#include "ipc/SharedLockFile.h"

class Conector {

private:
    bool conectado;
    const char* archivoTmp = "../../tmp/cantClientes.txt";

    int leerNumero ();
    void escribirNumero (const int nro);

public:
    Conector ();
    ~Conector ();
    bool conectar ();
    bool desconectar ();
    int nroCliente ();

};


#endif //CLIENTE_BDD_CONECTOR_H
