
#include "../include/Buscador.h"
#include "../include/utils.h"

Buscador::Buscador() {

}

Buscador::~Buscador() {

}

vector<Persona> Buscador::buscar(Persona filtros) {
    Utilidades::crearDirectorio(RUTA_ARCHIVO_BDD);
    SharedLockFile lockLectura = SharedLockFile (RUTA_ARCHIVO_BDD);
    lockLectura.tomarLock();
    vector<Persona> resultado = vector<Persona>();
    std::ifstream input(RUTA_ARCHIVO_BDD);
    std::string linea, nombreBuscado = "$", direccionBuscada = "$", telefonoBuscado = "$";

    if (nombreBuscado.length() > 0) nombreBuscado = filtros.nombre ;
    if (direccionBuscada.length() > 0)direccionBuscada = filtros.direccion;
    if (telefonoBuscado.length() > 0) telefonoBuscado = filtros.telefono;
    std::regex regNombre(nombreBuscado, regex_constants::icase),regDireccion(direccionBuscada, regex_constants::icase),
            regTelefono(telefonoBuscado);

    while (std::getline(input, linea)) {
        std::string nombreLinea, direccionLinea, telefonoLinea;

        nombreLinea = linea.substr(0, linea.find(DELIMITADOR));

        linea =  linea.substr(linea.find(DELIMITADOR)+1, linea.length());
        direccionLinea =  linea.substr(0, linea.find(DELIMITADOR));

        linea = linea.substr(linea.find(DELIMITADOR)+1, linea.length());
        telefonoLinea = linea;

        if (regex_search(nombreLinea, regNombre) && regex_search(direccionLinea, regDireccion) &&
                regex_search(telefonoLinea, regTelefono)) {
            Persona personaValida;
            strcpy(personaValida.nombre, nombreLinea.c_str());
            strcpy(personaValida.direccion, direccionLinea.c_str());
            strcpy(personaValida.telefono, telefonoLinea.c_str());
            personaValida.faltanResultados = true;
            resultado.push_back(personaValida);
        }
    }
    lockLectura.liberarLock();
    if (resultado.size() == 0){
        Persona noEncontrado;
        strcpy(noEncontrado.nombre, "N/N");
        resultado.push_back(noEncontrado);
    }
    resultado.back().faltanResultados = false;
    return resultado;
}
