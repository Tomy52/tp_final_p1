#include "Patente.h"
#include <stdio.h>
#include <stdlib.h>

Patente agregarPatente() {
    Patente patente;
    char patenteString[7];
    int caracteresCorrectos = 0;

    while (caracteresCorrectos != 6 ) {
        printf("Patente: ");
        fflush(stdin);
        scanf("%6s", patenteString);

        for (int i = 0; i < 3; i++) {
            if (isalpha(patenteString[i]) != 0) {
                patente.letras[i] = patenteString[i];
                caracteresCorrectos++;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (isdigit(patenteString[i + 3]) != 0) {
                patente.numeros[i] = patenteString[i + 3];
                caracteresCorrectos++;
            }
        }

        if (caracteresCorrectos < 6) {
            printf("La patente contiene errores, intente nuevamente\n");
            caracteresCorrectos = 0;
        }
    }

    return patente;
}

void verPatente(Patente patente) {
    printf("Patente: %s%s\n",patente.letras,patente.numeros);
}

int compararPatente(Patente patenteA, Patente patenteB) {
    int flag = 1;

    if (strcmp(patenteA.letras,patenteB.letras) != 0) {
        flag = 0;
    }

    if (strcmp(patenteA.numeros,patenteB.numeros) != 0) {
        flag = 0;
    }

    return flag;
}
