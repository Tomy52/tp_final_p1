#include "pila.h"
#include "Venta.h"


void inicpila(P_Pila p)
{
       Venta *aux;
       aux = (Venta *)malloc(50*sizeof(Venta));
       p->valores = aux;
       p->postope=0;
}

void apilar(P_Pila p, Venta venta)
{
    int index = (*p).postope;
    (*p).valores[index]=venta;
    (*p).postope = (*p).postope + 1;
}

Venta desapilar(P_Pila p)
{
       Venta z = p->valores[p->postope -1];
       p->postope--;
       return z;
}

Venta tope(P_Pila p)
{
       return p->valores[p->postope - 1];
}

int pilavacia(P_Pila p)
{
       return (p->postope == 0);
}

void leer (P_Pila p, FILE *ventas)
{
    Venta aux;
    rewind(ventas);
    if (p->postope < 50) {
        while (fread(&aux,sizeof(Venta),1,ventas) != 0) {
            apilar(p, aux);
        }
    } else {
        printf("Error: la pila esta llena");
    }
}

void mostrar(P_Pila p)
{
    int i;
    printf("\nBase .............................................. Tope\n\n");
    for(i=0; i < p->postope; i++)
        printf("| %.2f ", p->valores[i].ganancia);
    printf("\n\nBase .............................................. Tope\n\n");
}

Venta menorElemento(P_Pila p) {
    Pila aux;
    inicpila(&aux);
    Venta menor = tope(p);
    while (!pilavacia(p)) {
        if (tope(p).ganancia < menor.ganancia) {
            menor = tope(p);
        }
        apilar(&aux,desapilar(p));
    }
    while(!pilavacia(&aux)) {
        if (tope(&aux).ganancia == menor.ganancia) {
            desapilar(&aux);
        } else {
            apilar(p,desapilar(&aux));
        }
    }
    return menor;
}

Pila pilaOrdenada(P_Pila p) {
    Pila ordenada;
    inicpila(&ordenada);
    while(!pilavacia(p)) {
        apilar(&ordenada,menorElemento(p));
    }
    return ordenada;
}

