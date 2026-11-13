#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Lee un entero en [min, max]. Repite hasta que la entrada sea valida. */
int leer_entero_seguro(const char *mensaje, int min, int max);

/* Lee un double en [min, max]. Repite hasta que la entrada sea valida. */
double leer_double_seguro(const char *mensaje, double min, double max);

#endif
