
#ifndef CLIENTE_BDD_SHAREDLOCKFILE_H
#define CLIENTE_BDD_SHAREDLOCKFILE_H

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

class SharedLockFile {

private:
    struct flock fl;
    int fd;
    string nombre;

    int crearDirectorioSiNoExiste (string rutaCompletaArchivo);

public:
    SharedLockFile ( const string nombre );
    ~SharedLockFile ();

    int tomarLock ();
    int liberarLock ();
    ssize_t leer ( void* buffer,const ssize_t buffsize ) const;

};


#endif //CLIENTE_BDD_SHAREDLOCKFILE_H
