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

int crearArchivoTemporal(const string archivoTmp) {
    crearDirectorioSiNoExiste(archivoTmp);
    int fdTmp = open ( archivoTmp.c_str(), O_CREAT|O_EXCL|O_RDONLY, 0777 );
    return close( fdTmp );
}

int main() {
    std::cout << "Soy gestor!" << std::endl;

    const string archivoTmp = "../../tmp/cantClientes.txt";
    crearArchivoTemporal(archivoTmp);

    DespachanteConsultas despachante = DespachanteConsultas ();
    while (true) {  // TODO: Usar gracefulQuit con signals para matar el servidor.
        despachante.despachar();
        sleep(1);   // TODO: Si lo sacamos se me muere la compu.
    }

    unlink (archivoTmp.c_str());

    return 0;
}