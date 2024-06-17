#include "Usuario.h"

void agregarUsuario(FILE *usuarios) {
    Usuario usuario;
    int credencialesValidas;

    char nombre[LONG_MAX_LOGIN];
    char clave[LONG_MAX_LOGIN];

    printf("Ingrese un usuario: ");
    fflush(stdin);
    scanf("%s", nombre);

    printf("Ingrese una clave: ");
    fflush(stdin);
    scanf("%s", clave);

    credencialesValidas = validarCredenciales(nombre, clave, LONG_MAX_LOGIN, usuarios);

    if (credencialesValidas == 0)
    {
        printf("Credenciales muy largas o repetidas, reintente nuevamente\n");
    }

    if (credencialesValidas == 1)
    {
        fseek(usuarios,0,SEEK_END);
        strcpy(usuario.nombre, nombre);
        strcpy(usuario.clave, clave);

        fwrite(&usuario, sizeof(Usuario), 1, usuarios);
    }

}

void mostrarUsuario(FILE *usuarios) { // Funcion de prueba, muestra los usuarios cargados en un archivo dado
    Usuario usuario;

    fseek(usuarios,0,SEEK_SET);

    while (fread(&usuario, sizeof(Usuario), 1, usuarios) != 0) {
        printf("Nombre: %s\n", usuario.nombre);
        printf("Clave: %s\n\n", usuario.clave);
    }

}

int login(FILE *usuarios) { // Lee archivo de usuarios y retorna 0 si fallo o 1 si fue exitoso
    Usuario usuario;
    char nombreEnviado[LONG_MAX_LOGIN];
    char claveEnviada[LONG_MAX_LOGIN];

    int flag = 0;

    printf("Ingrese un usuario: ");
    scanf("%s", &nombreEnviado);
    printf("Ingrese una clave: ");
    scanf("%s", &claveEnviada);

    fseek(usuarios,0,SEEK_SET);

    while (fread(&usuario, sizeof(Usuario), 1, usuarios) != 0 && flag == 0) {
        if (strcmp(nombreEnviado, usuario.nombre) == 0 && strcmp(claveEnviada, usuario.clave) == 0) {
            printf("Bienvenido %s\n", usuario.nombre);
            flag = 1;
        }
    }


    if (flag == 0) printf("No se encontro el usuario / clave incorrecta\n");

    return flag;
}

void loginCheck(int estado) { // Funcion de prueba, chequea si el login fue exitoso o no
    if (estado == 1) printf("esta logueado");
    if (estado == 0) printf("no esta logueado");
}

int validarLongitudCredenciales(char usuario[], char clave[], int longMax) {
    int flag = 1;

    if (strlen(usuario) >= longMax || strlen(clave) >= longMax) {
        flag = 0;
    }

    return flag;
}

int validarExistenciaUsuario(FILE *usuarios, char nombreUsuario[]) {
    int flag = 0;
    Usuario usuario;

    fseek(usuarios,0,SEEK_SET);

    while (fread(&usuario, sizeof(Usuario), 1, usuarios) != 0 && flag == 0) {
        if (strcmp(usuario.nombre, nombreUsuario) == 0) {
            flag = 1;
        }
    }

    return flag;
}

int validarCredenciales(char usuario[], char clave[], int longMax, FILE *usuarios) {
    int flag = 1;

    if (validarLongitudCredenciales(usuario,clave,longMax) == 0) {
        flag = 0;
    }
    if (validarExistenciaUsuario(usuarios, usuario) == 1) {
        flag = 0;
    }

    return flag;
}
