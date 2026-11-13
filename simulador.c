#include <stdio.h>
#include <math.h>
#include "simulador.h"
#include "validaciones.h"

#define PI 3.14159265358979323846

/* ---------- Auxiliares internas ---------- */

/* Energia mecanica (cinetica + potencial) en Joules */
static double energia_mecanica(double masa, double velocidad, double altitud) {
    return 0.5 * masa * velocidad * velocidad + masa * GRAVEDAD * altitud;
}

/* Arma el mensaje con unidad y rango, y pide el valor de forma segura */
static double pedir_valor(const char *nombre, const char *unidad,
                          double min, double max) {
    char mensaje[160];
    snprintf(mensaje, sizeof(mensaje), "%s [%s] (entre %.2f y %.2f): ",
             nombre, unidad, min, max);
    return leer_double_seguro(mensaje, min, max);
}

/* ---------- Carga de parametros ---------- */

void cargar_valores_por_defecto(ParametrosSimulacion *p) {
    p->masa                  = MASA_ORION;
    p->altitud_inicial       = ALTITUD_INICIAL;
    p->velocidad_inicial     = VEL_INICIAL;
    p->altitud_final         = ALTITUD_FINAL;
    p->velocidad_final       = VEL_FINAL;
    p->velocidad_impacto     = VEL_IMPACTO;
    p->tiempo_desaceleracion = TIEMPO_DESACEL_DEF;
    p->hundimiento_agua      = HUNDIMIENTO_DEF;
    p->angulo_reingreso      = ANGULO_DEF;
}

void ingresar_parametros(ParametrosSimulacion *p) {
    int modo;

    printf("\n--- PARAMETROS DE SIMULACION ---\n");
    printf("1. Usar los valores del enunciado\n");
    printf("2. Ingresar valores manualmente\n");
    modo = leer_entero_seguro("Opcion (1-2): ", 1, 2);

    if (modo == 1) {
        cargar_valores_por_defecto(p);
        printf("Valores del enunciado cargados.\n");
        return;
    }

    /* Se piden en este orden para que los rangos sean coherentes entre si */
    p->masa = pedir_valor("Masa de la capsula", "kg", 1000.0, 100000.0);
    p->altitud_final = pedir_valor("Altitud de apertura de paracaidas", "m",
                                   100.0, 20000.0);
    p->altitud_inicial = pedir_valor("Altitud de reingreso", "m",
                                     p->altitud_final + 1.0, 200000.0);
    p->velocidad_inicial = pedir_valor("Velocidad de reingreso", "m/s",
                                       100.0, 15000.0);
    p->velocidad_final = pedir_valor("Velocidad al abrir paracaidas", "m/s",
                                     1.0, p->velocidad_inicial);
    p->velocidad_impacto = pedir_valor("Velocidad de amerizaje", "m/s",
                                       0.0, p->velocidad_final);
    p->tiempo_desaceleracion = pedir_valor("Duracion de la fase de mayor desaceleracion",
                                           "s", 1.0, 5000.0);
    p->hundimiento_agua = pedir_valor("Hundimiento en el agua", "m", 0.01, 20.0);
    p->angulo_reingreso = pedir_valor("Angulo de reingreso", "grados", 0.1, 90.0);

    printf("Parametros cargados correctamente.\n");
}

/* ---------- Calculos fisicos ---------- */

/* W_roz = delta(Em) = Em_final - Em_inicial (negativo: el aire quita energia) */
double calcular_trabajo_rozamiento(const ParametrosSimulacion *p) {
    double em_inicial = energia_mecanica(p->masa, p->velocidad_inicial,
                                         p->altitud_inicial);
    double em_final   = energia_mecanica(p->masa, p->velocidad_final,
                                         p->altitud_final);
    return em_final - em_inicial;
}

void mostrar_trabajo_rozamiento(const ParametrosSimulacion *p) {
    double w = calcular_trabajo_rozamiento(p);

    printf("\n--- TRABAJO DE ROZAMIENTO ATMOSFERICO ---\n");
    printf("Energia mecanica inicial: %.4e J\n",
           energia_mecanica(p->masa, p->velocidad_inicial, p->altitud_inicial));
    printf("Energia mecanica final:   %.4e J\n",
           energia_mecanica(p->masa, p->velocidad_final, p->altitud_final));
    printf("Trabajo de rozamiento:    %.4e J\n", w);
    printf("Energia disipada por el escudo termico: %.4e J\n", -w);
}

void calcular_y_mostrar_desaceleracion(const ParametrosSimulacion *p) {
    double a = (p->velocidad_final - p->velocidad_inicial)
               / p->tiempo_desaceleracion;

    printf("\n--- DESACELERACION MEDIA ---\n");
    printf("Desaceleracion media: %.2f m/s^2\n", a);
    printf("Equivalente en g:     %.2f g\n", fabs(a) / GRAVEDAD);
}

void calcular_y_mostrar_impacto(const ParametrosSimulacion *p) {
    /* Por trabajo-energia: F_agua * d = Ec  ->  F_frenado = m*v^2 / (2*d)
       La fuerza total del agua tambien debe sostener el peso: N = F_frenado + m*g */
    double peso = p->masa * GRAVEDAD;
    double f_frenado = 0.5 * p->masa * p->velocidad_impacto
                       * p->velocidad_impacto / p->hundimiento_agua;
    double f_total = f_frenado + peso;

    printf("\n--- FUERZA DE IMPACTO EN EL AGUA ---\n");
    printf("Peso de la nave:               %.2f N\n", peso);
    printf("Fuerza de frenado (m*v^2/2d):  %.2f N\n", f_frenado);
    printf("Fuerza promedio total del agua: %.2f N\n", f_total);
    printf("Equivalente en pesos de la nave: %.2f veces\n", f_total / peso);
}

void analizar_angulo_reingreso(const ParametrosSimulacion *p) {
    double rad = p->angulo_reingreso * PI / 180.0;

    printf("\n--- ANALISIS DEL ANGULO DE REINGRESO ---\n");
    printf("Angulo ingresado: %.2f grados\n", p->angulo_reingreso);
    printf("Componente horizontal de la velocidad: %.2f m/s\n",
           p->velocidad_inicial * cos(rad));
    printf("Componente vertical (descenso):        %.2f m/s\n",
           p->velocidad_inicial * sin(rad));

    if (p->angulo_reingreso < ANGULO_MIN_SEGURO) {
        printf("Estado: REBOTE ATMOSFERICO. Angulo menor a %.1f grados: la capsula\n"
               "no penetra lo suficiente, rebota hacia el espacio y no vuelve a la\n"
               "trayectoria de reingreso.\n", ANGULO_MIN_SEGURO);
    } else if (p->angulo_reingreso > ANGULO_MAX_SEGURO) {
        printf("Estado: DESACELERACION EXCESIVA. Angulo mayor a %.1f grados: la\n"
               "capsula frena en una capa muy densa, con g y carga termica que\n"
               "superan los limites de la tripulacion y del escudo.\n", ANGULO_MAX_SEGURO);
    } else {
        printf("Estado: OPTIMO. Dentro de la ventana segura (%.1f a %.1f grados).\n",
               ANGULO_MIN_SEGURO, ANGULO_MAX_SEGURO);
    }
}
