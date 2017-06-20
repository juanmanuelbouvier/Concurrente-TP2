
#include <iostream>
#include "../include/Conector.h"

Conector::Conector() : conectado (false), nroCliente (1) {
}

Conector::~Conector() {
    this->conectado = false;
    this->nroCliente = 0;
}

bool Conector::conectar() {
    if (this->conectado)
        return false;

    if ( !existeContadorConexiones() ) {
        perror("El archivo con el contador de conexiones no existe");
        return false;
    }

    int numLeido = leerNumero();
    int cantClientes = numLeido + 1;
    escribirNumero(cantClientes);
    this->conectado = true;
    this->nroCliente = cantClientes;
    return true;
}

void Conector::desconectar() {
    if ( !existeContadorConexiones() ) {
        perror("El archivo con el contador de conexiones no existe");
        this->nroCliente = 0;
        return;
    }

    int numLeido = leerNumero();
    int cantClientes = numLeido - 1;
    escribirNumero(cantClientes);
    this->conectado = false;
    this->nroCliente = cantClientes;
}

int Conector::verNroCliente() {
    return nroCliente;
}

int Conector :: leerNumero () {
    SharedLockFile readLock = SharedLockFile (archivo);
    int numLeido = 0;
    readLock.tomarLock();
    readLock.leer(&numLeido, sizeof(int));
    readLock.liberarLock();
    return numLeido;
}

void Conector::escribirNumero(const int nro) {
    ExclusiveLockFile writeLock = ExclusiveLockFile (archivo);
    writeLock.tomarLock();
    writeLock.remplazar( static_cast<const void*>(&nro), sizeof(int) );
    writeLock.liberarLock();
}

bool Conector::existeContadorConexiones() {
    int fdTmp = open ( archivo, O_RDONLY, 0777 );
    if (fdTmp < 0) {
        return false;
    }
    close ( fdTmp );
    return true;
}

