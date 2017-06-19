
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

void Insertor::insertar(Persona nuevoRegistro) {
    // TODO: Acceder en modo escritura al archivo de la base de datos.
    const string archivoBDD = "../../bdd/registros.txt";
    crearDirectorioSiNoExiste(archivoBDD);

    string nombre = nuevoRegistro.nombre;
    string direccion = nuevoRegistro.direccion;
    string telefono = nuevoRegistro.telefono;

    ExclusiveLockFile writeLock = ExclusiveLockFile (archivoBDD);
    writeLock.tomarLock();
    const string registro = nombre + "," + direccion + "," + telefono + "\n";
    ssize_t resultado = writeLock.escribir ( static_cast<const void *>(registro.c_str()), registro.size() );
    writeLock.liberarLock();
}
