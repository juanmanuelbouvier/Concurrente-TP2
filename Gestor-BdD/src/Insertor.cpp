
#include "../include/Insertor.h"
#include "../include/ipc/ExclusiveLockFile.h"

Insertor::Insertor() {

}

Insertor::~Insertor() {

}

int Insertor::crearDirectorioSiNoExiste(string rutaCompletaArchivo) {
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

bool Insertor::insertar(Persona nuevoRegistro) {
    const string archivoBDD = "../../bdd/registros.txt";
    crearDirectorioSiNoExiste(archivoBDD);

    string nombre = nuevoRegistro.nombre;
    string direccion = nuevoRegistro.direccion;
    string telefono = nuevoRegistro.telefono;

    ExclusiveLockFile writeLock = ExclusiveLockFile (archivoBDD);
    const string registro = nombre + "," + direccion + "," + telefono + "\n";
    if (writeLock.tomarLock() < 0) {
        perror("Error al tomar lock exclusivo para escribir en la base de datos");
        return false;
    }
    if ( writeLock.escribir (static_cast<const void *>(registro.c_str()), registro.size()) < 0 ) {
        perror("Error al intentar escribir en el archivo de la base de datos");
        return false;
    }
    writeLock.liberarLock();
    return true;
}
