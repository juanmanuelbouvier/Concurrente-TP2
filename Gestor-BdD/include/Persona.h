
#ifndef GESTOR_BDD_PERSONA_H
#define GESTOR_BDD_PERSONA_H

#define MAX_NOMBRE      61
#define MAX_DIRECCION   120
#define MAX_TELEFONO    13

typedef struct Persona {
    long mtype;
    char nombre [MAX_NOMBRE];
    char direccion [MAX_DIRECCION];
    char telefono [MAX_TELEFONO];
} Persona;

#endif //GESTOR_BDD_PERSONA_H
