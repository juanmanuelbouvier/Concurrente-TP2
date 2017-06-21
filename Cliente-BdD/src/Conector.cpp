
#include <iostream>
#include "../include/Conector.h"
#include "../include/Logger.h"

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

    long numLeido = leerNumero();
    if (numLeido < 0) {
        Logger :: getInstance() -> info( "Conector", "No se pudo leer la cantidad de clientes conectados");
        return false;
    }
    long cantClientes = numLeido + 1;
    if ( escribirNumero(cantClientes) <= 0 ) {
        Logger :: getInstance() -> info( "Conector", "No se pudo actualizar el contador de clientes conectados");
        return false;
    }
    this->conectado = true;
    this->nroCliente = cantClientes;
    return true;
}

void Conector::desconectar() {
    this->conectado = false;

    if ( !existeContadorConexiones() ) {
        perror("El archivo con el contador de conexiones no existe");
        return;
    }

    long numLeido = leerNumero();
    if (numLeido >= 0) {
        long cantClientes = numLeido - 1;
        if ( escribirNumero(cantClientes) <= 0 ) {
            Logger :: getInstance() -> info( "Conector", "No se pudo decrementar el contador de conexiones activas al desconectar el cliente");
        }
    } else {
        Logger :: getInstance() -> info( "Conector", "No se pudo leer la cantidad de clientes conectados entonces no se pudo decrementar el contador al desconectar el cliente");
    }
}

long Conector::verNroCliente() {
    return nroCliente;
}

long Conector :: leerNumero () {
    SharedLockFile readLock = SharedLockFile (archivo);
    long numLeido = 0;
    readLock.tomarLock();
    if ( readLock.leer(&numLeido, sizeof(long)) <= 0 ) {
        perror("No se pudo leer el archivo contador de conexiones");
        numLeido = -1;
    }
    readLock.liberarLock();
    return numLeido;
}

ssize_t Conector::escribirNumero(const long nro) {
    ExclusiveLockFile writeLock = ExclusiveLockFile (archivo);
    writeLock.tomarLock();
    ssize_t bytesEscritos = writeLock.remplazar( static_cast<const void*>(&nro), sizeof(long) );
    if ( bytesEscritos <= 0 ) {
        perror("No se pudo actualizar el contador de conexiones");
    }
    writeLock.liberarLock();
    return bytesEscritos;
}

bool Conector::existeContadorConexiones() {
    int fdTmp = open ( archivo, O_RDONLY, 0777 );
    if (fdTmp < 0) {
        return false;
    }
    close ( fdTmp );
    return true;
}

