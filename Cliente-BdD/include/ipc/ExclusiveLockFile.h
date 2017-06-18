
#ifndef CLIENTE_BDD_LOCKFILE_H
#define CLIENTE_BDD_LOCKFILE_H

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

class ExclusiveLockFile {

private:
    struct flock fl;
    int fd;
    string nombre;

    int crearDirectorioSiNoExiste (string rutaCompletaArchivo);

public:
    ExclusiveLockFile ( const string nombre );
    ~ExclusiveLockFile();

    int tomarLock ();
    int liberarLock ();
    ssize_t escribir ( const void* buffer,const ssize_t buffsize ) const;
    ssize_t remplazar ( const void* buffer,const ssize_t buffsize ) const;
};


#endif //CLIENTE_BDD_LOCKFILE_H
