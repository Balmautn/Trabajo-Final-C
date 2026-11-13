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

void calcular_fuerza_impacto(float d) {
    if (d <= 0) {
        printf("Error: la profundidad de hundimiento debe ser mayor a 0.\n");
        return;
    }

    double energia_cinetica = 0.5 * MASA_ORION * VEL_IMPACTO * VEL_IMPACTO;
    double fuerza_frenado = energia_cinetica / d;
    double fuerza_total = fuerza_frenado + (MASA_ORION * GRAVEDAD);

    printf("\n--- FUERZA DE IMPACTO EN EL AGUA ---\n");
    printf("Fuerza media de frenado: %.2f N\n", fuerza_frenado);
    printf("Fuerza total soportada (con peso): %.2f N\n", fuerza_total);
}

void analizar_angulo_reingreso(float angulo) {
    const double PI = 3.14159265358979323846;
    double radianes = angulo * (PI / 180.0);
    double vel_horizontal = VEL_INICIAL * cos(radianes);
    double vel_vertical = VEL_INICIAL * sin(radianes);

    printf("\n--- ANALISIS DEL ANGULO DE REINGRESO ---\n");
    printf("Angulo ingresado: %.2f grados\n", angulo);
    printf("Componente horizontal de velocidad: %.2f m/s\n", vel_horizontal);
    printf("Componente vertical de descenso: %.2f m/s\n", vel_vertical);

    if (angulo < 5.5f) {
        printf("Estado: PELIGRO DE REBOTE. El angulo es muy bajo y la capsula podria rebotar en la atmosfera hacia el espacio.\n");
    } else if (angulo > 7.5f) {
        printf("Estado: PELIGRO TERMICO Y DE G. El angulo es muy pronunciado; riesgo de sobrecalentamiento y fuerzas G criticas.\n");
    } else {
        printf("Estado: OPTIMO. La capsula ingresa dentro del corredor seguro de reingreso (5.5 a 7.5 grados).\n");
    }
}