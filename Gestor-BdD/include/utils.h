
#ifndef GESTOR_BDD_UTILS_H
#define GESTOR_BDD_UTILS_H

#include <dirent.h>
#include <sys/stat.h>
#include <string>

#define RUTA_ARCHIVO_BDD "../../bdd/registros.txt"
#define DELIMITADOR ","

class Utilidades
{
    public:
        static int crearDirectorio(std::string path);
};

#endif //GESTOR_BDD_UTILS_H
