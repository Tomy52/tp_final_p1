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

    cocheAGuardar.dniTitular = 0;

    fwrite(&cocheAGuardar,sizeof(AutoArchivo),1,archAuto);
}

Auto obtenerAutoDeArchivo(FILE *archAuto, FILE *personas) {
    Patente *areaPatente = calloc(2,sizeof(Patente));
    AutoArchivo cocheDeArchivo;
    Auto coche;

    int encontrado = 0;

    while (encontrado == 0) {
        areaPatente[1] = agregarPatente();
        strncpy(areaPatente[2].letras,areaPatente[1].letras,3);
        strncpy(areaPatente[2].numeros,areaPatente[1].numeros,3);

        fseek(archAuto,0,SEEK_SET);
        while(fread(&cocheDeArchivo,sizeof(AutoArchivo),1,archAuto) != 0) {
            if (compararPatente(areaPatente[2],cocheDeArchivo.patente) == 1) {
                coche = convertirAuto(cocheDeArchivo,personas);

                encontrado = 1;
            }
        }

        if (encontrado == 0) {
            printf("No se pudo encontrar el auto con la patente solicitada, intente nuevamente\n");
        }
    }

    return coche;
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

Auto convertirAuto(AutoArchivo autoDeArchivo, FILE *personas) {
    Auto autoConvertido;

    autoConvertido.patente = autoDeArchivo.patente;
    strcpy(autoConvertido.marca,autoDeArchivo.marca);
    strcpy(autoConvertido.modelo,autoDeArchivo.modelo);
    autoConvertido.anio = autoDeArchivo.anio;
    autoConvertido.kms = autoDeArchivo.kms;
    autoConvertido.Titular = obtenerPersonaPorDNI(personas,autoDeArchivo.dniTitular);
    autoConvertido.precioDeAdquisicion = autoDeArchivo.precioDeAdquisicion;

    return autoConvertido;
}

int cantAutosEnVenta(FILE *archAuto) {
    AutoArchivo coche;
    int autosEnVenta = 0;

    fseek(archAuto,0,SEEK_SET);
    while(fread(&coche,sizeof(AutoArchivo),1,archAuto) != 0) {
        if (coche.dniTitular == 0) {
            autosEnVenta++;
        }
    }

    return autosEnVenta;
}

Auto* obtenerAutosEnVenta(FILE *archAuto, FILE *personas) {
    Auto *autosEnVenta = malloc(cantAutosEnVenta(archAuto)*(sizeof(Auto)));
    AutoArchivo coche;
    int i = 0;

    fseek(archAuto,0,SEEK_SET);
    while(fread(&coche,sizeof(AutoArchivo),1,archAuto) != 0) {
        if (coche.dniTitular == 0) {
            autosEnVenta[i] = convertirAuto(coche,personas);
            i++;
        }
    }

    return autosEnVenta;
}

void verAutosEnVenta(Auto *autosEnVenta, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        verAuto(autosEnVenta[i]);
    }
}
