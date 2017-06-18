#include <iostream>
#include "../include/DespachanteConsultas.h"
#include "../include/Logger.h"

int main() {
    std::cout << "Soy gestor!" << std::endl;

    // TODO: Crear archivo temporal de cantClientes.txt que usan los clientes e inicializarlo en 0.

    DespachanteConsultas despachante = DespachanteConsultas ();
    while (true) {  // TODO: Usar gracefulQuit con signals para matar el servidor.
        Logger :: getInstance() -> info( "Gestor", "Esperando consulta..." );
        despachante.despachar();
        sleep(1);   // TODO: Sacar el sleep!
    }

    // TODO: Borrar archivo temporal cantClientes.txt

    return 0;
}