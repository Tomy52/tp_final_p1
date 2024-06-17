#include "Persona.h"
#include <stdio.h>
#include <stdlib.h>

void agregarPersona(FILE *personas) {
    Persona persona;

    printf("DNI: ");
    fflush(stdin);
    scanf("%i",&persona.dni);

    printf("Nombre: ");
    fflush(stdin);
    gets(persona.nombre);

    printf("Telefono: ");
    fflush(stdin);
    scanf("%i",&persona.telefono);

    printf("Direccion: ");
    fflush(stdin);
    gets(persona.direccion);

    printf("Rol (comprador o vendedor): ");
    fflush(stdin);
    scanf("%s", persona.rol);

    fwrite(&persona,sizeof(Persona),1,personas);
}

void verPersona(Persona persona) {
    printf("DNI: %i\n",persona.dni);
    printf("Nombre: %s\n",persona.nombre);
    printf("Telefono: %i\n",persona.telefono);
    printf("Direccion: %s\n",persona.direccion);
    printf("Rol: %s\n",persona.rol);
}

void verListadoPersonas(FILE *personas) {
    Persona persona;

    fseek(personas,0,SEEK_SET); //reemplazar por rewind
    while(fread(&persona,sizeof(Persona),1,personas) != 0) {
        printf("\nDNI: %i\n",persona.dni);
        printf("Nombre: %s\n\n",persona.nombre);
    }
}

void verPersonaPorDNI(FILE *personas) {
    Persona persona;
    int dniSolicitado = 0;
    int encontrada = 0;

    printf("Ingrese el DNI de la persona a buscar: ");
    fflush(stdin);
    scanf("%i",&dniSolicitado);

    fseek(personas,0,SEEK_SET);
    while(fread(&persona,sizeof(Persona),1,personas) != 0 && encontrada == 0) {
        if (persona.dni == dniSolicitado) {
            verPersona(persona);
            encontrada = 1;
        }
    }

    if (encontrada == 0) {
        printf("No se encontro a la persona con el DNI solicitado");
    }
}

Persona obtenerPersonaPorDNI(FILE *personas, int dni) {
    Persona persona;
    int encontrada = 0;

    fseek(personas,0,SEEK_SET);
    while(fread(&persona,sizeof(Persona),1,personas) != 0 && encontrada == 0) {
        if (persona.dni == dni) {
            encontrada = 1;
        }
    }

    if (encontrada == 0) {
        persona.dni = dni;
        strcpy(persona.nombre,"");
        persona.telefono = 0;
        strcpy(persona.direccion,"");
        strcpy(persona.rol,"");
    }

    return persona;
}