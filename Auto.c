#include "Auto.h"
#include "Patente.h"
#include "Persona.h"
#include <stdio.h>
#include <stdlib.h>

void agregarAuto(FILE *archAuto) {
    AutoArchivo cocheAGuardar;

    cocheAGuardar.patente = agregarPatente();
    printf("Marca: ");
    fflush(stdin);
    scanf("%s",cocheAGuardar.marca);

    printf("Modelo: ");
    fflush(stdin);
    scanf("%s",cocheAGuardar.modelo);

    printf("Anio: ");
    fflush(stdin);
    scanf("%i",&cocheAGuardar.anio);

    printf("Kilometraje: ");
    fflush(stdin);
    scanf("%i",&cocheAGuardar.kms);

    printf("Precio de adquisicion: ");
    fflush(stdin);
    scanf("%f",&cocheAGuardar.precioDeAdquisicion);

    fwrite(&cocheAGuardar,sizeof(AutoArchivo),1,archAuto);
}

void verAutoDeArchivo(FILE *archAuto, FILE *personas) {
    AutoArchivo cocheDeArchivo;
    Auto coche;
    Patente patenteBuscada = agregarPatente();
    int encontrado = 0;

    fseek(archAuto,0,SEEK_SET); // reemplazar por rewind
    while(fread(&cocheDeArchivo,sizeof(AutoArchivo),1,archAuto) != 0 && encontrado == 0) {
        if (compararPatente(patenteBuscada,cocheDeArchivo.patente) == 1) {
            encontrado = 1;

            coche.patente = patenteBuscada;
            strcpy(coche.marca,cocheDeArchivo.marca);
            strcpy(coche.modelo,cocheDeArchivo.modelo);
            coche.anio = cocheDeArchivo.anio;
            coche.kms = cocheDeArchivo.kms;
            coche.Titular = obtenerPersonaPorDNI(personas,cocheDeArchivo.dniTitular);
            coche.precioDeAdquisicion = cocheDeArchivo.precioDeAdquisicion;

            verAuto(coche);
        }
    }

    if (encontrado == 0) {
        printf("No se encontro el coche con la patente solicitada\n");
    }
}

void verAuto(Auto coche) {
    printf("\n- Informacion del coche - \n");
    verPatente(coche.patente);
    printf("Marca: %s\n",coche.marca);
    printf("Modelo: %s\n",coche.modelo);
    printf("Anio: %i\n",coche.anio);
    printf("Kilometros: %i\n",coche.kms);
    printf("Precio de adquisicion: $%.2f\n",coche.precioDeAdquisicion);

    if (coche.Titular.dni == 0) {
        printf("En poder de la concesionaria\n\n");
    } else {
        printf("\n- Informacion del titular - \n");
        verPersona(coche.Titular);
        printf("\n");
    }
}

void verListadoAutos(FILE *archAuto) {
    Auto coche;

    fseek(archAuto,0,SEEK_SET); //reemplazar por rewind
    while(fread(&coche,sizeof(AutoArchivo),1,archAuto) != 0) {
        printf("\nMarca: %s\n",coche.marca);
        printf("Modelo: %s\n",coche.modelo);
        verPatente(coche.patente);
        printf("\n");
    }
}
