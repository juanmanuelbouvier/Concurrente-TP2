
#include "../include/DespachanteConsultas.h"

DespachanteConsultas::DespachanteConsultas() {
    this->consultas = new Cola<Persona> ( "/bin/bash", 'q' );
}

DespachanteConsultas::~DespachanteConsultas() {
    this->consultas->destruir();
    delete this->consultas;
}

void DespachanteConsultas::despachar() {
    pid_t pid = fork();
    if (pid == 0) {
        Persona consulta;
        this->consultas->leerProximo(&consulta);
        if (consulta.tipoConsulta == BUSQUEDA) {
            Buscador buscador = Buscador();
            vector<Persona> respuesta = buscador.buscar(consulta);
            for (int i = 0; i < respuesta.size(); i++) {
                Persona aEncolar = respuesta.at(i);
                aEncolar.mtype = consulta.mtype;
                this->consultas->escribir( aEncolar );
            }
            Logger :: getInstance() -> info( "Gestor", "Consulta de busqueda resuelta" );
        } else if (consulta.tipoConsulta == INSERCION) {
            Insertor insertor = Insertor();
            insertor.insertar(consulta);
            this->consultas->escribir( consulta );  // Devuelvo lo mismo como confirmacion de que ya se persistio el dato.
            Logger :: getInstance() -> info( "Gestor", "Consulta de insercion resuelta" );
        }
        exit(0);
    }
}
