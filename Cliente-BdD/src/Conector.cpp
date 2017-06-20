
#include <iostream>
#include "../include/Conector.h"

Conector::Conector() : conectado (false) {
}

Conector::~Conector() {
    this->conectado = false;
}

bool Conector::conectar() {
    if (this->conectado)
        return false;

    this->conectado = true;
    int numLeido = leerNumero();
    int cantClientes = numLeido + 1;
    escribirNumero(cantClientes);
    return true;
}

bool Conector::desconectar() {
    if (!this->conectado)
        return false;

    this->conectado = false;
    int numLeido = leerNumero();
    int cantClientes = numLeido - 1;
    escribirNumero(cantClientes);
    return true;
}

int Conector::nroCliente() {
    if (!this->conectado)
        return 0;

    return leerNumero();
}

int Conector :: leerNumero () {
    SharedLockFile readLock = SharedLockFile (archivoTmp);
    int numLeido = 0;
    readLock.tomarLock();
    readLock.leer(&numLeido, sizeof(int));
    readLock.liberarLock();
    return numLeido;
}

void Conector::escribirNumero(const int nro) {
    ExclusiveLockFile writeLock = ExclusiveLockFile (archivoTmp);
    writeLock.tomarLock();
    writeLock.remplazar( static_cast<const void*>(&nro), sizeof(int) );
    writeLock.liberarLock();
}

