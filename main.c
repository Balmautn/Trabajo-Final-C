#include <stdio.h>

#include "simulador.h"
#include "validaciones.h"

static void mostrar_menu(void) {
    printf("\n=== SIMULADOR MISION ARTEMIS: REINGRESO ATMOSFERICO ===\n");
    printf("1. Ingresar los parametros de simulacion\n");
    printf("2. Calcular el trabajo de rozamiento\n");
    printf("3. Calcular la desaceleracion media\n");
    printf("4. Calcular la fuerza de impacto\n");
    printf("5. Analizar el angulo de reingreso\n");
    printf("6. Salir\n");
}

int main(void) {
    ParametrosSimulacion params;
    int datos_cargados = 0;
    int opcion;

    cargar_valores_por_defecto(&params);

    do {
        mostrar_menu();
        opcion = leer_entero_seguro("Ingrese una opcion (1-6): ", 1, 6);

        if (opcion >= 2 && opcion <= 5 && !datos_cargados) {
            printf("Aviso: primero cargue los parametros (opcion 1).\n");
            continue;
        }

        switch (opcion) {
            case 1:
                ingresar_parametros(&params);
                datos_cargados = 1;
                break;
            case 2:
                mostrar_trabajo_rozamiento(&params);
                break;
            case 3:
                calcular_y_mostrar_desaceleracion(&params);
                break;
            case 4:
                calcular_y_mostrar_impacto(&params);
                break;
            case 5:
                analizar_angulo_reingreso(&params);
                break;
            case 6:
                printf("Saliendo del simulador...\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}
