#include <stdio.h>
#include <stdlib.h>

typedef struct {
char nombre[30];
char clave[30];
} Usuario;

typedef struct {
char letras[3];
char numeros[3];
} Patente;

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
int dni;
char nombre[30];
int telefono;
char direccion[30];
char rol[30]; //comprador o vendedor
} Persona;

typedef struct {
Patente patente;
char marca[30];
char modelo[30];
int anio;
int kms;
Persona Titular;
float precioDeAdquisicion;
} Auto;

typedef struct {
int dia;
int mes;
int anio;
} Fecha;

typedef struct {
Fecha fecha;
Patente autoAVender;
float precioVenta;
float ganancia;
int dniComprador;
int dniVendedor;
} Venta;

int main()
{
    return 0;
}
