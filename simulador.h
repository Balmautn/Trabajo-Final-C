#ifndef SIMULADOR_H
#define SIMULADOR_H

// --- CONSTANTES FÍSICAS (Escenario 4: Reingreso Orion) ---
#define MASA_ORION 10400.0       // kg
#define ALTITUD_INICIAL 120000.0 // m (120 km)
#define VEL_INICIAL 11000.0      // m/s (11 km/s)
#define ALTITUD_FINAL 2500.0     // m (2.5 km)
#define VEL_FINAL 25.0           // m/s
#define VEL_IMPACTO 8.0          // m/s
#define GRAVEDAD 9.81            // m/s^2

// --- ESTRUCTURA DE DATOS ---
typedef struct {
    float tiempo_desaceleracion; // Delta t (ej. 400.0 s)
    float hundimiento_agua;      // d (ej. 1.50 m)
    float angulo_reingreso;      // gamma (ej. 6.0 grados)
} ParametrosSimulacion;

// --- PROTOTIPOS DE LAS FUNCIONES FÍSICAS ---
double calcular_trabajo_rozamiento(void);
void calcular_desaceleracion_media(float delta_t);
void calcular_fuerza_impacto(float d);
void analizar_angulo_reingreso(float angulo);

#endif