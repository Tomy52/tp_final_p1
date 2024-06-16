#include <stdio.h>
#include <stdlib.h>

#define LONG_MAX_LOGIN 30

typedef struct {
char nombre[LONG_MAX_LOGIN];
char clave[LONG_MAX_LOGIN];
} Usuario;

typedef struct {
char letras[4];
char numeros[4];
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

void menuUsuario();
void menuConcesionaria();
void agregarUsuario(FILE *usuarios);
void mostrarUsuario(FILE *usuarios);
int login(FILE *usuarios);
void loginCheck(int estado);
int validarLongitudCredenciales(char usuario[], char clave[], int longMax);
int validarExistenciaUsuario(FILE *usuarios, char nombreUsuario[]);
int validarCredenciales(char usuario[], char clave[], int longMax, FILE *usuarios);
Patente agregarPatente();
void verPatente(Patente patente);
int compararPatente(Patente patenteA, Patente patenteB);
void agregarAuto(FILE *archAuto);
void verAutoDeArchivo(FILE *archAuto, FILE *personas);
void verAuto(Auto coche);
void verListadoAutos(FILE *archAuto);
void agregarPersona(FILE *personas);
void verPersona(Persona persona);
void verListadoPersonas(FILE *personas);
void verPersonaPorDNI(FILE *personas);
Persona obtenerPersonaPorDNI(FILE *personas, int dni);

int logueado = 0;

int main() {
    menuUsuario();
    menuConcesionaria();
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


