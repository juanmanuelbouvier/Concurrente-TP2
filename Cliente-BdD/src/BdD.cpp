
#include "../include/BdD.h"
#include "../include/Logger.h"

BdD::BdD(long nroCliente) : nroCliente (nroCliente) {
    this->peticiones = new Cola<Persona> ( "/bin/bash", 'p' );
    this->respuestas = new Cola<Persona> ( "/bin/bash", 'r' );
}

BdD::~BdD() {
    delete peticiones;
    delete respuestas;
}

vector<Persona> BdD::buscar(Persona consulta) {
    consulta.mtype = nroCliente;
    consulta.tipoConsulta = BUSQUEDA;
    peticiones->escribir(consulta);
    vector<Persona> respuesta;
    Persona personaEncontrada;
    do {
        respuestas->leer(nroCliente, &personaEncontrada);
        respuesta.push_back(personaEncontrada);
    } while (personaEncontrada.faltanResultados);
    return respuesta;
}

Persona BdD::insertar(Persona nuevaPersona) {
    nuevaPersona.mtype = nroCliente;
    nuevaPersona.tipoConsulta = INSERCION;
    peticiones->escribir(nuevaPersona);
    Persona personaConfirmada;
    respuestas->leer( nroCliente, &personaConfirmada );
    return personaConfirmada;
}
