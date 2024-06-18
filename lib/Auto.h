#ifndef AUTO_H_INCLUDED
#define AUTO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Patente.h"
#include "Persona.h"

typedef struct {
Patente patente;
char marca[30];
char modelo[30];
int anio;
int kms;
int dniTitular;
float precioDeAdquisicion;
} AutoArchivo;

typedef struct {
Patente patente;
char marca[30];
char modelo[30];
int anio;
int kms;
Persona Titular;
float precioDeAdquisicion;
} Auto;

void agregarAuto(FILE *archAuto);
Auto obtenerAutoDeArchivo(FILE *archAuto, FILE *personas);
void verAuto(Auto coche);
void verListadoAutos(FILE *archAuto);
Auto convertirAuto(AutoArchivo autoDeArchivo, FILE *personas);
int cantAutosEnVenta(FILE *archAuto);
Auto* obtenerAutosEnVenta(FILE *archAuto,FILE *personas);
void verArregloDeAutos(Auto *arregloAutos, int validos);
int cantAutosMenoresADiezAnios(FILE *archAuto);
Auto* obtenerAutosMenoresADiezAnios(FILE *archAuto, FILE *personas);
Auto* ordenarPorAntiguedad(Auto *arregloAutos, int validos);

#endif // AUTO_H_INCLUDED
