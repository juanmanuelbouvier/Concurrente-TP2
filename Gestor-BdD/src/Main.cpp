#include <iostream>
#include "../include/DespachanteConsultas.h"

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
    std::cout << "Soy gestor!" << std::endl;

    const string archivoTmp = "../../tmp/cantClientes.txt";
    inicializarArchivoTemporal(archivoTmp);

    DespachanteConsultas despachante = DespachanteConsultas ();
    while (true) {  // TODO: Usar gracefulQuit con signals para matar el servidor.
        despachante.despachar();
    }

    unlink (archivoTmp.c_str());

    return 0;
}