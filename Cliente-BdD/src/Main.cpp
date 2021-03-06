#include <iostream>
#include "../include/Conector.h"
#include "../include/Logger.h"
#include "../include/BdD.h"
#include "../include/ipc/signal/impl/SIGINT_Handler.h"
#include "../include/ipc/signal/SignalHandler.h"

using namespace std;

const char INGRESAR = '1';
const char BUSCAR = '2';
const char SALIR = '3';

void ingresarPersona(Persona* persona){
    string input;
    cout << "Ingrese el nombre: " << endl;
    getline(cin, input);
    getline(cin, input); //Es necesario doble aca. Arrastra del cin del main.
    strcpy(persona->nombre, input.c_str());

    cout << "Ingrese la direccion: " << endl;
    getline(cin, input);
    strcpy(persona->direccion, input.c_str());

    cout << "Ingrese el telefono: " << endl;
    getline(cin, input);
    strcpy(persona->telefono, input.c_str());
}

int main() {
    SIGINT_Handler sigint_handler;
    SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

    Conector* conector = new Conector();
    if ( conector->conectar() ) {
        Logger :: getInstance() -> info( "Cliente", "Soy el cliente nro " + to_string(conector->verNroCliente()) + " y me voy a conectar");
        long nroCliente = conector->verNroCliente();

        BdD* bdd = new BdD(nroCliente);

        cout << "¡Bienvenido! Se ha conectado a la Base de Datos" << endl;
        while ( sigint_handler.getGracefulQuit() == 0 ) {
            char input;
            cout << "Indique la accion a realizar:" << endl;
            cout << "1 - Si desea ingresar un nuevo registro." << endl;
            cout << "2 - Si desea realizar una busqueda." << endl;
            cout << "3 - Si desea desconectarse y salir de la Base de Datos." << endl;
            cin >> input;

            Persona personaIngresada;
            vector<Persona> personasEncontradas;
            switch (input){
                case (INGRESAR):
                    Persona personaIngresar;
                    cout << "INGRESAR NUEVA PERSONA A LA BASE DE DATOS" << endl;
                    ingresarPersona(&personaIngresar);

                    personaIngresada = bdd->insertar(personaIngresar);
                    if (strcmp (personaIngresada.nombre, "N/N") == 0) {
                        perror("No se pudo insertar a la persona como registro en la base de datos");
                        break;
                    }
                    cout << "Se ha insertado correctamente a la Base de Datos el siguiente registro:" << endl;
                    cout << "Nombre: " << personaIngresada.nombre << " - Direccion: " <<
                         personaIngresada.direccion << " - Telefono: " << personaIngresada.telefono << endl;
                    break;

                case (BUSCAR):
                    Persona personaBuscar;
                    cout << "BUSQUEDA EN LA BASE DE DATOS" << endl;
                    ingresarPersona(&personaBuscar);
                    cout << "PERSONA BUSCADA: Nombre: " << personaBuscar.nombre << " - Direccion: " <<
                         personaBuscar.direccion << " - Telefono: " << personaBuscar.telefono << endl;

                    cout << "El resultado de la busqueda fue:" << endl;
                    personasEncontradas = bdd->buscar(personaBuscar);
                    for (int i = 0; i < personasEncontradas.size(); i++){
                        Persona personaEncontrada = personasEncontradas.at(i);
                        if (strcmp (personaEncontrada.nombre, "N/N") == 0) {
                            cout << "No se encontraron resultados." << endl;
                        } else {
                        cout << "Nombre: " << personaEncontrada.nombre << " - Direccion: " <<
                             personaEncontrada.direccion << " - Telefono: "<< personaEncontrada.telefono << endl;
                        }
                    }
                    break;

                case (SALIR):
                    Logger :: getInstance() -> info( "Cliente", "Soy el cliente nro " + to_string(conector->verNroCliente()) + " y me voy a desconectar" );
                    delete bdd;
                    SignalHandler :: destruir ();
                    Logger :: destruir();
                    conector->desconectar();
                    delete conector;
                    exit(0);

                default:
                    cout << "No ha seleccionado ninguna opcion valida." << endl;
                    break;
            }
        }

        delete bdd;
    } else {
        cout << "No se pudo conectar el cliente a la base de datos. Intentar reiniciando el gestor para regenerar el contador de conexiones." << endl;
    }
    SignalHandler :: destruir ();

    Logger :: destruir ();
    delete conector;

    return 0;
}