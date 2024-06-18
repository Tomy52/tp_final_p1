#include "Venta.h"
#include <stdio.h>
#include <stdlib.h>
#include "Persona.h"
#include "Auto.h"
#include "Fecha.h"
#include "pila.h"

void agregarVenta(FILE *ventas,FILE *autos, FILE *personas) {
    Venta venta;
    Auto datosAutoAVender;

    rewind(ventas);

    printf ("Ingrese la patente del auto a vender: ");
    datosAutoAVender = obtenerAutoDeArchivo(autos,personas);
    venta.autoAVender = datosAutoAVender.patente;

    printf("Fecha de la venta: ");
    venta.fecha = crearFecha();

    printf("Precio de venta: ");
    scanf("%f",&venta.precioVenta);

    venta.ganancia = venta.precioVenta - datosAutoAVender.precioDeAdquisicion;

    printf("DNI del comprador: ");
    scanf("%i",&venta.dniComprador);

    venta.dniVendedor = datosAutoAVender.Titular.dni;

    fwrite(&venta,sizeof(Venta),1,ventas);
}

void verVenta(Venta venta) {
    printf("\n- Informacion de la venta -\n");
    verPatente(venta.autoAVender);
    printf("Fecha de venta: ");
    verFecha(venta.fecha);
    printf("\nPrecio de venta: %.2f\n",venta.precioVenta);
    printf("Ganancia: %.2f\n",venta.ganancia);
    printf("DNI vendedor: %i\n",venta.dniVendedor);
    printf("DNI comprador: %i\n\n",venta.dniComprador);
}

Venta obtenerVentaDeArchivo(FILE *ventas) {
    Fecha fechaVenta;
    Venta venta;
    int encontrada = 0;

    while (encontrada == 0) {
        rewind(ventas);
        printf("Ingrese la fecha de la venta a buscar:\n");
        fechaVenta = crearFecha();

        while (compararFecha(fechaVenta,venta.fecha) != 1 && fread(&venta,sizeof(Venta),1,ventas) != 0) {
            if (compararFecha(fechaVenta,venta.fecha) == 1) {
                encontrada = 1;
            }
        }

        if (encontrada == 0) {
            printf("La venta hecha en la fecha solicitada no fue encontrada\n");
        }
    }

    return venta;
}

void verGananciaPeriodo(FILE *ventas) {
    Venta venta;
    Fecha periodo;
    float ganancias[31] = {0};
    float total = 0;
    int dia = 0;

    printf("Ingrese el anio que desea buscar: ");
    scanf("%i",&periodo.anio);

    printf("Ingrese el mes que desea buscar: ");
    scanf("%i",&periodo.mes);

    rewind(ventas);

    while (fread(&venta,sizeof(Venta),1,ventas) != 0) {
        if (venta.fecha.anio == periodo.anio && venta.fecha.mes == periodo.mes) {
            ganancias[venta.fecha.dia - 1] = venta.ganancia;
        }
    }

    for (int i = 0; i < 31; i++) {
        total += ganancias[i];
    }


    printf ("\n La ganancia total del periodo fue de $%.2f\n",total);
}

void verVentaMasFavorable(FILE *ventas) {
    Pila pilaVentas;
    inicpila(&pilaVentas);

    leer(&pilaVentas,ventas);
    pilaVentas = pilaOrdenada(&pilaVentas);
    verVenta(tope(&pilaVentas));
}
