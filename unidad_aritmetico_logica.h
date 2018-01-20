#ifndef UNIDAD_ARITMETICO_LOGICA_H
#define UNIDAD_ARITMETICO_LOGICA_H

#include <iostream>
#include <cstdlib>
#include <cmath>

class UNIDAD_ARITMETICO_LOGICA
{
public:
    UNIDAD_ARITMETICO_LOGICA();
    ~UNIDAD_ARITMETICO_LOGICA();
    long operacion(long&, long&);
    void cargar_a(long);
    void cargar_b(long);
    int cargar_op(int);

private:
    long indicadores(long valor);
    long A, B, F, indicador;
    int op, z, d, p, s;

};

#endif // UNIDAD_ARITMETICO_LOGICA_H
