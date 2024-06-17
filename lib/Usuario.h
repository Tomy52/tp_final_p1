#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define LONG_MAX_LOGIN 30

typedef struct {
char nombre[LONG_MAX_LOGIN];
char clave[LONG_MAX_LOGIN];
} Usuario;

void agregarUsuario(FILE *usuarios);
void mostrarUsuario(FILE *usuarios);
int login(FILE *usuarios);
void loginCheck(int estado);
int validarLongitudCredenciales(char usuario[], char clave[], int longMax);
int validarExistenciaUsuario(FILE *usuarios, char nombreUsuario[]);
int validarCredenciales(char usuario[], char clave[], int longMax, FILE *usuarios);

#endif // USUARIO_H_INCLUDED
