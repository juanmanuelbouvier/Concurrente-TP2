
#ifndef CLIENTE_BDD_LOCKFILE_H
#define CLIENTE_BDD_LOCKFILE_H

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

class LockFile {

private:
    struct flock fl;
    int fd;
    string nombre;

    int crearDirectorioSiNoExiste (string rutaCompletaArchivo);

public:
    LockFile ( const string nombre );
    ~LockFile();

    int tomarLock ();
    int liberarLock ();
    ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
    ssize_t leer ( void* buffer,const ssize_t buffsize ) const;
};


#endif //CLIENTE_BDD_LOCKFILE_H
