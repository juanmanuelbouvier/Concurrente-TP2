
#include "../include/Buscador.h"

Buscador::Buscador() {

}

Buscador::~Buscador() {

}

vector<Persona> Buscador::buscar(Persona filtros) {
    // TODO: Acceder en modo lectura al archivo de la base de datos.
    vector<Persona> resultado = vector<Persona>();
    resultado.push_back(filtros);
    return resultado;
}
