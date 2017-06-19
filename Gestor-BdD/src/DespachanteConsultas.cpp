
#include "../include/DespachanteConsultas.h"

DespachanteConsultas::DespachanteConsultas() {
    this->consultas = new Cola<Persona> ( "/bin/bash", 'q' );
}

DespachanteConsultas::~DespachanteConsultas() {
    this->consultas->destruir();
    delete this->consultas;
}

void DespachanteConsultas::despachar() {
    Persona consulta;
    int lecturaCorrecta = this->consultas->leer(PETICION, &consulta);

    if (lecturaCorrecta > 0) {
        pid_t pid = fork();
        if (pid == 0) {

            if (consulta.tipoConsulta == BUSQUEDA) {
                Buscador buscador = Buscador();
                vector<Persona> respuesta = buscador.buscar(consulta);

                for (int i = 0; i < respuesta.size(); i++) {
                    Persona aEncolar = respuesta.at(i);
                    aEncolar.mtype = RESPUESTA;
                    cout << "Cliente NRO: " << consulta.id << endl; //de prueba dsp borrar.
                    aEncolar.id = consulta.id;
                    aEncolar.esUnicoResultado = 1; // TODO: de prueba, deberia ir en el Buscador
                    this->consultas->escribir(aEncolar);
                    Logger::getInstance()->info("Gestor", "Resultado de Búsqueda encolado");
                }
                Logger :: getInstance() -> info( "Gestor", "Consulta de busqueda resuelta" );

            } else if (consulta.tipoConsulta == INSERCION) {
                Insertor insertor = Insertor();
                insertor.insertar(consulta);
                //// Devuelvo lo mismo como confirmacion de que ya se persistio el dato:
                consulta.mtype = RESPUESTA;
                this->consultas->escribir(consulta);
                Logger::getInstance()->info("Gestor", "Consulta de insercion resuelta");
            }
            exit(0);
        }
    }
}
