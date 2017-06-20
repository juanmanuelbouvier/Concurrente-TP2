
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
    std::regex regNombre(nombreBuscado,regex_constants::icase),regDireccion(direccionBuscada,regex_constants::icase),
            regTelefono(telefonoBuscado);
    while (std::getline(input,linea)) {
        std::string nombreLinea,direccionLinea,telefonoLinea;
        nombreLinea = linea.substr(0,linea.find(DELIMITADOR));
        linea =  linea.substr(linea.find(DELIMITADOR)+1,linea.length());
        direccionLinea =  linea.substr(0,linea.find(DELIMITADOR));
        linea = linea.substr(linea.find(DELIMITADOR)+1,linea.length());
        telefonoLinea = linea;
        if (regex_search(nombreLinea,regNombre) && regex_search(direccionLinea,regDireccion) &&
                regex_search(telefonoLinea,regTelefono)) {
            Persona personaValida;
            strncpy(personaValida.nombre,nombreLinea,sizeof(personaValida.nombre) -1);
            strncpy(personaValida.direccion,direccionLinea,sizeof(personaValida.direccion)-1);
            strncpy(personaValida.telefono,telefonoLinea,sizeof(personaValida.telefono)-1);
            resultado.push_back(personaValida);
        }

    }
    return resultado;
}
