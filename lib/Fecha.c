#include "Fecha.h"
#include <stdio.h>
#include <stdlib.h>

Fecha crearFecha() {
    Fecha fecha;
    int dia;
    int mes;
    int anio;
    int formatoCorrecto = 0;

    while (formatoCorrecto == 0) {
        printf("Ingrese el dia: ");
        scanf("%d", &dia);

        printf("Ingrese el mes: ");
        scanf("%d", &mes);

        printf("Ingrese el anio: ");
        scanf("%d", &anio);

        if (anio > 0 && mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31) {
            fecha.dia = dia;
            fecha.mes = mes;
            fecha.anio = anio;
            formatoCorrecto = 1;
        } else {
            printf("La fecha contiene errores\n");
        }
    }

    return fecha;
}

void verFecha(Fecha fecha) {
    printf("%i/%i/%i",fecha.dia,fecha.mes,fecha.anio);
}

int compararFecha(Fecha fechaA, Fecha fechaB) {
    int flag = 1;

    if (fechaA.anio != fechaB.anio) {
        flag = 0;
    }

    if (fechaA.mes != fechaB.mes) {
        flag = 0;
    }

    if (fechaA.dia != fechaB.dia) {
        flag = 0;
    }

    return flag;
}
