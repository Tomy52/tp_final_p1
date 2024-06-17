#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "Persona.h"
#include "Auto.h"
#include "Fecha.h"

typedef struct {
Fecha fecha;
Patente autoAVender;
float precioVenta;
float ganancia;
int dniComprador;
int dniVendedor;
} Venta;

void agregarVenta(FILE *ventas,FILE *autos, FILE *personas);
void verVenta(Venta venta);
Venta obtenerVentaDeArchivo(FILE *ventas);

#endif // VENTA_H_INCLUDED
