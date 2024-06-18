#include <stdio.h>
#include <stdlib.h>
#include "Usuario.h"
#include "Persona.h"
#include "Auto.h"
#include "Fecha.h"
#include "Venta.h"
#include "pila.h"

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
                system("cls");
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

        printf("Menu concesionaria:\n");

        while(opcion != 13)
        {
            printf("1. Agregar un auto al stock\n");
            printf("2. Agregar una persona\n");
            printf("3. Ver listado resumido de personas\n");
            printf("4. Ver informacion de una persona (por DNI)\n");
            printf("5. Ver listado resumido de autos\n");
            printf("6. Ver autos en venta (a nombre de la concesionaria)\n");
            printf("7. Ver informacion de un auto (por patente)\n");
            printf("8. Agregar una venta\n");
            printf("9. Ver una venta (por fecha)\n");
            printf("10. Ver ganancia de un periodo (anio y mes)\n");
            printf("11. Ver venta mas favorable (mayor ganancia)\n");
            printf("12. Ver autos con antiguedad menor a 10 anios\n");
            printf("13. Salir\n");
            printf("Opcion elegida: ");
            scanf("%d", &opcion);

            switch(opcion)
            {
                case 1:
                    agregarAuto(autos);
                    system("cls");
                    break;
                case 2:
                    agregarPersona(personas);
                    system("cls");
                    break;
                case 3:
                    system("cls");
                    verListadoPersonas(personas);
                    break;
                case 4:
                    system("cls");
                    verPersonaPorDNI(personas);
                    break;
                case 5:
                    system("cls");
                    verListadoAutos(autos);
                    break;
                case 6:
                    system("cls");
                    verArregloDeAutos(obtenerAutosEnVenta(autos,personas),cantAutosEnVenta(autos));
                    break;
                case 7:
                    system("cls");
                    verAuto(convertirAuto(obtenerAutoDeArchivo(autos),personas));
                    break;
                case 8:
                    fclose(autos);
                    autos = fopen("autosArch.bin", "rb+");

                    agregarVenta(ventas,autos,personas);

                    fclose(autos);
                    autos = fopen("autosArch.bin", "ab+");

                    system("cls");
                    break;
                case 9:
                    system("cls");
                    verVenta(obtenerVentaDeArchivo(ventas));
                    break;
                case 10:
                    system("cls");
                    verGananciaPeriodo(ventas);
                    break;
                case 11:
                    system("cls");
                    verVentaMasFavorable(ventas);
                    break;
                case 12:
                    system("cls");
                    verArregloDeAutos(obtenerAutosMenoresADiezAnios(autos,personas),cantAutosMenoresADiezAnios(autos));
                    break;
                case 13:
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
