#include <iostream>
#include "../include/Conector.h"
#include "../include/Logger.h"

int main() {
    std::cout << "Soy cliente!" << std::endl;

    Conector conector = Conector ();
    conector.conectar();
    Logger :: getInstance() -> info( "Cliente", "Soy el cliente nro " + to_string(conector.nroCliente()) );
    conector.desconectar();

    return 0;
}