
#include "../include/Conector.h"

Conector::Conector() : conectado (true) {
    this->lock = new LockFile (archivoTmp);
}

Conector::~Conector() {
    this->conectado = false;
    delete lock;
}

bool Conector::conectar() {
    if (conectado)
        return false;

    this->lock->tomarLock();

    // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    char numLeido;
    this->lock->leer(&numLeido, 1);
    int cantClientes = atoi(&numLeido);
    cantClientes++;
    this->lock->escribir(&cantClientes, 1);

    this->lock->liberarLock();
    return true;
}

bool Conector::desconectar() {
    if (!conectado)
        return false;

    this->lock->tomarLock();

    // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    char numLeido;
    this->lock->leer(&numLeido, 1);
    int cantClientes = atoi(&numLeido);
    cantClientes--;
    this->lock->escribir(&cantClientes, 1);

    this->lock->liberarLock();
    return true;
}

int Conector::nroCliente() {
    if (!conectado)
        return 0;

    this->lock->tomarLock();

    // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    char numLeido;
    this->lock->leer(&numLeido, 1);
    int cantClientes = atoi(&numLeido);

    this->lock->liberarLock();
    return cantClientes;
}
