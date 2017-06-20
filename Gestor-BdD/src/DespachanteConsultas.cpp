
#include <cstring>
#include "../include/DespachanteConsultas.h"

DespachanteConsultas::DespachanteConsultas() {
    this->peticiones = new Cola<Persona> ( "/bin/bash", 'p' );
    this->respuestas = new Cola<Persona> ( "/bin/bash", 'r' );
}

DespachanteConsultas::~DespachanteConsultas() {
    this->peticiones->destruir();
    delete this->peticiones;

    this->respuestas->destruir();
    delete this->respuestas;
}

void DespachanteConsultas::despachar() {
    Persona consulta;
    ssize_t lecturaCorrecta = this->peticiones->leerProximo(&consulta);

    if (lecturaCorrecta > 0) {
        pid_t pid = fork();
        if (pid == 0) {
            long nroCliente = consulta.mtype;
            if (consulta.tipoConsulta == BUSQUEDA) {
                Buscador buscador = Buscador();
                vector<Persona> respuesta = buscador.buscar(consulta);

                for (int i = 0; i < respuesta.size(); i++) {
                    Persona aEncolar = respuesta.at(i);
                    aEncolar.mtype = nroCliente;
                    aEncolar.faltanResultados = false; // TODO: de prueba, deberia ir en el Buscador
                    this->respuestas->escribir(aEncolar);
                    Logger::getInstance()->info("Gestor", "Resultado de Búsqueda encolado");
                }
                Logger :: getInstance() -> info( "Gestor", "Consulta de busqueda resuelta" );

            } else if (consulta.tipoConsulta == INSERCION) {
                Insertor insertor = Insertor();
                bool ok = insertor.insertar(consulta);
                if (ok) {
                    this->respuestas->escribir(consulta);    // Devuelvo lo mismo como confirmacion de que ya se persistio el dato.
                } else {
                    Persona NN;
                    strcpy(NN.nombre, "N/N");
                    NN.mtype = nroCliente;
                    this->respuestas->escribir(NN);
                }
                Logger::getInstance()->info("Gestor", "Consulta de insercion resuelta");
            }
            exit(0);
        }
    }
}
