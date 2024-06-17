#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct {
int dia;
int mes;
int anio;
} Fecha;

Fecha crearFecha();
void verFecha(Fecha fecha);
int compararFecha(Fecha fechaA, Fecha fechaB);

#endif // FECHA_H_INCLUDED
