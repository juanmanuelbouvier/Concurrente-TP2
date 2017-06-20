
#ifndef CLIENTE_BDD_PERSONA_H
#define CLIENTE_BDD_PERSONA_H

#define MAX_NOMBRE      61
#define MAX_DIRECCION   120
#define MAX_TELEFONO    13

static const int BUSQUEDA = 0;
static const int INSERCION = 1;

typedef struct Persona {
    long mtype;
    char nombre [MAX_NOMBRE];
    char direccion [MAX_DIRECCION];
    char telefono [MAX_TELEFONO];
    int tipoConsulta;
    bool esUnicoResultado;
} Persona;


#endif //CLIENTE_BDD_PERSONA_H
