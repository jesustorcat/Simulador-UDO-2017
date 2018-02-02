#ifndef UNIDAD_DE_CONTROL_H
#define UNIDAD_DE_CONTROL_H

#include <iostream>

class UNIDAD_DE_CONTROL
{
public:
    UNIDAD_DE_CONTROL();
    ~UNIDAD_DE_CONTROL();
    void ejecutar_control(int&,int&,int&,int&,int&,int&,int&,int&,int&,int&,
                          int&,int&,int&,int&,int&,int&,int&,int&,int&,int&,
                          int&,int&,int&,int&);
    void cargar_temporizador(long int);
    void cargar_ri(long);
    void cargar_indicadores(int);

private:
    long int temporizador;
    long ri;
    int z, d, p, s, op, indicadores;
};

#endif // UNIDAD_DE_CONTROL_H
