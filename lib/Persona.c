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

    rewind(personas);
    while(fread(&persona,sizeof(Persona),1,personas) != 0) {
        printf("\nDNI: %i\n",persona.dni);
        printf("Nombre: %s\n\n",persona.nombre);
    }
}

void verPersonaPorDNI(FILE *personas) {
    Persona persona;
    int dniSolicitado = 0;

    printf("Ingrese el DNI de la persona a buscar: ");
    fflush(stdin);
    scanf("%i",&dniSolicitado);

    verPersona(obtenerPersonaPorDNI(personas,dniSolicitado));
}

Persona obtenerPersonaPorDNI(FILE *personas, int dni) {
    Persona persona;
    int encontrada = 0;

    rewind(personas);
    while(fread(&persona,sizeof(Persona),1,personas) != 0 && encontrada == 0) {
        if (persona.dni == dni) {
            encontrada = 1;
            break;
        }
    }

    if (encontrada == 0) {
        persona.dni = dni;
        if (dni == 0)
        {
            strcpy(persona.nombre,"Concesionaria");
        }
        else
        {
            strcpy(persona.nombre,"");
        }
        persona.telefono = 0;
        strcpy(persona.direccion,"");
        strcpy(persona.rol,"");
    }

    return persona;
}
