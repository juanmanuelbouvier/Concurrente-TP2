#include <iostream>
#include "../include/Conector.h"
#include "../include/Logger.h"
#include "../include/BdD.h"
#include <string.h>

using namespace std;

const int INGRESAR = 1;
const int BUSCAR = 2;
const int SALIR = 3;

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
    Conector* conector = new Conector();
    conector->conectar();
    Logger :: getInstance() -> info( "Cliente", "Soy el cliente nro " + to_string(conector->nroCliente()) + " y me voy a conectar");
    int nroCliente = conector->nroCliente();

    BdD* bdd = new BdD(nroCliente);

    cout << "¡Bienvenido! Se ha conectado a la Base de Datos" << endl;
    while (true){
        int input;
        cout << "Indique la accion a realizar:" << endl;
        cout << "1 - Si desea ingresar un nuevo registro." << endl;
        cout << "2 - Si desea realizar una busqueda." << endl;
        cout << "3 - Si desea desconectarse y salir de la Base de Datos." << endl;
        cin >> input;

        switch (input){
            case (INGRESAR):
                Persona personaIngresar;
                cout << "INGRESAR NUEVA PERSONA A LA BASE DE DATOS" << endl;
                ingresarPersona(&personaIngresar);
                personaIngresar.mtype = PETICION;
                personaIngresar.id = nroCliente;
                personaIngresar.tipoConsulta = INSERCION;

                Persona personaIngresada;
                personaIngresada = bdd->insertar(personaIngresar);

                cout << "Se ha insertado correctamente a la Base de Datos el siguiente registro:" << endl;
                cout << "Nombre: " << personaIngresada.nombre << " - Direccion: " <<
                     personaIngresada.direccion << " - Telefono: "<< personaIngresada.telefono << endl;
                break;

            case (BUSCAR):
                Persona personaBuscar;
                cout << "BUSQUEDA EN LA BASE DE DATOS" << endl;
                ingresarPersona(&personaBuscar);
                personaBuscar.mtype = PETICION;
                personaBuscar.id = nroCliente;
                personaBuscar.tipoConsulta = BUSQUEDA;
                cout << "PERSONA BUSCADA: " << personaBuscar.nombre << " DIR: " <<
                     personaBuscar.direccion << " TEL: "<< personaBuscar.telefono << endl;

                Persona* resultado;
                resultado = bdd->buscar(personaBuscar);
                //TODO: usar esto cuando se adapte a varios resultados
                /*for (int i = 0; i < resultado->size(); i++){
                    Persona persona = resultado->at(i);
                    cout << "Se han encontrado los siguientes resultados:" << endl;
                    cout << "Nombre: " << persona.nombre << " - Direccion: " <<
                         persona.direccion << " - Telefono: "<< persona.telefono << endl;
                }*/
                cout << "Se han encontrado los siguientes resultados:" << endl;
                cout << "Nombre: " << resultado->nombre << " - Direccion: " <<
                     resultado->direccion << " - Telefono: "<< resultado->telefono << endl;
                break;

            case (SALIR):
                Logger :: getInstance() -> info( "Cliente", "Soy el cliente nro " + to_string(conector->nroCliente()) + " y me voy a desconectar" );
                conector->desconectar();
                delete conector;
                delete bdd;
                exit(0);

            default:
                cout << "No ha seleccionado ninguna opcion valida." << endl;
                break;
        }
    }
}