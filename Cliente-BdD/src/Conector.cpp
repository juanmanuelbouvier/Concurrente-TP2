
#include "../include/Conector.h"

Conector::Conector() : conectado (true) {
    this->writeLock = new ExclusiveLockFile (archivoTmp);
    this->readLock = new SharedLockFile (archivoTmp);
    initArchivo();
}

Conector::~Conector() {
    this->conectado = false;
    delete writeLock;
    delete readLock;
}

bool Conector::conectar() {
    if (conectado)
        return false;

    char numLeido;  // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    this->readLock->tomarLock();
    this->readLock->leer(&numLeido, 1);
    this->readLock->liberarLock();

    int cantClientes = atoi(&numLeido);
    cantClientes++;
    this->writeLock->tomarLock();
    this->writeLock->escribir(&cantClientes, 1);
    this->writeLock->liberarLock();

    return true;
}

bool Conector::desconectar() {
    if (!conectado)
        return false;

    char numLeido;  // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    this->readLock->tomarLock();
    this->readLock->leer(&numLeido, 1);
    this->readLock->liberarLock();

    int cantClientes = atoi(&numLeido);
    cantClientes--;
    this->writeLock->tomarLock();
    this->writeLock->escribir(&cantClientes, 1);
    this->writeLock->liberarLock();

    return true;
}

int Conector::nroCliente() {
    if (!conectado)
        return 0;

    char numLeido;  // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    this->readLock->tomarLock();
    this->readLock->leer(&numLeido, 1);
    this->readLock->liberarLock();
    int cantClientes = atoi(&numLeido);
    return cantClientes;
}

void Conector::initArchivo() {
    char numLeido;  // TODO: Esto solo soporta hasta 9 conexiones en simultaneo!
    this->readLock->tomarLock();
    int bytesLeidos = (int) this->readLock->leer(&numLeido, 1);
    this->readLock->liberarLock();
    if (bytesLeidos <= 0) {
        int cantClientesInit = 0;
        this->writeLock->tomarLock();
        this->writeLock->escribir(&cantClientesInit, 1);
        this->writeLock->liberarLock();
    }
}

