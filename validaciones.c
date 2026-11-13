#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"

// Función para leer enteros de forma segura (ej. para el menú de opciones)
int leer_entero_seguro(const char* mensaje, int min, int max) {
    int valor;
    char buffer[100];
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Intentamos parsear un entero
            if (sscanf(buffer, "%d", &valor) == 1) {
                if (valor >= min && valor <= max) {
                    valido = 1;
                } else {
                    printf("Error: El valor debe estar entre %d y %d.\n", min, max);
                }
            } else {
                printf("Error: Entrada invalida. Por favor, ingrese un numero entero.\n");
            }
        }
    } while (!valido);

    return valor;
}

// Función para leer flotantes de forma segura (ej. para los parámetros de la simulación)
float leer_flotante_seguro(const char* mensaje, float min, float max) {
    float valor;
    char buffer[100];
    int valido = 0;

    do {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Intentamos parsear un flotante
            if (sscanf(buffer, "%f", &valor) == 1) {
                if (valor >= min && valor <= max) {
                    valido = 1;
                } else {
                    printf("Error: El valor debe estar entre %.2f y %.2f.\n", min, max);
                }
            } else {
                printf("Error: Entrada invalida. Por favor, ingrese un numero valido (use punto para decimales).\n");
            }
        }
    } while (!valido);

    return valor;
}