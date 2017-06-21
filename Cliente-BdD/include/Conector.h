
#ifndef CLIENTE_BDD_CONECTOR_H
#define CLIENTE_BDD_CONECTOR_H


#include "ipc/ExclusiveLockFile.h"
#include "ipc/SharedLockFile.h"

class Conector {

private:
    const char* archivo = "../../aux/cantClientes.txt";
    bool conectado;
    long nroCliente;

    long leerNumero ();
    ssize_t escribirNumero (const long nro);
    bool existeContadorConexiones ();

public:
    Conector ();
    ~Conector ();
    bool conectar ();
    void desconectar ();
    long verNroCliente ();

};


#endif //CLIENTE_BDD_CONECTOR_H
