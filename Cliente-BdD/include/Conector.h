
#ifndef CLIENTE_BDD_CONECTOR_H
#define CLIENTE_BDD_CONECTOR_H


#include "ipc/ExclusiveLockFile.h"
#include "ipc/SharedLockFile.h"

class Conector {

private:
    const char* archivo = "../../aux/cantClientes.txt";
    bool conectado;
    int nroCliente;

    int leerNumero ();
    void escribirNumero (const int nro);
    bool existeContadorConexiones ();

public:
    Conector ();
    ~Conector ();
    bool conectar ();
    void desconectar ();
    int verNroCliente ();

};


#endif //CLIENTE_BDD_CONECTOR_H
