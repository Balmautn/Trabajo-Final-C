#include <stdio.h>
#include <math.h>
#include "simulador.h"

double calcular_trabajo_rozamiento(void) {
    double energia_inicial = 0.5 * MASA_ORION * VEL_INICIAL * VEL_INICIAL + MASA_ORION * GRAVEDAD * ALTITUD_INICIAL;
    double energia_final = 0.5 * MASA_ORION * VEL_FINAL * VEL_FINAL + MASA_ORION * GRAVEDAD * ALTITUD_FINAL;
    
    return energia_final - energia_inicial;