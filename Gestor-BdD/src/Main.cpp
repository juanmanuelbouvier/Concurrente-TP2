#include <iostream>
#include "../include/DespachanteConsultas.h"

int main() {
    std::cout << "Soy gestor!" << std::endl;

    // TODO: Crear archivo temporal de cantClientes.txt que usan los clientes e inicializarlo en 0.

    DespachanteConsultas despachante = DespachanteConsultas ();
    while (true) {  // TODO: Usar gracefulQuit con signals para matar el servidor.
        despachante.despachar();
        sleep(1);   // TODO: Si lo sacamos se me muere la compu.
    }

    // TODO: Borrar archivo temporal cantClientes.txt

    return 0;
}