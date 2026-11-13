#ifndef SIMULADOR_H
#define SIMULADOR_H

/* --- VALORES POR DEFECTO (Escenario 4: Reingreso Orion) --- */
#define MASA_ORION          10400.0   /* kg  */
#define ALTITUD_INICIAL     120000.0  /* m   (120 km)  */
#define VEL_INICIAL         11000.0   /* m/s (11 km/s) */
#define ALTITUD_FINAL       2500.0    /* m   (2,5 km)  */
#define VEL_FINAL           25.0      /* m/s */
#define VEL_IMPACTO         8.0       /* m/s */
#define TIEMPO_DESACEL_DEF  400.0     /* s   */
#define HUNDIMIENTO_DEF     1.50      /* m   */
#define ANGULO_DEF          6.0       /* grados */

/* --- CONSTANTE FISICA (mismo valor que el enunciado) --- */
#define GRAVEDAD            9.80      /* m/s^2 */

/* --- VENTANA DE SEGURIDAD DEL ANGULO DE REINGRESO --- */
#define ANGULO_MIN_SEGURO   5.5       /* grados */
#define ANGULO_MAX_SEGURO   7.0       /* grados */

/* --- ESTRUCTURA DE DATOS --- */
typedef struct {
    double masa;                  /* kg  */
    double altitud_inicial;       /* m   */
    double velocidad_inicial;     /* m/s */
    double altitud_final;         /* m   (apertura de paracaidas) */
    double velocidad_final;       /* m/s */
    double velocidad_impacto;     /* m/s */
    double tiempo_desaceleracion; /* s   (delta t) */
    double hundimiento_agua;      /* m   (d) */
    double angulo_reingreso;      /* grados (gamma) */
} ParametrosSimulacion;

/* --- PROTOTIPOS (todos reciben la estructura por puntero) --- */
void cargar_valores_por_defecto(ParametrosSimulacion *p);
void ingresar_parametros(ParametrosSimulacion *p);

double calcular_trabajo_rozamiento(const ParametrosSimulacion *p);
void mostrar_trabajo_rozamiento(const ParametrosSimulacion *p);
void calcular_y_mostrar_desaceleracion(const ParametrosSimulacion *p);
void calcular_y_mostrar_impacto(const ParametrosSimulacion *p);
void analizar_angulo_reingreso(const ParametrosSimulacion *p);

#endif
