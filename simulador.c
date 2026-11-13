#include <stdio.h>
#include <math.h>
#include "simulador.h"

double calcular_trabajo_rozamiento(void) {
    double energia_inicial = 0.5 * MASA_ORION * VEL_INICIAL * VEL_INICIAL + MASA_ORION * GRAVEDAD * ALTITUD_INICIAL;
    double energia_final = 0.5 * MASA_ORION * VEL_FINAL * VEL_FINAL + MASA_ORION * GRAVEDAD * ALTITUD_FINAL;
    
    return energia_final - energia_inicial;
}

void calcular_desaceleracion_media(float delta_t) {
    if (delta_t <= 0) {
        printf("Error: el tiempo de desaceleracion debe ser mayor a 0.\n");
        return;
    }

    double desaceleracion = (VEL_FINAL - VEL_INICIAL) / delta_t;
    double fuerzas_g = fabs(desaceleracion) / GRAVEDAD;

    printf("\n--- DESACELERACION MEDIA ---\n");
    printf("Desaceleracion: %.2f m/s^2\n", desaceleracion);
    printf("Equivalente en fuerzas G: %.2f G\n", fuerzas_g);
}