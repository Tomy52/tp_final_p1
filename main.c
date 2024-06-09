#include <stdio.h>
#include <stdlib.h>

#define LONG_MAX_LOGIN 30

typedef struct {
char nombre[LONG_MAX_LOGIN];
char clave[LONG_MAX_LOGIN];
} Usuario;

typedef struct {
char letras[3];
char numeros[3];
} Patente;

typedef struct {
Patente patente;
char marca[30];
char modelo[30];
int anio;
int kms;
int dniTitular;
float precioDeAdquisicion;
} AutoArchivo;

typedef struct {
int dni;
char nombre[30];
int telefono;
char direccion[30];
char rol[30]; //comprador o vendedor
} Persona;

typedef struct {
Patente patente;
char marca[30];
char modelo[30];
int anio;
int kms;
Persona Titular;
float precioDeAdquisicion;
} Auto;

typedef struct {
int dia;
int mes;
int anio;
} Fecha;

typedef struct {
Fecha fecha;
Patente autoAVender;
float precioVenta;
float ganancia;
int dniComprador;
int dniVendedor;
} Venta;

void agregarUsuario(char nombreArchivo[]);
void mostrarUsuario(char nombreArchivo[]);
int login(char nombreArchivo[]);
void loginCheck(int estado);
int validarLongitudCredenciales(char usuario[], char clave[], int longMax);
int validarExistenciaUsuario(char nombreArchivo[], char nombreUsuario[]);
int validarCredenciales(char usuario[], char clave[], int longMax, char nombreArchivo[]);

int main()
{
    agregarUsuario("corto1.bin");
    mostrarUsuario("corto1.bin");
    loginCheck(login("corto1.bin"));
    return 0;
}

// Agrega usuarios a un archivo o lo crea de no existir

void agregarUsuario(char nombreArchivo[]) {
    FILE *usuarios;
    usuarios = fopen(nombreArchivo,"ab");
    Usuario usuario;

    char nombre[LONG_MAX_LOGIN];
    char clave[LONG_MAX_LOGIN];

    if (usuarios == NULL) {
        printf("Archivo invalido");
        return;
    }

    printf("Ingrese un usuario: ");
    fflush(stdin);
    scanf("%s",nombre);

    printf("Ingrese una clave: ");
    fflush(stdin);
    scanf("%s",clave);

    if (validarCredenciales(nombre, clave, LONG_MAX_LOGIN, nombreArchivo) == 0) {
        printf("Credenciales invalidas, reintente nuevamente\n");
    }

    if (validarCredenciales(nombre, clave, LONG_MAX_LOGIN, nombreArchivo) == 1) {
        strcpy(usuario.nombre,nombre);
        strcpy(usuario.clave,clave);

        fwrite(&usuario,sizeof(Usuario),1,usuarios);
    }

    fclose(usuarios);
}

void mostrarUsuario(char nombreArchivo[]) { // Funcion de prueba, muestra los usuarios cargados en un archivo dado
    FILE *usuarios;
    usuarios = fopen(nombreArchivo,"rb");

    Usuario usuario;

    if (usuarios == NULL) {
        printf("Archivo invalido");
        return;
    }

    while (fread(&usuario,sizeof(Usuario),1,usuarios) != 0) {
        printf("Nombre: %s\n",usuario.nombre);
        printf("Clave: %s\n\n",usuario.clave);
    }

    fclose(usuarios);
}

int login(char nombreArchivo[]) { // Lee archivo de usuarios y retorna 0 si fallo o 1 si fue exitoso
    FILE *usuarios;
    usuarios = fopen(nombreArchivo,"rb");

    Usuario usuario;
    char nombreEnviado[LONG_MAX_LOGIN];
    char claveEnviada[LONG_MAX_LOGIN];
    int logueado = 0;

    if (usuarios == NULL) {
        printf("Archivo invalido");
        return 0;
    }

    printf("Ingrese un usuario: ");
    scanf("%s",&nombreEnviado);
    printf("Ingrese una clave: ");
    scanf("%s",&claveEnviada);

    while (fread(&usuario,sizeof(Usuario),1,usuarios) != 0 && logueado == 0) {
        if (strcmp(nombreEnviado,usuario.nombre) == 0 && strcmp(claveEnviada,usuario.clave) == 0) {
            printf("Bienvenido %s\n",usuario.nombre);
            logueado = 1;
        }
    }

    if (logueado == 0) printf("No se encontro el usuario / clave incorrecta\n");

    fclose(usuarios);

    return logueado;
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

int validarExistenciaUsuario(char nombreArchivo[], char nombreUsuario[]) {
    int flag = 0;
    FILE *usuarios;
    usuarios = fopen(nombreArchivo,"rb");

    Usuario usuario;

    if (usuarios == NULL) {
        printf("Archivo invalido");
        return flag;
    }

    while (fread(&usuario,sizeof(Usuario),1,usuarios) != 0 && flag == 0) {
        if (strcmp(usuario.nombre,nombreUsuario) == 0) {
            flag = 1;
        }
    }

    fclose(usuarios);
    return flag;
}

int validarCredenciales(char usuario[], char clave[], int longMax, char nombreArchivo[]) {
    int flag = 1;

    if (validarLongitudCredenciales(usuario,clave,longMax) == 0) {
        flag = 0;
    }
    if (validarExistenciaUsuario(nombreArchivo, usuario) == 1) {
        flag = 0;
    }

    return flag;
}


