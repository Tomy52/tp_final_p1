#include <stdio.h>
#include <stdlib.h>
#include "Usuario.h"
#include "Persona.h"
#include "Auto.h"
#include "Fecha.h"

typedef struct {
Fecha fecha;
Patente autoAVender;
float precioVenta;
float ganancia;
int dniComprador;
int dniVendedor;
} Venta;

void menuUsuario();
void menuConcesionaria();

int logueado = 0;

int main() {
    menuUsuario();
    if (logueado == 1) {
        menuConcesionaria();
    }
    return 0;
}

void menuUsuario() {
    FILE *usuarios = fopen("usuarios.bin", "ab+");
    if (usuarios != NULL)
    {
        int opcion = 0;

        printf("Bienvenido! Elija alguna opcion antes de continuar:\n");

        while(opcion != 3 && logueado == 0)
        {
            printf("1. Agregar usuario\n");
            printf("2. Iniciar sesion\n");
            printf("3. Salir\n");
            printf("Opcion elegida: ");
            scanf("%d", &opcion);

            switch(opcion)
            {
            case 1:
                agregarUsuario(usuarios);
                break;
            case 2:
                logueado = login(usuarios);
                break;
            case 3:
                break;
            default:
                printf("Elija una opcion valida\n");
                break;
            }
        }
        fclose(usuarios);
    }
    else
    {
        printf("Archivo invalido");
    }
}

void menuConcesionaria() {
    FILE *autos = fopen("autosArch.bin", "ab+");
    FILE *personas = fopen("personas.bin", "ab+");
    FILE *ventas = fopen("ventas.bin", "ab+");

    if (autos != NULL && personas != NULL && ventas != NULL)
    {
        int opcion = 0;

        printf("Bienvenido a la concesionaria:\n");

        while(opcion != 7)
        {
            printf("1. Agregar un auto al stock\n");
            printf("2. Agregar una persona\n");
            printf("3. Ver listado resumido de personas\n");
            printf("4. Ver informacion de una persona (por DNI)\n");
            printf("5. Ver listado resumido de autos\n");
            printf("6. Ver informacion de un auto (por patente)\n");
            printf("7. Salir\n");
            printf("Opcion elegida: ");
            scanf("%d", &opcion);

            switch(opcion)
            {
                case 1:
                    agregarAuto(autos);
                    break;
                case 2:
                    agregarPersona(personas);
                    break;
                case 3:
                    verListadoPersonas(personas);
                    break;
                case 4:
                    verPersonaPorDNI(personas);
                    break;
                case 5:
                    verListadoAutos(autos);
                    break;
                case 6:
                    verAutoDeArchivo(autos,personas);
                    break;
                case 7:
                    break;
                default:
                    printf("Elija una opcion valida\n");
                    break;
            }
        }
        fclose(autos);
        fclose(ventas);
        fclose(personas);
    }
    else
    {
        printf("Error en la lectura de los archivos necesarios para trabajar");
    }
}
