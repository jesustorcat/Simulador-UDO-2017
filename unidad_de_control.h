#ifndef UNIDAD_DE_CONTROL_H
#define UNIDAD_DE_CONTROL_H

#include <iostream>

class UNIDAD_DE_CONTROL
{
public:
    UNIDAD_DE_CONTROL();
    ~UNIDAD_DE_CONTROL();
    void ejecutar_control(int&,int&,int&,int&,int&,int&,int&,int&,int&,int&,
                          int&,int&,int&,int&,int&,int&,int&,int&);
    void cargar_temporizador(long int);
    void cargar_ri(long);
    void cargar_indicadores(int);

private:
    long int temporizador;
    long ri;
    int z, d, p, s, op, indicadores;
    int Ca, La, Cb, Lb, Cf, Lf; //Señales de control de la unidad aritmetico lógica
    int Cri, Lri, Rt; //Señales del Registro de instrucciónes y Registro del temporizador
    int Ccp, Lcp, Icp, Dcp; //Señales de control del Contador de programa
    int Crdm, Em, Lm; // Señales de control de la Unidad de Memoria
    int Ce, Le, Cs; //Señales de control del dispositivo de entrada y sálida.
};

#endif // UNIDAD_DE_CONTROL_H
