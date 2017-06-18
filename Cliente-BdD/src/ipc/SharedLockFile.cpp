
#include "../../include/ipc/SharedLockFile.h"

SharedLockFile :: SharedLockFile ( const string nombre ) {

    this->nombre = nombre;
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;

    crearDirectorioSiNoExiste(nombre);
    this->fd = open ( this->nombre.c_str(),O_CREAT|O_RDONLY,0777 );
}

int SharedLockFile :: tomarLock () {
    this->fl.l_type = F_WRLCK;
    return fcntl ( this->fd,F_SETLKW,&(this->fl) );
}

int SharedLockFile :: liberarLock () {
    this->fl.l_type = F_UNLCK;
    return fcntl ( this->fd,F_SETLK,&(this->fl) );
}

ssize_t SharedLockFile :: leer ( void* buffer,const ssize_t buffsize ) const {
    return read ( this->fd,buffer,buffsize );
}

SharedLockFile :: ~SharedLockFile () {
    close ( this->fd );
}

int SharedLockFile :: crearDirectorioSiNoExiste ( string rutaCompletaArchivo ) {
    string path = rutaCompletaArchivo.substr(0, rutaCompletaArchivo.find_last_of("\\/"));
    DIR* dir = opendir(path.c_str());
    if (dir) {
        return closedir(dir);
    }
    else if (ENOENT == errno) {
        return mkdir(path.c_str(), 0777);
    }
}