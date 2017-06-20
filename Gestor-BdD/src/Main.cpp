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

void escribirNumero( const char* archivo, const long nro ) {
    ExclusiveLockFile writeLock = ExclusiveLockFile (archivo);
    writeLock.tomarLock();
    writeLock.remplazar( &nro, sizeof(long) );
    writeLock.liberarLock();
}

void inicializarArchivoTemporal(const string archivo) {
    crearDirectorioSiNoExiste(archivo);
    int fdTmp = open ( archivo.c_str(), O_CREAT|O_EXCL|O_RDONLY, 0777 );
    if ( fdTmp < 0 ) {
        Logger :: getInstance() -> info( "Gestor", "El archivo con contador de conexiones de clientes ya existe");
    } else {
        close( fdTmp );
        escribirNumero ( archivo.c_str(), 0 );
        Logger :: getInstance() -> info( "Gestor", "Archivo con contador de conexiones de clientes inicializado");
    }
}

int main() {
    cout << "Gestor de base de datos de personas iniciado" << endl;

    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    const string archivo = "../../aux/cantClientes.txt";
    inicializarArchivoTemporal(archivo);

    DespachanteConsultas despachante = DespachanteConsultas ();
    while ( sigint_handler.getGracefulQuit() == 0 ) {
        despachante.despachar();
    }
    SignalHandler :: destruir ();

    return 0;
}