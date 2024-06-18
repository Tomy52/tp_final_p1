#include <stdio.h>
#include <malloc.h>
#include "Venta.h"
#define Pila struct _Pila
#define P_Pila struct _Pila *

struct _Pila
{
    Venta *valores;
    int postope;
};

void inicpila(P_Pila p);
void apilar(P_Pila p, Venta venta);
void apilar(P_Pila p, Venta venta);
Venta desapilar(P_Pila p);
Venta tope(P_Pila p);
int pilavacia(P_Pila p);
void leer (P_Pila p, FILE *ventas);
void mostrar(P_Pila p);
Venta menorElemento(P_Pila p);
Pila pilaOrdenada(P_Pila p);


