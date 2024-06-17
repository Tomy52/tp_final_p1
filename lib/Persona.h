#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct {
int dni;
char nombre[30];
int telefono;
char direccion[30];
char rol[30]; //comprador o vendedor
} Persona;

void agregarPersona(FILE *personas);
void verPersona(Persona persona);
void verListadoPersonas(FILE *personas);
void verPersonaPorDNI(FILE *personas);
Persona obtenerPersonaPorDNI(FILE *personas, int dni);

#endif // PERSONA_H_INCLUDED
