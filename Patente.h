#ifndef PATENTE_H_INCLUDED
#define PATENTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct {
char letras[4];
char numeros[4];
} Patente;

Patente agregarPatente();
void verPatente(Patente patente);
int compararPatente(Patente patenteA, Patente patenteB);

#endif // PATENTE_H_INCLUDED
