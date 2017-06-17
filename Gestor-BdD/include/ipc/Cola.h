#ifndef GESTOR_BDD_COLA_H
#define GESTOR_BDD_COLA_H

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>

template <class T> class Cola {
private:
    int		id;

public:
    Cola ( const std::string& archivo,const char letra );
    ~Cola();
    int escribir ( const T& dato ) const;
    ssize_t leer ( const int tipo,T* buffer ) const;
    ssize_t leerProximo ( T* buffer ) const;
    int destruir () const;
};

template <class T> Cola<T> :: Cola ( const std::string& archivo,const char letra ) {
    key_t clave = ftok ( archivo.c_str(),letra );
    if ( clave == -1 )
        perror ( "Error en ftok" );

    this->id = msgget ( clave,0777|IPC_CREAT );
    if ( this->id == -1 )
        perror ( "Error en msgget" );
}

template <class T> Cola<T> :: ~Cola () {
}

template <class T> int Cola<T> :: destruir () const {
    return msgctl ( this->id,IPC_RMID,NULL );
}

template <class T> int Cola<T> :: escribir ( const T& dato ) const {
    return msgsnd ( this->id,static_cast<const void*>(&dato),sizeof(T)-sizeof(long),0 );
}

template <class T> ssize_t Cola<T> :: leer ( const int tipo,T* buffer ) const {
    return msgrcv ( this->id,static_cast<void *>(buffer),sizeof(T)-sizeof(long),tipo,0 );
}

template <class T> ssize_t Cola<T> :: leerProximo ( T* buffer ) const {
    return msgrcv ( this->id,static_cast<void *>(buffer),sizeof(T)-sizeof(long),0,0 );
}

#endif //GESTOR_BDD_COLA_H
