#include <iostream>
#include "../include/DespachanteConsultas.h"
#include "../include/ipc/signal/impl/SIGINT_Handler.h"
#include "../include/ipc/signal/SignalHandler.h"

int crearDirectorioSiNoExiste(string rutaCompletaArchivo) {
    string path = rutaCompletaArchivo.substr(0, rutaCompletaArchivo.find_last_of("\\/"));
    DIR* dir = opendir(path.c_str());
    if (dir) {
        return closedir(dir);
    }
    else if (ENOENT == errno) {
        return mkdir(path.c_str(), 0777);
    }
    return -1;
}

void escribirNumero( const char* archivoTmp, const int nro ) {
    ExclusiveLockFile writeLock = ExclusiveLockFile (archivoTmp);
    writeLock.tomarLock();
    writeLock.remplazar(&nro, sizeof(int));
    writeLock.liberarLock();
}

int inicializarArchivoTemporal(const string archivoTmp) {
    crearDirectorioSiNoExiste(archivoTmp);
    int fdTmp = open ( archivoTmp.c_str(), O_CREAT|O_EXCL|O_RDONLY, 0777 );
    escribirNumero ( archivoTmp.c_str(), 0 );
    return close( fdTmp );
}

int main() {
    cout << "Gestor de base de datos de personas iniciado" << endl;

    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    const string archivoTmp = "../../tmp/cantClientes.txt";
    inicializarArchivoTemporal(archivoTmp);

    DespachanteConsultas despachante = DespachanteConsultas ();
    while ( sigint_handler.getGracefulQuit() == 0 ) {
        despachante.despachar();
    }
    SignalHandler :: destruir ();

    unlink (archivoTmp.c_str());

    return 0;
}