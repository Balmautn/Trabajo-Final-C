#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "validaciones.h"

#define TAM_BUFFER 100

/* Lee una linea completa. Devuelve 1 si es valida, 0 si era demasiado larga.
   Si la entrada se cierra (Ctrl+D), termina el programa en forma ordenada. */
static int leer_linea(char *buffer, int tam) {
    int c;

    if (fgets(buffer, tam, stdin) == NULL) {
        printf("\nEntrada cerrada. Saliendo del programa.\n");
        exit(EXIT_FAILURE);
    }
    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        while ((c = getchar()) != '\n' && c != EOF);   /* descarta el resto */
        printf("Error: entrada demasiado larga.\n");
        return 0;
    }
    return 1;
}

int leer_entero_seguro(const char *mensaje, int min, int max) {
    char buffer[TAM_BUFFER], *fin;
    long valor;

    for (;;) {
        printf("%s", mensaje);
        if (!leer_linea(buffer, TAM_BUFFER)) continue;

        errno = 0;
        valor = strtol(buffer, &fin, 10);
        if (fin == buffer || errno == ERANGE) {
            printf("Error: ingrese un numero entero valido.\n");
        } else if (*fin != '\n' && *fin != '\0') {
            printf("Error: caracteres no validos despues del numero.\n");
        } else if (valor < min || valor > max) {
            printf("Error: el valor debe estar entre %d y %d.\n", min, max);
        } else {
            return (int)valor;
        }
    }
}

double leer_double_seguro(const char *mensaje, double min, double max) {
    char buffer[TAM_BUFFER], *fin;
    double valor;

    for (;;) {
        printf("%s", mensaje);
        if (!leer_linea(buffer, TAM_BUFFER)) continue;

        errno = 0;
        valor = strtod(buffer, &fin);
        if (fin == buffer || errno == ERANGE) {
            printf("Error: ingrese un numero valido (use punto decimal).\n");
        } else if (*fin != '\n' && *fin != '\0') {
            printf("Error: caracteres no validos despues del numero.\n");
        } else if (!(valor >= min && valor <= max)) {  /* tambien rechaza NaN */
            printf("Error: el valor debe estar entre %.2f y %.2f.\n", min, max);
        } else {
            return valor;
        }
    }
}
