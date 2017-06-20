
#include "../include/utils.h"



 int Utilidades::crearDirectorio(std::string pathArchivo) {
     std::string path = pathArchivo.substr(0, pathArchivo.find_last_of("\\/"));
     DIR* dir = opendir(path.c_str());
     if (dir) {
         return closedir(dir);
     }
     else if (ENOENT == errno) {
         return mkdir(path.c_str(), 0777);
     }
     return -1;
}
