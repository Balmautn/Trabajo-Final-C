#include <stdio.h>
#include <stdlib.h>

#include "simulador.h"
#include "validaciones.h"

int main() {
    int opcion;
    ParametrosSimulacion params; 

    do {
        printf("\n=== SIMULADOR MISION ARTEMIS: REINGRESO ATMOSFERICO ===\n");
        printf("1. Ingresar parametros de simulacion\n");
        printf("2. Calcular Trabajo de Rozamiento\n");
        printf("3. Calcular Desaceleracion Media\n");
        printf("4. Calcular Fuerza de Impacto\n");
        printf("5. Analizar Angulo de Reingreso\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        
      
        scanf("%d", &opcion); 

        switch(opcion) {
            case 1:
                printf("Ingresando datos...\n");
                // Pedir datos al usuario
                break;
            case 2:
                // Llamar a calcular_trabajo_rozamiento(...)
                break;
            case 3:
                // Llamar a calcular_y_mostrar_desaceleracion(...)
                break;
            case 4:
                // Llamar a calcular_y_mostrar_impacto(...)
                break;
            case 5:
                // Llamar a analizar_angulo_reingreso(...)
                break;
            case 6:
                printf("Saliendo del simulador...\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while(opcion != 6);

    return 0;
}